/* 
 * File:   button.c
 * Author: Mostafa_Asaad
 *
 * Created on November 23, 2023, 1:49 PM
 */

/* Includes */
#include "button.h"


/* Functions Declaration */

Std_ReturnType button_init(const button_t* _button){
    Std_ReturnType ret = E_OK;
    if(NULL == _button || ((_button->button_config).pin) > PIN_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_direction_init(&(_button->button_config));
    }
    return ret;
}
Std_ReturnType button_read_state(const button_t* _button, button_state_t* value){
    Std_ReturnType ret = E_OK;
    if((NULL == _button) || (((_button->button_config).pin) > PIN_MAX_NUMBER - 1)
                       || (NULL == value)){
        ret = E_NOT_OK;
    } else {
        button_state_t button_state = BUTTON_RELEASED;
        switch(_button->button_connection){
            case BUTTON_ACTIVE_HIGH:
                ret = gpio_pin_read_logic(&(_button->button_config), &button_state);
                *value = button_state;
                break;
            case BUTTON_ACTIVE_LOW:
                ret = gpio_pin_read_logic(&(_button->button_config), &button_state);
                if(GPIO_LOW == button_state){
                    *value = BUTTON_PRESSED;
                }else if (GPIO_HIGH == button_state){
                    *value = BUTTON_RELEASED;
                } else{
                    ret = E_NOT_OK;
                }
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}