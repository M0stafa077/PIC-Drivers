/* 
 * File:   keypad.h
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 11:38 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* Section : Includes */
#include "../../MCAL/DIO/DIO.h"
#include "keypad_cfg.h"

/* Section: Macro Declarations */
#define FOUR_BY_FOUR        4
#define FOUR_BY_THREE       3

/* The type of the keypad 
    FOUR_BY_FOUR or THREE_BY_THREE */
#define KEYPAD_TYPE         FOUR_BY_THREE

#if KEYPAD_TYPE==FOUR_BY_FOUR
#define KEYPAD_ROWS         4
#define KEYPAD_COLUMNS      4
#elif KEYPAD_TYPE==FOUR_BY_THREE
#define KEYPAD_ROWS         4
#define KEYPAD_COLUMNS      3
#endif

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct {
    pin_config_t keypad_row_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
} keypad_t;

/* Section: Function Declarations */
Std_ReturnType keypad_initialize(keypad_t* _keypad);
Std_ReturnType keypad_get_value(keypad_t* _keypad, uint8_t* value);

#endif	/* KEYPAD_H */

