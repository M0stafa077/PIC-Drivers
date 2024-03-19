/* 
 * File:   timer0.h
 * Author: Mostafa Asaad
 *
 * Created on January 31, 2024, 1:18 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H
/* --------------- Section : Includes --------------- */
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */
#define TMR0_TIMER_MODE             STD_HIGH
#define TMR0_COUNTER_MODE           STD_LOW

#define TMR0_PRESCALER_ENABLE       STD_HIGH
#define TMR0_PRESCALER_DISABLE      STD_LOW

#define TMR0_COUNTER_RISING_EDGE    STD_HIGH
#define TMR0_COUNTER_FALLING_EDGE   STD_LOW

#define TMR0_8_BIT_MODE             STD_HIGH
#define TMR0_16_BIT_MODE            STD_LOW
/* --------------- Section: Macro Functions Declarations --------------- */

/*
 * @brief : The Timer0 Enabling configuration.
 * @note  : (T0CON) Timer0 Control Register bit<7> => (TMR0ON)
 *          1 = Enables Timer0
 *          0 = Stops Timer0
 */
#define TMR0_MODULE_ENABLE()           (T0CONbits.TMR0ON = STD_ENABLE)
#define TMR0_MODULE_DISABLE()          (T0CONbits.TMR0ON = STD_DISABLE)

/*
 * @brief : The clock source configurations for Timer0 module.
 * @note  : (T0CON) Timer0 Control Register bit<5> => (T0CS) Clock Source Select.
 *          1 = Transition on T0CKI pin.
 *          0 = Internal instruction cycle clock (CLKO).
 */
#define TMR0_INTERNAL_CLK_MODE()        (T0CONbits.T0CS = STD_LOW)
#define TMR0_EXTERNEL_CLK_MODE()        (T0CONbits.T0CS = STD_HIGH)

/*
 * @brief : The Timer0 Source Edge Configuration.
 * @note  : (T0CON) Timer0 Control Register bit<4> => (T0SE).
 *          1 = Increment on high-to-low transition on T0CKI pin (falling edge)
 *          0 = Increment on low-to-high transition on T0CKI pin (rising  edge)
 */ 
#define TMR0_SELECT_RISING_EDGE()       (T0CONbits.T0SE = STD_LOW)
#define TMR0_SELECT_FALLING_EDGE()      (T0CONbits.T0SE = STD_HIGH)

/*
 * @brief : The Prescaler Assignment for Timer0 Module
 * @note  : (T0CON) Timer0 Control Register bit<3> => (PSA) prescaler assignment.
 *          1 = Timer0 prescaler is not assigned. 
 *              Timer0 clock input bypasses prescaler.
 *          0 = Timer0 prescaler is assigned. 
 *              Timer0 clock input comes from prescaler output. 
 */
#define TMR0_PRESCALAR_ASSIGN()         (T0CONbits.PSA = STD_LOW)
#define TMR0_PRESCALAR_NO_ASSIGN()      (T0CONbits.PSA = STD_HIGH)

/*
 * @brief : The Prescaler Ratio Configuration
 * @note  : (T0CON) Timer0 Control Register bits <0> to <2> 
 *          Timer0 prescaler select bits
 *          111 = 1:256 Prescale value  (7)
 *          110 = 1:128 Prescale value  (6)
 *          101 = 1:64 Prescale value   (5)
 *          100 = 1:32 Prescale value   (4)
 *          011 = 1:16 Prescale value   (3)
 *          010 = 1:8 Prescale value    (2)
 *          001 = 1:4 Prescale value    (1)
 *          000 = 1:2 Prescale value    (0)
 */
#define TMR0_PRESCALER_SET_RATIO(_R_)    (T0CONbits.T0PS = _R_)

/*
 * @brief : R/W data in the high & low registers of Timer0
 * @note  :  TMR0H => High Byte.
 *           TMR0L => Low Byte.
 */
#define TMR0_WRITE_HIGH_BYTE(_D_)       (TMR0H = _D_)
#define TMR0_WRITE_LOW_BYTE(_D_)        (TMR0L = _D_)

#define TMR0_READ_LOW_BYTE()            (TMR0L)
#define TMR0_READ_HIGH_BYTE()           (TMR0H)
/*
 * @brief : Timer0 8Bit/16Bit Configurations.
 * @note  : (T0CON) Timer0 Control Register bit<6> => T08BIT: Timer0 8-Bit/16-Bit 
 *                                                            Control bit.
 *          1 = Timer0 is configured as an 8-bit timer/counter
 *          0 = Timer0 is configured as a 16-bit timer/counter
 */
#define TMR0_SELECT_8BIT_MODE()         (T0CONbits.T08BIT = STD_HIGH)
#define TMR0_SELECT_16BIT_MODE()        (T0CONbits.T08BIT = STD_LOW)


/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
    TMR0_PRESCALAR_RATIO_2 = 0,
    TMR0_PRESCALAR_RATIO_4,  
    TMR0_PRESCALAR_RATIO_8,  
    TMR0_PRESCALAR_RATIO_16,  
    TMR0_PRESCALAR_RATIO_32,  
    TMR0_PRESCALAR_RATIO_64,  
    TMR0_PRESCALAR_RATIO_128,  
    TMR0_PRESCALAR_RATIO_256  
} timer0_prescalar_ratio_t;

typedef struct 
{
#if TMR0_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    interrupt_handler_t TMR0_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    interrupt_priority_t priority;
#endif
#endif  
    uint16_t timer0_preloaded_value;
    timer0_prescalar_ratio_t prescaler_value;
    uint8_t timer0_mode                   :1;
    uint8_t prescaler_enable              :1;
    uint8_t tmr0_register_size            :1;
    uint8_t tmr0_counter_edge_select      :1;
    uint8_t tmr0_reserved                 :4;
} Timer0_t;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType timer0_init(const Timer0_t *_timer);
Std_ReturnType timer0_deInit(const Timer0_t *_timer);
Std_ReturnType timer0_write_value(const Timer0_t *_timer, uint16_t _val);
Std_ReturnType timer0_read_value(const Timer0_t *_timer, uint16_t *_val);
#endif	/* TIMER0_H */

