/* 
 * File:   timer1.h
 * Author: Mostafa Asaad
 *
 * Created on February 1, 2024, 2:45 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H
/* --------------- Section : Includes --------------- */
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */
#define TMR1_TIMER_MODE             STD_LOW
#define TMR1_COUNTER_MODE           STD_HIGH

#define TMR1_COUNTER_RISING_EDGE    STD_HIGH

#define TMR1_16_BIT_MODE            STD_HIGH

#define TMR1_COUNTER_SYNCH          STD_LOW
#define TMR1_COUNTER_ASYNCH         STD_HIGH

#define TMR1_RW_REG_MODE_8BIT       STD_LOW
#define TMR1_RW_REG_MODE_16BIT      STD_HIGH

#define TMR1_OSC_ENABLE             STD_ENABLE
#define TMR1_OSC_DISABLE            STD_DISABLE
/* --------------- Section: Macro Functions Declarations --------------- */

/*
 * @brief : The Timer1 Enabling configuration.
 * @note  : (T1CON) Timer1 Control Register bit <0> => (TMR1ON)
 *          1 = Enables Timer1
 *          0 = Stops   Timer1
 */
#define TMR1_MODULE_ENABLE()        (T1CONbits.TMR1ON = STD_ENABLE)
#define TMR1_MODULE_DISABLE()       (T1CONbits.TMR1ON = STD_DISABLE)

/*
 * @brief : The clock source configurations for Timer1 module.
 * @note  : (T1CON) Timer1 Control Register bit<1> => (TMR1CS) Clock Source Select.
 *          1 = External clock from pin RC0/T1OSO/T13CKI (on the rising edge)
 *          0 = Internal clock (FOSC/4)
 */
#define TMR1_INTERNAL_CLK_MODE()    (T1CONbits.TMR1CS = TMR1_TIMER_MODE)
#define TMR1_EXTERNEL_CLK_MODE()    (T1CONbits.TMR1CS = TMR1_COUNTER_MODE)

/*
 * @brief : The Timer1 External Clock Input Synchronization Selection.
 * @note  : (T1CON) Timer1 Control Register bit <2> => (T1SYNC).
 *          => When TMR1CS = 1:
 *              1 = Do not synchronize external clock input
 *              0 = Synchronize external clock input
 *          => When TMR1CS = 0:
 *              This bit is ignored. 
 *              Timer1 uses the internal clock when TMR1CS = 0.
 */ 
#define TMR1_COUNTER_SET_SYNCH()    (T1CONbits.T1SYNC = TMR1_COUNTER_SYNCH)
#define TMR1_COUNTER_SET_ASYNCH()   (T1CONbits.T1SYNC = TMR1_COUNTER_ASYNCH)

/*
 * @brief : The Timer1 Oscillator Configurations.
 * @note  : (T1CON) Timer1 Control Register bit <3> => (T1OSCEN).
 *          1 = Timer1 oscillator is enabled
 *          0 = Timer1 oscillator is shut off
 */
#define TMR1_OSCILLATOR_ASSIGN()    (T1CONbits.T1OSCEN = TMR1_OSC_ENABLE)
#define TMR1_OSCILLATOR_NO_ASSIGN() (T1CONbits.T1OSCEN = TMR1_OSC_DISABLE)

/*
 * @brief : The Prescaler Ratio Configuration
 * @note  : (T1CON) Timer1 Control Register bits <4> & <5> 
 *          11 = 1:8 Prescale value
 *          10 = 1:4 Prescale value
 *          01 = 1:2 Prescale value
 *          00 = 1:1 Prescale value
 */
#define TMR1_PRESCALER_SET_RATIO(_R_)    (T1CONbits.T1CKPS = _R_)

/*
 * @brief : The Timer1 System Clock Status.
 * @note  : (T1CON) Timer1 Control Register bit <6> => (T1RUN).
 *              ==> (This is a read only bit) <==
 *          1 = Device clock is derived from Timer1 oscillator
 *          0 = Device clock is derived from another source
 */
#define TMR1_SYS_CLK_STATUS()           (T1CONbits.T1RUN)

/*
 * @brief : The Timer1 16-Bit Read/Write Mode Configuration.
 * @note  : (T1CON) Timer1 Control Register bit <7> => (RD16).
 *          1 = Enables register read/write of TImer1 in one 16-bit operation
 *          0 = Enables register read/write of Timer1 in two 8-bit operations
 */
#define TMR1_RW_SET_MODE_8BIT()         (T1CONbits.RD16 = TMR1_RW_REG_MODE_8BIT)
#define TMR1_RW_SET_MODE_16BIT()        (T1CONbits.RD16 = TMR1_RW_REG_MODE_16BIT)

/*
 * @brief : The Timer1 Reading and Writing into TMR1 Register.
 * @note  : (TMR1) Timer1 Register.
 */
#define TMR1_WRITE(_D_)                 (TMR1 = _D_)
#define TMR1_READ()                     (TMR1)
/* ========================================================================== */

/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
    TMR1_PRESCALAR_RATIO_1 = 0b00,
    TMR1_PRESCALAR_RATIO_2 = 0b01,  
    TMR1_PRESCALAR_RATIO_4 = 0b10,  
    TMR1_PRESCALAR_RATIO_8 = 0b11
} timer1_prescaler_ratio_t;

typedef struct
{
#if TMR1_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /**
     * A pointer to the ISR for timer1.
     */
    interrupt_handler_t TMR1_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /**
     * The priority of the timer1 interrupt.
     *          (PRIORITY_HIGH or PRIORITY_LOW)
     */
    interrupt_priority_t priority;
#endif
#endif 
    /**
     * A uint16_t value to be loaded initially in the timer1 Register.
     */
    uint16_t timer1_preloaded_value;
    /**
     * The prescaler ratio.
     *      ex => (TMR1_PRESCALAR_RATIO_2)
     */
    timer1_prescaler_ratio_t prescaler_value;
    /**
     * The timer1 operating mode
     *      (TMR1_TIMER_MODE or TMR1_COUNTER_MODE)
     */
    uint8_t timer1_mode                 :1;
    /**
     * The Synchronization mode for timer1 if it's
     *                                 assigned to operate in Counter mode.
     *      (TMR1_COUNTER_SYNCH or TMR1_COUNTER_ASYNCH )
     */
    uint8_t timer1_counter_synch_mode   :1;
    /**
     * Enable or disable the timer1 oscillator.
     *          (TMR1_OSC_ENABLE or TMR1_OSC_DISABLE)
     */
    uint8_t timer1_OSC_cfg              :1; 
    /**
     * (TMR1_RW_REG_MODE_8BIT or TMR1_RW_REG_MODE_16BIT).
     */
    uint8_t timer1_rw_mode              :1;
    /**
     * Four Reserved Bits.
     * (Unimplemented).
     */
    uint8_t timer1_reserved             :4;
    
} Timer1_t;

/*---------------  Section: Function Declarations --------------- */
/**
 * 
 * @param _timer : A pointer to a Timer1 object.
 * @Brief   A software interface initializes an object of timer 1 module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_init(const Timer1_t *_timer);

/**
 * 
 * @Brief A software interface deInitializes an object of timer 1 module.
 * @param _timer : A pointer to a Timer1 object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_deInit(const Timer1_t *_timer);

/**
 * 
 * @Brief  A software interface writes a value to the timer 1 register.  
 * @param _timer : A pointer to a Timer1 object.
 * @param _val : The value to be written into the timer 1 register.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_write_value(const Timer1_t *_timer, uint16_t _val);

/**
 * 
 * @Brief : A software interface Reads the content of the timer 1 module register.
 * @param _timer : A pointer to a Timer1 object.
 * @param _val : The variable in which the read value will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType timer1_read_value(const Timer1_t *_timer, uint16_t *_val);
#endif	/* TIMER1_H */

