/* 
 * File:   relay.h
 * Author: Mostafa_Asaad
 *
 * Created on November 30, 2023, 1:50 PM
 */

#ifndef RELAY_H
#define	RELAY_H

/* Includes */
#include "../../MCAL/DIO/DIO.h"

/* Macros Declaration */
#define RELAY_ON_STATUS      STD_ACTIVE
#define RELAY_OFF_STATUS     STD_IDLE

/* Datatype Declarations: */
typedef struct {
    uint8_t relay_port    : 4;
    uint8_t relay_pin     : 3;
    uint8_t relay_status  : 1;       
} relay_t;

/* Functions Prototypes */
Std_ReturnType relay_init(relay_t* _relay);
Std_ReturnType relay_turn_on(relay_t* _relay);
Std_ReturnType relay_turn_off(relay_t* _relay);

#endif	/* RELAY_H */

