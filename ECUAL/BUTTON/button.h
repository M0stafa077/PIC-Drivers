/* 
 * File:   button.h
 * Author: Mostafa_Asaad
 * Created on November 23, 2023, 1:42 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/* Includes : */
#include "../../MCAL/DIO/DIO.h"
/* Datatype Declaration :*/
typedef enum{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
} button_state_t;

typedef enum{
    BUTTON_ACTIVE_LOW  = 0,
    BUTTON_ACTIVE_HIGH
} button_active_state_t;

typedef struct{
    pin_config_t button_config;
    button_active_state_t button_connection;
    
} button_t;

/* Functions Prototypes */
Std_ReturnType button_init(const button_t* _button);               
Std_ReturnType button_read_state(const button_t* _button, button_state_t* value); 


#endif	/* BUTTON_H */

