/* 
 * File:   timer2.h
 * Author: Mostafa Asaad
 *
 * Created on February 2, 2024, 11:26 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H
/* --------------- Section : Includes --------------- */
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */
/*
 * @Brief : The Timer2 Enabling configuration.
 * @note  : (T2CON) Timer1 Control Register bit <2> => (TMR2ON)
 *          1 = Enables Timer2
 *          0 = Stops   Timer2
 */
#define TMR2_MODULE_ENABLE()                (T2CONbits.TMR2ON = STD_ENABLE)
#define TMR2_MODULE_DISABLE()               (T2CONbits.TMR2ON = STD_DISABLE)

/*
 * @Brief : The Prescaler Ratio Configuration
 * @note  : (T2CON) Timer1 Control Register bits <1> & <0> 
 *          00 = Prescaler is 1
 *          01 = Prescaler is 4
 *          1x = Prescaler is 16
 */
#define TMR2_PRESCALER_SET_RATIO(_R_)       (T2CONbits.T2CKPS = _R_)
/*
 * @Brief : The Postscaler Ratio Configuration
 * @note  : (T2CON) Timer1 Control Register bits <3> to <6> 
 *          0000 = 1:1 Postscaler
 *          0001 = 1:2 Postscaler
 *          ?
 *          ?
 *          ?
 *          1111 = 1:16 Postscaler
 */
#define TMR2_POSTSCALER_SET_RATIO(_R_)      (T2CONbits.TOUTPS = _R_)

/*
 * @Brief : The Timer1 Reading and Writing into TMR2 Register.
 * @note  : (TMR2) Timer2 Register.
 */
#define TMR2_WRITE(_D_)                     (TMR2 = _D_)  
#define TMR2_READ()                         (TMR2)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
    TMR2_POSTSCALAR_RATIO_1 = 0,
    TMR2_POSTSCALAR_RATIO_2,  
    TMR2_POSTSCALAR_RATIO_3,  
    TMR2_POSTSCALAR_RATIO_4,  
    TMR2_POSTSCALAR_RATIO_5,  
    TMR2_POSTSCALAR_RATIO_6,  
    TMR2_POSTSCALAR_RATIO_7,  
    TMR2_POSTSCALAR_RATIO_8,
    TMR2_POSTSCALAR_RATIO_9,
    TMR2_POSTSCALAR_RATIO_10,
    TMR2_POSTSCALAR_RATIO_11,
    TMR2_POSTSCALAR_RATIO_12,
    TMR2_POSTSCALAR_RATIO_13,
    TMR2_POSTSCALAR_RATIO_14,
    TMR2_POSTSCALAR_RATIO_15,
    TMR2_POSTSCALAR_RATIO_16
} timer2_postscaler_ratio_t;

typedef enum
{
    TMR2_PRESCALER_RATIO_1 = 0,
    TMR2_PRESCALER_RATIO_4,
    TMR2_PRESCALER_RATIO_16,
} timer2_prescaler_ratio_t;

typedef struct
{
#if TMR1_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /**
     * A pointer to the ISR for timer2.
     */
    interrupt_handler_t TMR2_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /**
     * The priority of the timer2 interrupt.
     *          (PRIORITY_HIGH or PRIORITY_LOW)
     */
    interrupt_priority_t priority;
#endif
#endif 
    /**
     * A uint8_t value to be loaded initially in the timer2 Register.
     */
    uint8_t timer2_preloaded_value;
    /**
     * The post-scaler ratio.
     *      ex => (TMR2_POSTSCALAR_RATIO_15)
     */
    timer2_postscaler_ratio_t postscaler_value;
    /**
     * The prescaler ratio.
     *      ex => (TMR2_PRESCALER_RATIO_4)
     */
    timer2_prescaler_ratio_t prescaler_value;
    
} Timer2_t;
/*---------------  Section: Function Declarations --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer2 object.
 * @Brief   A software interface initializes an object of timer 2 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_init(const Timer2_t *_timer);

/**
 * 
 * @Brief A software interface deInitializes an object of timer 2 module.
 * @param _timer : A pointer to a Timer2 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_deInit(const Timer2_t *_timer);

/**
 * 
 * @Brief  A software interface writes a value to the timer 2 register.  
 * @param _timer : A pointer to a Timer2 object.
 * @param _val : The value to be written into the timer 2 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_write_value(const Timer2_t *_timer, uint8_t _val);

/**
 * 
 * @Brief : A software interface Reads the content of the timer 2 module register.
 * @param _timer : A pointer to a Timer2 object.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer2_read_value(const Timer2_t *_timer, uint8_t *_val);
#endif	/* TIMER2_H */

