/* 
 * File:   timer1.h
 * Author: Mostafa Asaad
 *
 * Created on February 1, 2024, 2:45 PM
 */
/* --------------- Section : Includes --------------- */
#include "timer1.h"
/* --------------- Section : Global Variables --------------- */
#if TMR1_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t TMR1_interrupt_handler = NULL;
#endif
static uint16_t g_preloaded_value = ZERO_INIT;

/*---------------  Section: Function Definitions --------------- */
/**
 * 
 * @Brief  A software interface initializes an object of timer 1 module.
 * @param _timer : A pointer to a Timer1 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_init(const Timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer 1 Module */  
        TMR1_MODULE_DISABLE();
        
        /* 2. Configure the module mode */
        switch (_timer->timer1_mode)
        {
            case TMR1_TIMER_MODE : TMR1_INTERNAL_CLK_MODE();
                                break;
            case TMR1_COUNTER_MODE: 
                TMR1_EXTERNEL_CLK_MODE();
                switch (_timer->timer1_counter_synch_mode)
                {
                    case TMR1_COUNTER_SYNCH : TMR1_COUNTER_SET_SYNCH();
                                            break;  
                    case TMR1_COUNTER_ASYNCH : TMR1_COUNTER_SET_ASYNCH();
                                            break;
                    default : /* Nothing*/
                                            break;
                }
                break;
            default : TMR1_INTERNAL_CLK_MODE();
                  break;                
        }
        
        /* 3. Configure the Prescaler Assignment and Rate */
        TMR1_PRESCALER_SET_RATIO(_timer->prescaler_value);
        
        /* 4. Configure the timer1 r/w register size */
        switch (_timer->timer1_rw_mode)
        {
            case TMR1_RW_REG_MODE_8BIT : TMR1_RW_SET_MODE_8BIT();
                                    break;
            case TMR1_RW_REG_MODE_16BIT : TMR1_RW_SET_MODE_16BIT();
                                    break;
            default : TMR1_RW_SET_MODE_16BIT();
                                    break;            
        }
        
        /* 5. Configure The Interrupts */
#if TMR1_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        // 1- Enable Global & Peripheral Interrupts
        INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
        INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
        // 2- Enable The priority.
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
            // 3- Assign the Specified priority. 
        switch (_timer->priority)
        {
            case PRIORITY_HIGH : INTI_TMR1_INTERRUPT_PRIORITY_HIGH();
                            break;
            case PRIORITY_LOW : INTI_TMR1_INTERRUPT_PRIORITY_LOW();
                            break;
            default : INTI_TMR1_INTERRUPT_PRIORITY_HIGH();
                            break;                
        }
#endif
        // 4- Clear The Timer1 interrupt flag & Enable its interrupt.
        INTI_TMR1_CLR_FLAG();
        INTI_TMR1_INTERRRUPT_ENABLE();
        // 5- Assign the interrupt handler.
        TMR1_interrupt_handler = _timer->TMR1_INTERRUPT_HANDLER;
#endif
        
        /* 6. Write the preloaded value */
        g_preloaded_value = _timer->timer1_preloaded_value;
        TMR1_WRITE(g_preloaded_value);
        /* 7. Enable the timer1 module */
        TMR1_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer1 object.
 * @brief : A software interface deInitializes an object of timer 1 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_deInit(const Timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer1 Module */
        TMR1_MODULE_DISABLE();
        /* 2. Disable The timer1 interrupt */
        INTI_TMR1_INTERRRUPT_DISABLE();   
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer1 object.
 * @brief : A software interface writes a value to the timer 1 register.  
 * @param _val : The value to be written into the timer 1 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_write_value(const Timer1_t *_timer, uint16_t _val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1_WRITE(_val);
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer1 object.
 * @brief : A software interface Reads the content of the timer 1 module register.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_read_value(const Timer1_t *_timer, uint16_t *_val)
{
    Std_ReturnType ret = E_OK;
    if ((NULL == _timer) || (NULL == _val))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *_val = TMR1_READ();
    }
    return ret;
}

/**
 * @brief : Timer1 Module Interrupt Handler.
 */
void INTI_TMR1_ISR (void)
{
    /* 1. Clear the Interrupt Flag */
    INTI_TMR1_CLR_FLAG();
    
    /* 2. ReWrite The timer1 module with preloaded value */
    TMR1_WRITE(g_preloaded_value);
    
    /* 3. Call the ISR */
    if (TMR1_interrupt_handler)
    {
        TMR1_interrupt_handler();
    }
    else
    { /* Nothing */}
}