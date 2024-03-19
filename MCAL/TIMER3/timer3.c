/* 
 * File:   timer3.c
 * Author: Mostafa Asaad
 *
 * Created on February 4, 2024, 12:59 PM
 */
/* --------------- Section : Includes --------------- */
#include "timer3.h"
/* --------------- Section : Global Variables --------------- */
#if TMR3_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t TMR3_interrupt_handler = NULL;
#endif
static uint16_t g_preloaded_value = ZERO_INIT;
/*---------------  Section: Function Definitions --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer3 object.
 * @Brief   A software interface initializes an object of timer 3 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_init(const Timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer 3 Module */
        TMR3_MODULE_DISABLE();
        
        /* 2. Configure the module mode */
        switch (_timer->timer3_mode)
        {
            case TMR3_TIMER_MODE : TMR3_INTERNAL_CLK_MODE();
                            break;
            case TMR3_COUNTER_MODE : 
                TMR3_EXTERNEL_CLK_MODE();
                switch (_timer->timer3_counter_synch_mode)
                {
                    case TMR3_COUNTER_SYNCH: TMR3_COUNTER_SET_SYNCH();
                                        break;
                    case TMR3_COUNTER_ASYNCH: TMR3_COUNTER_SET_ASYNCH();
                                        break;
                    default : /* Nothing */
                                        break;
                }
                
                break;
            default : TMR3_INTERNAL_CLK_MODE();
                            break;
        }
        
        /* 3. Configure the Prescaler Assignment and Rate */
        TMR3_PRESCALER_SET_RATIO(_timer->prescaler_value);
        
        /* 4. Configure the timer1 r/w register size */
        switch (_timer->timer3_rw_mode)
        {
            case TMR3_RW_REG_MODE_8BIT : TMR3_RW_SET_MODE_8BIT();
                                    break;
            case TMR3_RW_REG_MODE_16BIT : TMR3_RW_SET_MODE_16BIT();
                                    break;
            default : TMR3_RW_SET_MODE_16BIT();
                                    break;
                
        }
        
        /* 5. Configure The Interrupts */
#if TMR3_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        // 1- Enable Global & Peripheral Interrupts
        INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
        INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
        // 2- Enable The priority.
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        // 3- Assign the Specified priority. 
        switch (_timer->priority)
        {
            case PRIORITY_HIGH : INTI_TMR3_INTERRUPT_PRIORITY_HIGH();
                            break;
            case PRIORITY_LOW : INTI_TMR3_INTERRUPT_PRIORITY_LOW();
                            break;
            default : INTI_TMR3_INTERRUPT_PRIORITY_HIGH();
                                    break;
        }
#endif
        // 4- Clear The Timer 3 interrupt flag & Enable its interrupt
        INTI_TMR3_CLR_FLAG();
        INTI_TMR3_INTERRRUPT_ENABLE();
        // 5- Assign the interrupt handler.
        TMR3_interrupt_handler = _timer->TMR3_INTERRUPT_HANDLER;
#endif
        
        /* 6. Write the preloaded value */
        g_preloaded_value = _timer->timer3_preloaded_value;
        TMR3_WRITE(g_preloaded_value);
        
        /* 7. Enable the timer 3 module */
        TMR3_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @Brief A software interface deInitializes an object of timer 3 module.
 * @param _timer : A pointer to a Timer3 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_deInit(const Timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer 3 Module */
        TMR3_MODULE_DISABLE();
        
        /* 2. Disable The timer 3 interrupt */
        INTI_TMR3_INTERRRUPT_DISABLE();
    }
    return ret;   
}

/**
 * 
 * @Brief  A software interface writes a value to the timer 3 register.  
 * @param _timer : A pointer to a Timer3 object.
 * @param _val : The value to be written into the timer 3 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_write_value(const Timer3_t *_timer, uint16_t _val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3_WRITE(_val);
    }
    return ret;  
}

/**
 * 
 * @Brief : A software interface Reads the content of the timer 3 module register.
 * @param _timer : A pointer to a Timer3 object.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_read_value(const Timer3_t *_timer, uint16_t *_val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer || NULL == _val)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *_val = TMR3_READ();
    }
    return ret;  
}
/* -------------- Section : Helper Functions -------------- */
/**
 * @brief : Timer 3 Module Interrupt Handler.
 */
void INTI_TMR3_ISR (void)
{
    /* 1. Clear the Interrupt Flag */
    INTI_TMR3_CLR_FLAG();
    
    /* 2. ReWrite The timer1 module with preloaded value */
    TMR3_WRITE(g_preloaded_value);
    
    /* 3. Call the ISR */
    if (TMR3_interrupt_handler)
    {
        TMR3_interrupt_handler();
    }
    else
    { /* Nothing */}
}