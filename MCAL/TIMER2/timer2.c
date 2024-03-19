/* 
 * File:   timer2.h
 * Author: Mostafa Asaad
 *
 * Created on February 2, 2024, 11:26 PM
 */
/* --------------- Section : Includes --------------- */
#include "timer2.h"
/* --------------- Section : Global Variables --------------- */
#if TMR2_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t TMR2_interrupt_handler = NULL;
#endif
static uint8_t g_preloaded_value = ZERO_INIT;

/*---------------  Section: Function Definitions --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer2 object.
 * @Brief   A software interface initializes an object of timer 2 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_init(const Timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer2 Module */  
        TMR2_MODULE_DISABLE();
        
        /* 2. Configure the Prescaler Assignment and Rate */
        TMR2_PRESCALER_SET_RATIO(_timer->prescaler_value);
        
        /* 3. Configure the postscaler Assignment and Rate */
        TMR2_POSTSCALER_SET_RATIO(_timer->postscaler_value);
        
        /* 4. Configure The Interrupts */
#if TMR2_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        // 1- Enable Global & Peripheral Interrupts
        INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
        INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
        // 2- Enable The priority.
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        // 3- Assign the Specified priority. 
        switch (_timer -> priority)
        {
            case PRIORITY_HIGH : INTI_TMR2_INTERRUPT_PRIORITY_HIGH();
                            break;
            case PRIORITY_LOW : INTI_TMR2_INTERRUPT_PRIORITY_LOW();
                            break;
            default : INTI_TMR2_INTERRUPT_PRIORITY_HIGH();
                            break;                
        }
#endif
        // 4- Clear The Timer1 interrupt flag & Enable its interrupt.
        INTI_TMR2_CLR_FLAG();
        INTI_TMR2_INTERRRUPT_ENABLE();
        // 5- Assign the interrupt handler.
        TMR2_interrupt_handler = _timer->TMR2_INTERRUPT_HANDLER;
#endif
        
        /* 5. Write the preloaded value */
        g_preloaded_value = _timer->timer2_preloaded_value;
        TMR2_WRITE(g_preloaded_value);
        
        /* 6. Enable the timer2 module */
        TMR2_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @Brief A software interface deInitializes an object of timer 2 module.
 * @param _timer : A pointer to a Timer2 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_deInit(const Timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer2 Module */
        TMR2_MODULE_DISABLE();
        /* 2. Disable The timer1 interrupt */
        INTI_TMR2_INTERRRUPT_DISABLE();
    }
    return ret;
}

/**
 * 
 * @Brief  A software interface writes a value to the timer 2 register.  
 * @param _timer : A pointer to a Timer2 object.
 * @param _val : The value to be written into the timer 2 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_write_value(const Timer2_t *_timer, uint8_t _val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2_WRITE(_val);
    }
    return ret;
}

/**
 * 
 * @Brief : A software interface Reads the content of the timer 2 module register.
 * @param _timer : A pointer to a Timer2 object.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_read_value(const Timer2_t *_timer, uint8_t *_val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer || NULL == _val)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *_val = TMR2_READ();
    }
    return ret;
}

/**
 * @brief : Timer2 Module Interrupt Handler.
 */
void INTI_TMR2_ISR (void)
{
    /* 1. Clear the Interrupt Flag */
    INTI_TMR2_CLR_FLAG();
    
    /* 2. ReWrite The timer1 module with preloaded value */
    TMR2_WRITE(g_preloaded_value);
    
    /* 3. Call the ISR */
    if (TMR2_interrupt_handler)
    {
        TMR2_interrupt_handler();
    }
    else
    { /* Nothing */}
}