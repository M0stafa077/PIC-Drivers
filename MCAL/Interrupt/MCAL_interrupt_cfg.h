/* 
 * File:   MCAL_Interrupt_cfg.h
 * Author: User
 *
 * Created on January 15, 2024, 11:34 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/* -------------- Section : Includes -------------- */
#include "../compiler.h"
#include "../DIO/DIO.h"

/* -------------- Section: Macro Declarations -------------- */
#define INTERRUPT_ENABLE                        STD_ENABLE
#define INTERRUPT_DISABLE                       STD_DISABLE

#define INTERRUPT_OCCURED                       STD_ACTIVE
#define INTERRUPT_NOT_OCCURED                   STD_IDLE

#define INTERRUPT_PRIORITY_FEATURE              INTERRUPT_ENABLE
#define EXTI_INTx_ARE_ENABLED                   INTERRUPT_ENABLE
#define EXTI_RBx_ARE_ENABLED                    INTERRUPT_ENABLE

/* -------------- Section: Macro Functions Declarations -------------- */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
/* Enables The Priority Levels */
#define INTERRUPT_PRIORITY_ENABLE()             (RCONbits.IPEN = STD_ENABLE)

/* Disables The Priority Levels */
#define INTERRUPT_PRIORITY_DISABLE()            (RCONbits.IPEN = STD_DISABLE)
#endif

/* Enables High Priority Global Interrupts */
#define INTERRUPT_GIEH_ENABLE()                 (INTCONbits.GIEH = STD_ENABLE)

/* Disables High Priority Global Interrupts */
#define INTERRUPT_GIEH_DISABLE()                (INTCONbits.GIEH = STD_DISABLE)

/* Enables Low Priority Global Interrupts */
#define INTERRUPT_GIEL_ENABLE()                 (INTCONbits.GIEL = STD_ENABLE)

/* Disables Low Priority Global Interrupts */
#define INTERRUPT_GIEL_DISABLE()                (INTCONbits.GIEL = STD_DISABLE)

/* -------------- Section: Data Type Declarations -------------- */
typedef void (*interrupt_handler_t)(void);

typedef enum {
    PRIORITY_LOW = STD_LOW,
    PRIORITY_HIGH = STD_HIGH      
} interrupt_priority_t;

/* -------------- Section: Function Declarations -------------- */

#endif	/* MCAL_INTERRUPT_CFG_H */

