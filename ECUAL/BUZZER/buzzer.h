/* 
 * File:   buzzer.h
 * Author: Mostafa Asaad
 *
 * Created on January 30, 2024, 7:42 PM
 */

#ifndef BUZZER_H
#define	BUZZER_H

/* --------------- Section : Includes --------------- */
#include "../../MCAL/DIO/DIO.h"
/* --------------- Section: Data Type Declarations --------------- */
typedef struct
{
    pin_config_t buzzer_pin;
} Buzzer_t;
/*---------------  Section: Function Declarations --------------- */
Std_ReturnType buzzer_init(const Buzzer_t *_buzzer);
Std_ReturnType buzzer_turn_on(const Buzzer_t *_buzzer);
Std_ReturnType buzzer_turn_off(const Buzzer_t *_buzzer);

#endif	/* BUZZER_H */

