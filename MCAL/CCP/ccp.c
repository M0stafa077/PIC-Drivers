/* 
 * File:   ccp_cfg.h
 * Author: Mostafa Asaad
 *
 * Created on February 12, 2024, 5:29 PM
 */
/* --------------- Section : Includes --------------- */
#include "ccp.h"

/* --------------- Section : Global Variables --------------- */
#if (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE)
static interrupt_handler_t ccp1_interrupt_handler = NULL;
#endif

#if (CCP2_INTERRUPT_FEATURE==INTERRUPT_ENABLE)
static interrupt_handler_t ccp2_interrupt_handler = NULL;
#endif

/*---------------  Section: Helper Function Declarations --------------- */

/*
 * A software interface initializes the chosen mode
 * for the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return 
 */
static Std_ReturnType ccp_Mode_Init(const ccp_t *ccp_obj);

/**
 * A software interface configures the interrupt feature
 * for the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
static void CCP_Configure_Interrupts(const ccp_t *ccp_obj);

/**
 * A software interface initializes the capture mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
static void CCP_Capture_Mode_Init(const ccp_t *ccp_obj);
#endif

/**
 * A software interface initializes the compare mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
static void CCP_Compare_Mode_Init(const ccp_t *ccp_obj);
#endif

/**
 * A software interface initializes the pwm mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
static void CCP_PWM_Mode_Init(const ccp_t *ccp_obj);
#endif
/*---------------  Section: Function Definitions --------------- */
/**
 * A software interface initializes the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Init(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable the ccp module */
        switch (ccp_obj -> ccp_module_select)
        {
            case CCP1_MODULE : CCP1_MODULE_SET_DISABLE();
                            break;
            case CCP2_MODULE : CCP2_MODULE_SET_DISABLE();
                            break;
            default : ret = E_NOT_OK;
                  break;
        }
        
        /* 2. Select the mode of the ccp module */
        ret = ccp_Mode_Init(ccp_obj);
        
        /* 3. Configure the pin */
        ret = gpio_pin_initialize(&(ccp_obj -> pin));
        
        /* 4. Configure the interrupt */
        CCP_Configure_Interrupts(ccp_obj);
        
    }
    return ret;
}

/**
 * A software Interface deInitializes the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable the module */
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : CCP1_MODULE_SET_DISABLE();
                            break;
            case CCP2_MODULE : CCP2_MODULE_SET_DISABLE();
                            break;
            default : ret = E_NOT_OK;
                   break;
        }
        
        /* 2. Disable the module interrupt */
#if (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE) || (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE)
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : INTI_CCP1_INTERRRUPT_DISABLE();
                            break;
            case CCP2_MODULE : INTI_CCP2_INTERRRUPT_DISABLE();
                            break;
            default : ret = E_NOT_OK;
                   break;
        }
#endif
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
/**
 * A software Interface checks for the capture status.(Ready or Not)
 * @param ccp_obj : A pointer to a ccp module object.
 * @param capture_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Capture_Is_Ready(const ccp_t *ccp_obj, uint8_t *capture_status)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj || NULL == capture_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : 
                *capture_status = PIR1bits.CCP1IF;
                INTI_CCP1_CLR_FLAG();
                break;
            case CCP2_MODULE : 
                *capture_status = PIR2bits.CCP2IF;
                INTI_CCP2_CLR_FLAG();
                break;
            default : ret = E_NOT_OK;
                  break;
        }
    }
    return ret;
}
/**
 * A software Interface reads the value of the capture mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param capture_value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Capture_Read_Value(const ccp_t *ccp_obj, uint16_t *capture_value)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj || NULL == capture_value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ccp_period_reg_t l_temp_cap_value = { 0 };
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : 
                l_temp_cap_value.cppr_low  = CCPR1L;
                l_temp_cap_value.cppr_high = CCPR1H;
                *capture_value = l_temp_cap_value.ccpr_16bit;
                break;
            case CCP2_MODULE : 
                l_temp_cap_value.cppr_low  = CCPR2L;
                l_temp_cap_value.cppr_high = CCPR2H;
                *capture_value = l_temp_cap_value.ccpr_16bit;
                break;
            default : ret = E_NOT_OK;
                  break;
        }   
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
/**
 * A software Interface checks if the comparing is completed or not.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param compare_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Compare_IsCompleted(const ccp_t *ccp_obj, uint8_t *compare_status)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj || NULL == compare_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : 
                *compare_status = PIR1bits.CCP1IF;
                INTI_CCP1_CLR_FLAG();
                break;
            case CCP2_MODULE : 
                *compare_status = PIR2bits.CCP2IF;
                INTI_CCP2_CLR_FLAG();
                break;
            default : ret = E_NOT_OK;
                  break;
        }
    }
    return ret;
}
/**
 * A software Interface sets the value for the comparison.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param compare_value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Compare_SetValue(const ccp_t *ccp_obj, uint16_t compare_value)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ccp_period_reg_t l_temp_cap_value = { 0 }; 
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : 
                l_temp_cap_value.ccpr_16bit = compare_value; 
                CCPR1L = l_temp_cap_value.cppr_low;
                CCPR1H = l_temp_cap_value.cppr_high;
                break;
            case CCP2_MODULE : 
                l_temp_cap_value.ccpr_16bit = compare_value; 
                CCPR2L = l_temp_cap_value.cppr_low;
                CCPR2H = l_temp_cap_value.cppr_high;
                break;
                break;
            default : ret = E_NOT_OK;
                  break;
        }
    }
    return ret;  
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
/**
 * A software Interface sets the duty cycle for the ccp module in pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param dutyCycle
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_SetDutyCycle(const ccp_t *ccp_obj, const uint8_t dutyCycle)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint16_t l_temp_dutyCycle = 0;
        l_temp_dutyCycle = (uint16_t)((float)4 * ((float)PR2 + 1.0) * ((float)dutyCycle / 100.0));
        
        switch (ccp_obj -> ccp_module_select)
        {
            case CCP1_MODULE :
                CCP1CONbits.DC1B = (uint8_t)(l_temp_dutyCycle & 0x0003);
                CCPR1L = (uint8_t)(l_temp_dutyCycle >> 2);
                break; 
            case CCP2_MODULE :
                CCP2CONbits.DC2B = (uint8_t)(l_temp_dutyCycle & 0x0003);
                CCPR2L = (uint8_t)(l_temp_dutyCycle >> 2);
                break; 
            default : 
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
/**
 * A software Interface starts the pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (ccp_obj -> ccp_module_select)
        {
            case CCP1_MODULE : CCP1_SET_MODE(CCP_PWM_MODE);
                            break; 
            case CCP2_MODULE : CCP2_SET_MODE(CCP_PWM_MODE);
                            break; 
            default : ret = E_NOT_OK;
                  break;
        }
    }
    return ret;
}
/**
 * A software Interface stops the pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (ccp_obj -> ccp_module_select)
        {
            case CCP1_MODULE : CCP1_MODULE_SET_DISABLE();
                break; 
            case CCP2_MODULE : CCP2_MODULE_SET_DISABLE();
                break; 
            default : ret = E_NOT_OK;
                  break;
        }
    }
    return ret; 
}
#endif

/*---------------  Section: Helper Function Definitions --------------- */
static Std_ReturnType ccp_Mode_Init(const ccp_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    switch (ccp_obj -> ccp_mode)
    {
        case CCP_MODE_CAPTURE : 
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
            CCP_Capture_Mode_Init(ccp_obj);
#endif
            break;
        case CCP_MODE_COMPARE : 
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
            CCP_Compare_Mode_Init(ccp_obj);
#endif
            break;
        case CCP_MODE_PWM : 
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
            CCP_PWM_Mode_Init(ccp_obj);
#endif
            break;
        default : ret = E_NOT_OK;
            break;
        }
    return ret;
}

/**
 * A software interface configures the interrupt feature
 * for the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
static void CCP_Configure_Interrupts(const ccp_t *ccp_obj)
{
#if (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE) || (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE)
    // 1- Enable Global & Peripheral Interrupts
    INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
    INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    // 2- Enable The priority.
    INTERRUPT_PRIORITY_ENABLE();
    // 3- Assign the Specified priority. 
    switch (ccp_obj -> ccp_module_select)
    {
        case CCP1_MODULE :
            switch (ccp_obj -> ccp_interrupt_priority)
            {
                case PRIORITY_HIGH : INTI_CCP1_INTERRUPT_PRIORITY_HIGH();
                                break;
                case PRIORITY_LOW : INTI_CCP1_INTERRUPT_PRIORITY_LOW();
                                break;
                default : INTI_CCP1_INTERRUPT_PRIORITY_HIGH();
                    break;
            }
            break;
            
        case CCP2_MODULE :
            switch (ccp_obj -> ccp_interrupt_priority)
            {
                case PRIORITY_HIGH : INTI_CCP2_INTERRUPT_PRIORITY_HIGH();
                                break;
                case PRIORITY_LOW : INTI_CCP2_INTERRUPT_PRIORITY_LOW();
                                break;
                default : INTI_CCP2_INTERRUPT_PRIORITY_HIGH();
                      break;
            }
            break;
                
            default : /* Nothing */;
                  break;
        }
#endif
        // 4- Clear The interrupt flag & Enable its interrupt.
        switch (ccp_obj->ccp_module_select)
        {
            case CCP1_MODULE : 
                INTI_CCP1_CLR_FLAG();
                INTI_CCP1_INTERRRUPT_ENABLE();
                break;
            case CCP2_MODULE : 
                INTI_CCP2_CLR_FLAG();
                INTI_CCP2_INTERRRUPT_ENABLE();
                break;
            default : /* Nothing */;
                  break;
        }
        // 5- Assign the interrupt handler.
        switch(ccp_obj -> ccp_module_select)
        {
            case CCP1_MODULE : ccp1_interrupt_handler = ccp_obj -> ccp_interrupt_handler;
                            break;
            case CCP2_MODULE : ccp2_interrupt_handler = ccp_obj -> ccp_interrupt_handler;
                            break;
            default : /* Nothing */;
                  break;
        }
#endif 
}

/**
 * A software interface initializes the capture mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
static void CCP_Capture_Mode_Init(const ccp_t *ccp_obj)
{
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
    switch(ccp_obj->ccp_capture_config)
    {
        case CCP_CAPTURE_EVERY_FALLING_EDGE :
            switch (ccp_obj->ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_CAPTURE_EVERY_FALLING_EDGE);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_CAPTURE_EVERY_FALLING_EDGE);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
        case CCP_CAPTURE_EVERY_RISING_EDGE :
            switch (ccp_obj->ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_CAPTURE_EVERY_RISING_EDGE);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_CAPTURE_EVERY_RISING_EDGE);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
        case CCP_CAPTURE_4TH_RISING_EDGE :
            switch (ccp_obj->ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_CAPTURE_4TH_RISING_EDGE);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_CAPTURE_4TH_RISING_EDGE);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
        case CCP_CAPTURE_16TH_RISING_EDGE :
            switch (ccp_obj->ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_CAPTURE_16TH_RISING_EDGE);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_CAPTURE_16TH_RISING_EDGE);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
        default : /* Nothing */;
            break;
    }
    
    /* Configure which timer operate with each ccp module */
    switch (ccp_obj->ccp_capture_timer)
    {
        case CCP1_CCP2_TMR3 : 
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 1;
            break;
        case CCP1_TMR1_CCP2_TMR3 :
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
            break;
        case CCP1_CCP2_TMR1 :
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
            break;
        default :   
            /* Nothing */
            break;
    }
#endif 
}

/**
 * A software interface initializes the compare mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
static void CCP_Compare_Mode_Init(const ccp_t *ccp_obj)
{
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
    switch (ccp_obj -> ccp_compare_config)
    {
        case CCP_COMPARE_PIN_TOGGLE_ON_MATCH :
            switch (ccp_obj -> ccp_module_select)
            {
                case CCP1_MODULE : 
                    CCP1_SET_MODE(CCP_COMPARE_PIN_TOGGLE_ON_MATCH);
                    INTI_CCP1_CLR_FLAG();
                    break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_COMPARE_PIN_TOGGLE_ON_MATCH);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
        case CCP_COMPARE_SET_PIN_LOW :
            switch (ccp_obj -> ccp_module_select)
            {
                case CCP1_MODULE : 
                    CCP1_SET_MODE(CCP_COMPARE_SET_PIN_LOW);
                    INTI_CCP1_CLR_FLAG();
                    break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_COMPARE_SET_PIN_LOW);
                        break;
                default : /* Nothing */;
                    break;
            }
            break;
            
        case CCP_COMPARE_SET_PIN_HIGH :
            switch (ccp_obj -> ccp_module_select)
            {
                case CCP1_MODULE : 
                    CCP1_SET_MODE(CCP_COMPARE_SET_PIN_HIGH);
                    INTI_CCP1_CLR_FLAG();
                    break;
                case CCP2_MODULE : 
                    CCP2_SET_MODE(CCP_COMPARE_SET_PIN_HIGH);
                    INTI_CCP1_CLR_FLAG();
                    break;
                default : /* Nothing */;
                    break;
            }
            break;
        case CCP_COMPARE_SW_INTERRUPT :
            switch (ccp_obj -> ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_COMPARE_SW_INTERRUPT);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_COMPARE_SW_INTERRUPT);
                        break;
                default : /* Nothing */;
                        break;
            }
            break;
        case CCP_COMPARE_GEN_EVENT :
            switch (ccp_obj -> ccp_module_select)
            {
                case CCP1_MODULE : CCP1_SET_MODE(CCP_COMPARE_GEN_EVENT);
                        break;
                case CCP2_MODULE : CCP2_SET_MODE(CCP_COMPARE_GEN_EVENT);
                        break;
                default : /* Nothing */;
                        break;
            }
            break;
    }
    
    /* Configure which timer operate with each ccp module */
    switch (ccp_obj -> ccp_compare_timer)
    {
        case CCP1_CCP2_TMR3 : 
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 1;
            break;
        case CCP1_TMR1_CCP2_TMR3 :
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
            break;
        case CCP1_CCP2_TMR1 :
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
            break;
        default :   
            /* Nothing */
            break;
    }
#endif
}

/**
 * A software interface initializes the PWM mode 
 * in the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 */
static void CCP_PWM_Mode_Init(const ccp_t *ccp_obj)
{
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    switch (ccp_obj->ccp_module_select)
    {
        case CCP1_MODULE : CCP1_SET_MODE(CCP_PWM_MODE);
                        break;
        case CCP2_MODULE : CCP2_SET_MODE(CCP_PWM_MODE);
                        break;
        default : /* Nothing */;
              break;
    }
    /* Initialize PWM frequency */
    PR2 = (uint8_t) ((_XTAL_FREQ / ((ccp_obj -> ccp_pwm_frequency) * 4.0 * (ccp_obj -> timer2_prescaler_value)
            * ccp_obj -> timer2_postscaler_value)) - 1);
#endif
}
/*--------------- Section : The ISRs for CCP1 & CCP2 Modules --------------- */
/**
 * The Interrupt service routine for the ccp 1 module
 */
void CCP1_ISR(void)
{
    /* 1. Clear the interrupt flag */
    INTI_CCP1_CLR_FLAG();
    (PIR1bits.CCP1IF = 0);
    /* 2. Call the ISR */
    if (ccp1_interrupt_handler)
    {
        ccp1_interrupt_handler();
    }
    else
        { /* Nothing */ }
}

/*
 * The Interrupt service routine for the ccp 2 module.
 */
void CCP2_ISR(void)
{
    /* 1. Clear the interrupt flag */
    INTI_CCP2_CLR_FLAG();
    
    /* 2. Call the ISR */
    if (ccp2_interrupt_handler)
    {
        ccp2_interrupt_handler();
    }
    else
        { /* Nothing */ }
}

/*---------------  Section: End Of CCP Module Driver --------------- */
