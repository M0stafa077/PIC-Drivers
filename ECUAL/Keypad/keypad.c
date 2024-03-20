/* 
 * File:   keypad.c
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 11:38 PM
 */
/* ------------- Section : Includes ------------- */
#include "keypad.h"

/* ------------- Section : Global Variables ------------- */
#if KEYPAD_TYPE==FOUR_BY_FOUR
static const uint8_t buttons_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = 
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};
#elif KEYPAD_TYPE==FOUR_BY_THREE
static const uint8_t buttons_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = 
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
#endif


/* ------------- Section : Functions Definitions ------------- */
/**
 * 
 * @param _keypad : A pointer to a keypad object.
 * @brief : A software interface initializes the keypad object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType keypad_initialize(keypad_t* _keypad)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _keypad){
        ret = E_NOT_OK;
    }
    else{
        uint8_t l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT;
        for (l_rows_counter = ZERO_INIT; l_rows_counter < KEYPAD_ROWS; ++l_rows_counter)
        {
            ret = gpio_pin_initialize(&(_keypad->keypad_row_pins[l_rows_counter]));
        }
        for (l_columns_counter = ZERO_INIT; l_columns_counter < KEYPAD_COLUMNS; ++l_columns_counter)
        {
            ret = gpio_pin_direction_init(&(_keypad->keypad_columns_pins[l_columns_counter]));
        }
    }
    return ret;
}

/**
 * 
 * @param _keypad : A pointer to a keypad object.
 * @param value : The variable in which the value will be stored.
 * @brief : A software interface gets the clicked button on the keypad.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(keypad_t* _keypad, uint8_t* value)
{
    Std_ReturnType ret = E_OK;
    if((NULL == _keypad) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else
    {
        uint8_t l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
        uint8_t columns_logic = GPIO_LOW;
        for(l_rows_counter = ZERO_INIT;l_rows_counter < KEYPAD_ROWS; l_rows_counter++)
        {
            
            /* First : make sure all rows are LOW */
            for(l_counter = ZERO_INIT;l_counter < KEYPAD_ROWS; ++l_counter)
            {
                ret = gpio_pin_write_logic(&(_keypad->keypad_row_pins[l_counter]), GPIO_LOW);
            }
            
            /* Then write HIGH on the current row */
            ret = gpio_pin_write_logic(&(_keypad->keypad_row_pins[l_rows_counter]), GPIO_HIGH);
            for (l_columns_counter = ZERO_INIT; l_columns_counter  < KEYPAD_COLUMNS; l_columns_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad->keypad_columns_pins[l_columns_counter]), &columns_logic);
                if(GPIO_HIGH == columns_logic){
                    *value = buttons_values[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return ret;
}