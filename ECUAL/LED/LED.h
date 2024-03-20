/* 
 * File:   LED.h
 * Author: Mostafa_Asaad
 *
 * Created on November 3, 2023, 3:19 PM
 */

#ifndef LED_H
#define	LED_H

/* Includes */
#include "../../MCAL/DIO/DIO.h"

/* Datatype Declarations: */
typedef enum {
    LED_ON  = 1,
    LED_OFF = 0
} led_status_t;

typedef struct {
    uint8_t port       : 4;
    uint8_t pin        : 3;
    uint8_t led_status : 1;
}led_t;

/* Macros Declaration */

/* Function Macros Declaration */

/* Functions Prototypes */
Std_ReturnType led_init(const led_t* led);
Std_ReturnType led_turn_ON(const led_t* led);
Std_ReturnType led_turn_OFF(const led_t* led);
Std_ReturnType led_TOGGLE(const led_t* led);
Std_ReturnType led_READ(const led_t* led, uint8_t* status);


#endif	/* LED_H */

