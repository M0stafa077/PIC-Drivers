/* 
 * File:   MCAL_EXTI.h
 * Author: Mostafa Asaad
 *
 * Created on January 14, 2024, 9:20 PM
 */

/* -------------- Section : Includes -------------- */
#include "MCAL_EXTI.h"

/* -------------- Section : Pointers To ISRs --------------*/
static interrupt_handler_t INT0_INTERRUPT_HANDLER = NULL;
static interrupt_handler_t INT1_INTERRUPT_HANDLER = NULL;
static interrupt_handler_t INT2_INTERRUPT_HANDLER = NULL;

static interrupt_handler_t RB4_INTERRUPT_HIGH_HANDLER = NULL;
static interrupt_handler_t RB4_INTERRUPT_LOW_HANDLER = NULL;
static interrupt_handler_t RB5_INTERRUPT_HIGH_HANDLER = NULL;
static interrupt_handler_t RB5_INTERRUPT_LOW_HANDLER = NULL;
static interrupt_handler_t RB6_INTERRUPT_HIGH_HANDLER = NULL;
static interrupt_handler_t RB6_INTERRUPT_LOW_HANDLER = NULL;
static interrupt_handler_t RB7_INTERRUPT_HIGH_HANDLER = NULL;
static interrupt_handler_t RB7_INTERRUPT_LOW_HANDLER = NULL;


/* -------------- Section : Helper Functions Declaration -------------- */
static Std_ReturnType EXTI_INTx_enable(const EXTI_INTx_t* int_obj);
static Std_ReturnType EXTI_INTx_disable(const EXTI_INTx_t* int_obj);
static Std_ReturnType EXTI_INTx_edge_init(const EXTI_INTx_t* int_obj);
static Std_ReturnType EXTI_INTx_pin_init(const EXTI_INTx_t* int_obj);
static Std_ReturnType EXTI_INTx_clear_flag(const EXTI_INTx_t* int_obj);

static Std_ReturnType EXTI_INT0_setInterruptHandler(void (*EXTI_handler)(void));
static Std_ReturnType EXTI_INT1_setInterruptHandler(void (*EXTI_handler)(void));
static Std_ReturnType EXTI_INT2_setInterruptHandler(void (*EXTI_handler)(void));
static Std_ReturnType EXTI_INTx_setInterruptHandler(const EXTI_INTx_t* int_obj);

static Std_ReturnType EXTI_RBx_pin_init(const EXTI_RBx_t* int_obj);
static Std_ReturnType EXTI_RBx_setInterruptHandler(const EXTI_RBx_t* int_obj);

#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
static Std_ReturnType EXTI_INTx_priority_init(const EXTI_INTx_t* int_obj);
static Std_ReturnType EXTI_RBx_priority_init(const EXTI_RBx_t* int_obj);
#endif

/* -------------- Section: Function Definitions -------------- */

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_INTx_init(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1.Disable EXTI */
        ret = EXTI_INTx_disable(int_obj);
        
        /* 2.Clear EXTI Flag */
        ret = EXTI_INTx_clear_flag(int_obj);
        
        /* 3.Configure EXTI Edge */
        ret = EXTI_INTx_edge_init(int_obj);
        
        /* 4.Configure EXTI Priority */
        #if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        ret = EXTI_INTx_priority_init(int_obj);
        
        #else
        INTERRUPT_GIEH_ENABLE();
        INTERRUPT_GIEL_ENABLE();
        #endif
        
        /* 5.Configure EXTI Pin */
        ret = EXTI_INTx_pin_init(int_obj);
        
        /* 6.Configure EXTI CallBack */
        ret = EXTI_INTx_setInterruptHandler(int_obj);
        
        /* 7.Enable EXTI */
        ret = EXTI_INTx_enable(int_obj);
    }
    return ret;
}



/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_INTx_deInit(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = EXTI_INTx_disable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_RBx_init(const EXTI_RBx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1.Disable EXTI */
        EXTI_RBx_DISABLE();
        
        /* 2.Clear EXTI Flag */
        EXTI_RBx_CLR_FLAG();
        
        /* 3.Configure EXTI Priority */
        #if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        ret = EXTI_RBx_priority_init(int_obj); 
        #else
        INTERRUPT_GIEH_ENABLE();
        INTERRUPT_GIEL_ENABLE();
        #endif

        /* 4.Configure EXTI Pin */
        ret = EXTI_RBx_pin_init(int_obj);

        /* 5.Configure EXTI CallBack */
        ret = EXTI_RBx_setInterruptHandler(int_obj);
        
        /* 6.Enable EXTI */
        EXTI_RBx_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EXTI_RBx_deInit(const EXTI_RBx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXTI_RBx_DISABLE();
    }
    return ret;
}
/* -------------- Section : End Of Functions Definitions --------------  */

/* -------------- Section : ISRs For INTx Pins --------------  */
void INT0_ISR(void)
{
    /* First : Clear the flag. */
    EXTI_INT0_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT0 */
    if(INT0_INTERRUPT_HANDLER) { INT0_INTERRUPT_HANDLER(); }
}

void INT1_ISR(void)
{
    /* First : Clear the flag. */
    EXTI_INT1_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT1 */
    if(INT1_INTERRUPT_HANDLER) { INT1_INTERRUPT_HANDLER(); }
}
void INT2_ISR(void)
{
    /* First : Clear the flag. */
    EXTI_INT2_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT2 */
    if(INT2_INTERRUPT_HANDLER) { INT2_INTERRUPT_HANDLER(); }
}

void RB4_ISR(uint8_t mode)
{
    /* First : Clear the flag. */
    EXTI_RBx_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT2 */
    if (STD_HIGH == mode)
    {
        if(RB4_INTERRUPT_HIGH_HANDLER) { RB4_INTERRUPT_HIGH_HANDLER(); };
    }   
    else if(STD_LOW == mode)
    {
        if(RB4_INTERRUPT_LOW_HANDLER)  { RB4_INTERRUPT_LOW_HANDLER(); };
    }
    else
        {/* Nothing */}
}
void RB5_ISR(uint8_t mode)
{
    /* First : Clear the flag. */
    EXTI_RBx_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT2 */
    if(RB5_INTERRUPT_HIGH_HANDLER) { RB5_INTERRUPT_HIGH_HANDLER(); };
    if(RB5_INTERRUPT_LOW_HANDLER)  { RB5_INTERRUPT_LOW_HANDLER(); };
}
void RB6_ISR(uint8_t mode)
{
    /* First : Clear the flag. */
    EXTI_RBx_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT2 */
    if (STD_HIGH == mode)
    {
        if(RB6_INTERRUPT_HIGH_HANDLER) { RB6_INTERRUPT_HIGH_HANDLER(); };
    }   
    else if(STD_LOW == mode)
    {
        if(RB6_INTERRUPT_LOW_HANDLER)  { RB6_INTERRUPT_LOW_HANDLER(); };
    }
    else
        {/* Nothing */}
}
void RB7_ISR(uint8_t mode)
{
    /* First : Clear the flag. */
    EXTI_RBx_CLR_FLAG();
    
    /* Second : Write Your Code */
    
    /* Third : Call the CallBack Function For INT2 */
    if (STD_HIGH == mode)
    {
        if(RB7_INTERRUPT_HIGH_HANDLER) { RB7_INTERRUPT_HIGH_HANDLER(); };
    }   
    else if(STD_LOW == mode)
    {
        if(RB7_INTERRUPT_LOW_HANDLER)  { RB7_INTERRUPT_LOW_HANDLER(); };
    }
    else
        {/* Nothing */}    
}
/* -------------- End Of ISRs -------------- */

/* -------------- Section : Helper Functions Definitions -------------- */

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INTx_enable(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->src)
        {
            case EXTI_INT0:
                INTERRUPT_GIEH_ENABLE();    /* INTCON<7> */
                INTERRUPT_GIEL_ENABLE();    /* INTCON<6> */
                EXTI_INT0_ENABLE();
                break;
            case EXTI_INT1:
                INTERRUPT_GIEH_ENABLE();
                INTERRUPT_GIEL_ENABLE();
                EXTI_INT1_ENABLE();
                break;
            case EXTI_INT2:
                INTERRUPT_GIEH_ENABLE();
                INTERRUPT_GIEL_ENABLE();
                EXTI_INT2_ENABLE();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
        
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INTx_disable(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->src)
        {
            case EXTI_INT0:
                EXTI_INT0_DISABLE();
                break;
            case EXTI_INT1:
                EXTI_INT1_DISABLE();
                break;
            case EXTI_INT2:
                EXTI_INT2_DISABLE();
                break;
            default:
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
static Std_ReturnType EXTI_INTx_priority_init(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (int_obj->src)
        {
            case EXTI_INT0:
                if(PRIORITY_LOW == int_obj->priority)
                    ret = E_NOT_OK;/*Warning: INT0 is Always At High Priority*/
                break;
            case EXTI_INT1:
                switch(int_obj->priority)
                {
                    case PRIORITY_HIGH:
                        INTERRUPT_PRIORITY_ENABLE();
                        INTERRUPT_GIEH_ENABLE();
                        EXTI_INT1_PRIORITY_HIGH();
                        break;
                    case PRIORITY_LOW:
                        INTERRUPT_PRIORITY_ENABLE();
                        INTERRUPT_GIEL_ENABLE();
                        EXTI_INT1_PRIORITY_LOW();
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
                break;
            case EXTI_INT2:
                switch(int_obj->priority)
                {
                    case PRIORITY_HIGH:
                        INTERRUPT_PRIORITY_ENABLE();
                        INTERRUPT_GIEH_ENABLE();
                        EXTI_INT2_PRIORITY_HIGH();
                        break;
                    case PRIORITY_LOW:
                        INTERRUPT_PRIORITY_ENABLE();
                        INTERRUPT_GIEL_ENABLE();
                        EXTI_INT2_PRIORITY_LOW();
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
static Std_ReturnType EXTI_INTx_edge_init(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->src)
        {
            case EXTI_INT0:
                switch(int_obj->edge)
                {
                    case INTERRUPT_RISING_EDGE:
                        EXTI_INT0_AT_RISING_EDGE();
                        break;
                    case INTERRUPT_FALLING_EDGE:
                        EXTI_INT0_AT_FALLING_EDGE();
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
                break;
            case EXTI_INT1:
                switch(int_obj->edge)
                {
                    case INTERRUPT_RISING_EDGE:
                        EXTI_INT1_AT_RISING_EDGE();
                        break;
                    case INTERRUPT_FALLING_EDGE:
                        EXTI_INT1_AT_FALLING_EDGE();
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
                break;
            case EXTI_INT2:
                switch(int_obj->edge)
                {
                    case INTERRUPT_RISING_EDGE:
                        EXTI_INT2_AT_RISING_EDGE();
                        break;
                    case INTERRUPT_FALLING_EDGE:
                        EXTI_INT2_AT_FALLING_EDGE();
                        break;
                    default:
                        ret = E_NOT_OK;
                        break;
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INTx_pin_init(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_init(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INTx_clear_flag(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->src)
        {
            case EXTI_INT0:
                EXTI_INT0_CLR_FLAG();
                break;
            case EXTI_INT1:
                EXTI_INT1_CLR_FLAG();
                break;
            case EXTI_INT2:
                EXTI_INT2_CLR_FLAG();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;    
}

/**
 * 
 * @param EXTI_handler : A pointer to the ISR.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INT0_setInterruptHandler(void (*EXTI_handler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == EXTI_handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_INTERRUPT_HANDLER = EXTI_handler;
    }
    return ret;
}

/**
 * 
 * @param EXTI_handler : A pointer to the ISR.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INT1_setInterruptHandler(void (*EXTI_handler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == EXTI_handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_INTERRUPT_HANDLER = EXTI_handler;
    }
    return ret;  
}

/**
 * 
 * @param EXTI_handler : A pointer to the ISR.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INT2_setInterruptHandler(void (*EXTI_handler)(void))
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == EXTI_handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_INTERRUPT_HANDLER = EXTI_handler;
    }
    return ret;
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_INTx_setInterruptHandler(const EXTI_INTx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->src)
        {
            case EXTI_INT0:
                ret = EXTI_INT0_setInterruptHandler(int_obj->EXTI_Handler);
                break;
            case EXTI_INT1:
                ret = EXTI_INT1_setInterruptHandler(int_obj->EXTI_Handler);
                break;
            case EXTI_INT2:
                ret = EXTI_INT2_setInterruptHandler(int_obj->EXTI_Handler);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;    
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
static Std_ReturnType EXTI_RBx_priority_init(const EXTI_RBx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->priority)
        {
            case PRIORITY_HIGH:
                INTERRUPT_PRIORITY_ENABLE();
                INTERRUPT_GIEH_ENABLE();
                EXTI_RBx_PRIORITY_HIGH();
                break;
            case PRIORITY_LOW:
                INTERRUPT_PRIORITY_ENABLE();
                INTERRUPT_GIEL_ENABLE();
                EXTI_RBx_PRIORITY_LOW();
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;    
}
#endif
/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_RBx_pin_init(const EXTI_RBx_t* int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_init(&(int_obj->mcu_pin));
    }
    return ret;    
}

/**
 * 
 * @param int_obj : Pointer to External Interrupt pin configuration.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType EXTI_RBx_setInterruptHandler(const EXTI_RBx_t* int_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->mcu_pin.pin)
        {
            case PIN4_INDEX:
                RB4_INTERRUPT_HIGH_HANDLER = int_obj->EXTI_HIGH_Handler;
                RB4_INTERRUPT_LOW_HANDLER = int_obj->EXTI_LOW_Handler;
                break;
            case PIN5_INDEX:
                RB5_INTERRUPT_HIGH_HANDLER = int_obj->EXTI_HIGH_Handler;
                RB5_INTERRUPT_LOW_HANDLER = int_obj->EXTI_LOW_Handler;
                break;
            case PIN6_INDEX:
                RB6_INTERRUPT_HIGH_HANDLER = int_obj->EXTI_HIGH_Handler;
                RB6_INTERRUPT_LOW_HANDLER = int_obj->EXTI_LOW_Handler;
                break;
            case PIN7_INDEX:
                RB7_INTERRUPT_HIGH_HANDLER = int_obj->EXTI_HIGH_Handler;
                RB7_INTERRUPT_LOW_HANDLER = int_obj->EXTI_LOW_Handler;
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;  
}