/* 
 * File:   timer3.h
 * Author: Mostafa Asaad
 *
 * Created on February 4, 2024, 12:59 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/* --------------- Section : Includes --------------- */
#include "../compiler.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */
#define TMR3_TIMER_MODE             STD_LOW
#define TMR3_COUNTER_MODE           STD_HIGH

#define TMR3_COUNTER_RISING_EDGE    STD_HIGH

#define TMR3_16_BIT_MODE            STD_HIGH

#define TMR3_COUNTER_SYNCH          STD_LOW
#define TMR3_COUNTER_ASYNCH         STD_HIGH

#define TMR3_RW_REG_MODE_8BIT       STD_LOW
#define TMR3_RW_REG_MODE_16BIT      STD_HIGH
/* --------------- Section: Macro Functions Declarations --------------- */
/*
 * @brief : The Timer3 Enabling configuration.
 * @note  : (T3CON) Timer3 Control Register bit <0> => (TMR3ON)
 *          1 = Enables Timer3
 *          0 = Stops   Timer3
 */
#define TMR3_MODULE_ENABLE()        (T3CONbits.TMR3ON = STD_ENABLE)
#define TMR3_MODULE_DISABLE()       (T3CONbits.TMR3ON = STD_DISABLE)

/*
 * @brief : The clock source configurations for Timer3 module.
 * @note  : (T3CON) Timer3 Control Register bit<1> => (TMR3CS) Clock Source Select.
 *          1 = External clock input from Timer1 oscillator or T13CKI 
 *              (on the rising edge after the first falling edge)
 *          0 = Internal clock (FOSC/4)
 */
#define TMR3_INTERNAL_CLK_MODE()    (T3CONbits.TMR3CS = TMR3_TIMER_MODE)
#define TMR3_EXTERNEL_CLK_MODE()    (T3CONbits.TMR3CS = TMR3_COUNTER_MODE)

/*
 * @brief : Timer3 External Clock Input Synchronization Control bit.
 * @note  : (T3CON) Timer3 Control Register bit <2> => (T3SYNC).
            (Not usable if the device clock comes from Timer1/Timer3.)
 *          => When TMR3CS = 1:
 *              1 = Do not synchronize external clock input
 *              0 = Synchronize external clock input
 *          => When TMR3CS = 0:
 *              This bit is ignored. 
 *              Timer3 uses the internal clock when TMR3CS = 0.
 */ 
#define TMR3_COUNTER_SET_SYNCH()    (T3CONbits.T3SYNC = TMR3_COUNTER_SYNCH)
#define TMR3_COUNTER_SET_ASYNCH()   (T3CONbits.T3SYNC = TMR3_COUNTER_ASYNCH)

/*
 * @brief : The Prescaler Ratio Configuration
 * @note  : (T3CON) Timer3 Control Register bits <4> & <5> 
 *          11 = 1:8 Prescale value
 *          10 = 1:4 Prescale value
 *          01 = 1:2 Prescale value
 *          00 = 1:1 Prescale value
 */
#define TMR3_PRESCALER_SET_RATIO(_R_)    (T3CONbits.T3CKPS = _R_)

/*
 * @brief : The Timer3 16-Bit Read/Write Mode Configuration.
 * @note  : (T3CON) Timer3 Control Register bit <7> => (RD16).
 *          1 = Enables register read/write of TImer3 in one 16-bit operation
 *          0 = Enables register read/write of Timer3 in two 8-bit operations
 */
#define TMR3_RW_SET_MODE_8BIT()         (T3CONbits.RD16 = TMR3_RW_REG_MODE_8BIT)
#define TMR3_RW_SET_MODE_16BIT()        (T3CONbits.RD16 = TMR3_RW_REG_MODE_16BIT)
/*
 * @brief : The Timer 3 Reading and Writing into TMR3 Register.
 * @note  : (TMR3) Timer3 Register.
 */
#define TMR3_WRITE(_D_)                 (TMR3 = _D_)
#define TMR3_READ()                     (TMR3)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
    TMR3_PRESCALAR_RATIO_1 = 0b00,
    TMR3_PRESCALAR_RATIO_2 = 0b01,  
    TMR3_PRESCALAR_RATIO_4 = 0b10,  
    TMR3_PRESCALAR_RATIO_8 = 0b11
} timer3_prescaler_ratio_t;

typedef struct
{
#if TMR3_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /**
     * A pointer to the ISR for timer3.
     */
    interrupt_handler_t TMR3_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /**
     * The priority of the timer3 interrupt.
     *          (PRIORITY_HIGH or PRIORITY_LOW)
     */
    interrupt_priority_t priority;
#endif
#endif 
    /**
     * A uint16_t value to be loaded initially in the timer3 Register.
     */
    uint16_t timer3_preloaded_value;
    /**
     * The prescaler ratio.
     *      ex => (TMR3_PRESCALAR_RATIO_2)
     */
    timer3_prescaler_ratio_t prescaler_value;
    /**
     * The timer3 operating mode
     *      (TMR3_TIMER_MODE or TMR3_COUNTER_MODE)
     */
    uint8_t timer3_mode                 :1;
    /**
     * The Synchronization mode for timer3 if it's
     *                                 assigned to operate in Counter mode.
     *      (TMR3_COUNTER_SYNCH or TMR3_COUNTER_ASYNCH )
     */
    uint8_t timer3_counter_synch_mode   :1;
    /**
     * (TMR3_RW_REG_MODE_8BIT or TMR3_RW_REG_MODE_16BIT).
     */
    uint8_t timer3_rw_mode              :1;
    /**
     * Five Reserved Bits.
     * (Unimplemented).
     */
    uint8_t timer3_reserved             :5;
    
} Timer3_t;

/*---------------  Section: Function Declarations --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer3 object.
 * @Brief   A software interface initializes an object of timer 3 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_init(const Timer3_t *_timer);

/**
 * 
 * @Brief A software interface deInitializes an object of timer 3 module.
 * @param _timer : A pointer to a Timer3 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_deInit(const Timer3_t *_timer);

/**
 * 
 * @Brief  A software interface writes a value to the timer 3 register.  
 * @param _timer : A pointer to a Timer3 object.
 * @param _val : The value to be written into the timer 3 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_write_value(const Timer3_t *_timer, uint16_t _val);

/**
 * 
 * @Brief : A software interface Reads the content of the timer 3 module register.
 * @param _timer : A pointer to a Timer3 object.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer3_read_value(const Timer3_t *_timer, uint16_t *_val);

#endif	/* TIMER3_H */
