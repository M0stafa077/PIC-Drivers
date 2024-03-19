/* 
 * File:   timer0.h
 * Author: Mostafa Asaad
 *
 * Created on January 31, 2024, 1:18 PM
 */
/* --------------- Section : Includes --------------- */
#include "timer0.h"
/* --------------- Section : Global Variables --------------- */
#if TMR0_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t TMR0_interrupt_handler = NULL;
#endif
static uint16_t g_preloaded_value = ZERO_INIT;

/*---------------  Section: Function Definitions --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer0 object.
 * @brief : A software interface initializes an object of timer 0 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer0_init(const Timer0_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer0 Module */
        TMR0_MODULE_DISABLE();
        
        /* 2. Configure the module mode */
        switch (_timer->timer0_mode)
        {
            case TMR0_TIMER_MODE : TMR0_INTERNAL_CLK_MODE(); 
                                break;
            case TMR0_COUNTER_MODE: 
                TMR0_EXTERNEL_CLK_MODE(); 
                switch (_timer->tmr0_counter_edge_select)
                {
                    case TMR0_COUNTER_RISING_EDGE : TMR0_SELECT_RISING_EDGE();
                                        break;
                    case TMR0_COUNTER_FALLING_EDGE : TMR0_SELECT_FALLING_EDGE();
                                        break;
                    default : TMR0_SELECT_RISING_EDGE();
                          break;
                }
                break;
            default : TMR0_INTERNAL_CLK_MODE(); 
                  break;
        }
        
        /* 3. Configure the Prescaler Assignment and Rate */
        switch (_timer->prescaler_enable)
        {
            case TMR0_PRESCALER_ENABLE : 
                TMR0_PRESCALAR_ASSIGN();
                TMR0_PRESCALER_SET_RATIO(_timer->prescaler_value);
                break;
            case TMR0_PRESCALER_DISABLE : 
                TMR0_PRESCALAR_NO_ASSIGN();
                break;
        }
        
        /* 4. Configure the timer0 register size */
        switch (_timer->tmr0_register_size)
        {
            case TMR0_8_BIT_MODE :
                TMR0_SELECT_8BIT_MODE();
                break;
            case TMR0_16_BIT_MODE :
                TMR0_SELECT_16BIT_MODE();
                break;
        }
        
        /* 5. Configure The Interrupts */
#if TMR0_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        // 1- Enable Global & Peripheral Interrupts
        INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
        INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
        // 2- Enable The priority.
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        // 3-Assign the Specified priority. 
        switch (_timer->priority)
        {
            case PRIORITY_HIGH : INTI_TMR0_INTERRUPT_PRIORITY_HIGH();
                            break;
            case PRIORITY_LOW : INTI_TMR0_INTERRUPT_PRIORITY_LOW();
                            break;
            default : INTI_TMR0_INTERRUPT_PRIORITY_HIGH();
                            break;                
        }
#endif
        // 4- Clear The Timer0 interrupt flag & Enable its interrupt.
        INTI_TMR0_CLR_FLAG();
        INTI_TMR0_INTERRRUPT_ENABLE();
        TMR0_interrupt_handler = _timer->TMR0_INTERRUPT_HANDLER;
#endif
     
        /* 6. Write the preloaded value */
        TMR0_WRITE_HIGH_BYTE((_timer->timer0_preloaded_value) >> 8);
        TMR0_WRITE_LOW_BYTE((uint8_t) (_timer->timer0_preloaded_value));
        g_preloaded_value = _timer->timer0_preloaded_value;
        /* 7. Enable the timer0 module */
        TMR0_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer0 object.
 * @brief : A software interface deInitializes an object of timer 0 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer0_deInit(const Timer0_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable Timer0 Module */
        TMR0_MODULE_DISABLE();
        /* 2. Disable The timer0 interrupt */
        INTI_TMR0_INTERRRUPT_DISABLE();   
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer0 object.
 * @brief : A software interface writes a value to the timer 0 register.  
 * @param _val : The value to be written into the timer 0 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer0_write_value(const Timer0_t *_timer, uint16_t _val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0_WRITE_HIGH_BYTE((_val) >> 8);
        TMR0_WRITE_LOW_BYTE((uint8_t) (_val));
    }
    return ret;
}

/**
 * 
 * @param _timer : A pointer to a Timer0 object.
 * @brief : A software interface Reads the content of the timer 0 module register.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer0_read_value(const Timer0_t *_timer, uint16_t *_val)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8_t l_tmr0_low_byte = ZERO_INIT, l_tmr0_high_byte = ZERO_INIT;
        l_tmr0_low_byte = TMR0_READ_LOW_BYTE();
        l_tmr0_high_byte = TMR0_READ_HIGH_BYTE();
        *_val = (uint16_t)((l_tmr0_high_byte << 8) + (l_tmr0_low_byte));
    }
    return ret;
}

/**
 * @brief : Timer 0 Module Interrupt Handler.
 */
void INTI_TMR0_ISR(void)
{
    /* 1. Clear the interrupt flag */
    INTI_TMR0_CLR_FLAG();
    
    /* 2. ReWrite The timer0 module with preloaded value */
    TMR0_WRITE_HIGH_BYTE( (g_preloaded_value) >> 8);
    TMR0_WRITE_LOW_BYTE ( (uint8_t) (g_preloaded_value));
    
    /* 2. Call The ISR */
    if (TMR0_interrupt_handler)
    {
        TMR0_interrupt_handler(); 
    }
    else
    { /* Nothing */ }
}