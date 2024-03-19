/* 
 * File:   EXTI.h
 * Author: Mostafa Asaad
 *
 * Created on January 15, 2024, 11:33 PM
 */

#ifndef EXTI_H
#define	EXTI_H

/* Section : Includes */
#include "../MCAL_interrupt_cfg.h"

/* Section: Macro Declarations */

/* --------------- Section: Macro Functions Declarations --------------- */
#if EXTI_INTx_ARE_ENABLED==INTERRUPT_ENABLE

/* Handling INT0 pin */
#define EXTI_INT0_ENABLE()              (INTCONbits.INT0IE = INTERRUPT_ENABLE)
#define EXTI_INT0_DISABLE()             (INTCONbits.INT0IE = INTERRUPT_DISABLE)
#define EXTI_INT0_CLR_FLAG()            (INTCONbits.INT0IF = STD_LOW)
#define EXTI_INT0_AT_RISING_EDGE()      (INTCON2bits.INTEDG0 = STD_RISING_EDGE)
#define EXTI_INT0_AT_FALLING_EDGE()     (INTCON2bits.INTEDG0 = STD_FALLING_EDGE)


/* Handling INT1 pin */
#define EXTI_INT1_ENABLE()              (INTCON3bits.INT1IE = INTERRUPT_ENABLE)
#define EXTI_INT1_DISABLE()             (INTCON3bits.INT1IE = INTERRUPT_DISABLE)
#define EXTI_INT1_CLR_FLAG()            (INTCON3bits.INT1IF = STD_LOW)
#define EXTI_INT1_AT_RISING_EDGE()      (INTCON2bits.INTEDG1 = STD_RISING_EDGE)
#define EXTI_INT1_AT_FALLING_EDGE()     (INTCON2bits.INTEDG1 = STD_FALLING_EDGE)

/* Handling INT2 pin */
#define EXTI_INT2_ENABLE()              (INTCON3bits.INT2IE = INTERRUPT_ENABLE)
#define EXTI_INT2_DISABLE()             (INTCON3bits.INT2IE = INTERRUPT_DISABLE)
#define EXTI_INT2_CLR_FLAG()            (INTCON3bits.INT2IF = STD_LOW)
#define EXTI_INT2_AT_RISING_EDGE()      (INTCON2bits.INTEDG2 = STD_RISING_EDGE)
#define EXTI_INT2_AT_FALLING_EDGE()     (INTCON2bits.INTEDG2 = STD_FALLING_EDGE)
/* Handling INT0, INT1, and INT2 Priority bit */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE

/* -> INT0 is always at High Priority <-*/
/* INT1 Priority Handling */
#define EXTI_INT1_PRIORITY_HIGH()       (INTCON3bits.INT1IP = PRIORITY_HIGH)
#define EXTI_INT1_PRIORITY_LOW()        (INTCON3bits.INT1IP = PRIORITY_LOW)
/* INT2 Priority Handling */
#define EXTI_INT2_PRIORITY_HIGH()       (INTCON3bits.INT2IP = PRIORITY_HIGH)
#define EXTI_INT2_PRIORITY_LOW()        (INTCON3bits.INT2IP = PRIORITY_LOW)

#endif

#endif

/* -> Handling The ON_CHANGE pins on Port B <- */
#if EXTI_RBx_ARE_ENABLED==INTERRUPT_ENABLE

#define EXTI_RBx_ENABLE()               (INTCONbits.RBIE = INTERRUPT_ENABLE)
#define EXTI_RBx_DISABLE()              (INTCONbits.RBIE = INTERRUPT_DISABLE)
#define EXTI_RBx_CLR_FLAG()             (INTCONbits.RBIF = STD_LOW)

/* Handling the priority of the ON_CHANGE pins on Port B */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE

#define EXTI_RBx_PRIORITY_HIGH()         (INTCON2bits.RBIP = PRIORITY_HIGH)
#define EXTI_RBx_PRIORITY_LOW()          (INTCON2bits.RBIP = PRIORITY_LOW)

#endif

#endif
/* --------------- Section: Data Type Declarations --------------- */


typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE   
} EXTI_INTx_edge_t;

typedef enum {
    EXTI_INT0 = 0,
    EXTI_INT1,
    EXTI_INT2            
} EXTI_INTx_src_t;

typedef struct {
    /* Needs Five configurations 
     * (CallBack Function)
     * (Which pin on the MCU)
     * (FALLING OR RISING EDGE)
     * (WHO'S THE SRC OF THE INTERRUPT)
     * (WHAT'S THE PRIORITY OF THIS INTERRUPT) 
    */
    void (* EXTI_Handler)(void);
    pin_config_t mcu_pin;
    EXTI_INTx_edge_t edge;
    EXTI_INTx_src_t src;
    interrupt_priority_t priority;
} EXTI_INTx_t;

typedef struct {
    /* Needs Three configurations 
     * (Two CallBack Functions :
     *      One for the High from Low change
     *      Another one for Low from High Change).
     * (Which pin on the MCU)
     * (WHAT'S THE PRIORITY OF THIS INTERRUPT) 
    */
    struct 
    {
        interrupt_handler_t EXTI_HIGH_Handler;
        interrupt_handler_t EXTI_LOW_Handler;
    };
    pin_config_t mcu_pin;
    interrupt_priority_t priority;
} EXTI_RBx_t;

/* --------------- Section: Function Declarations --------------- */
#if EXTI_INTx_ARE_ENABLED==INTERRUPT_ENABLE
Std_ReturnType EXTI_INTx_init(const EXTI_INTx_t* int_obj);
Std_ReturnType EXTI_INTx_deInit(const EXTI_INTx_t* int_obj);
#endif

#if EXTI_RBx_ARE_ENABLED==INTERRUPT_ENABLE
Std_ReturnType EXTI_RBx_init(const EXTI_RBx_t* int_obj);
Std_ReturnType EXTI_RBx_deInit(const EXTI_RBx_t* int_obj);
#endif

#endif	/* EXTI_H */

