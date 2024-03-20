/* 
 * File:   LED.c
 * Author: Mostafa_Asaad
 *
 * Created on November 3, 2023, 3:19 PM
 */

#include "LED.h"


/* Functions Definitions */

/**
 * @brief Initializing the led's port & pin
 * @param led : pointer to structure containing port, pin, and initial status 
 *              of the led
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_init(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(NULL == led || (led -> pin) > (PIN_MAX_NUMBER - 1) ){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t led_pin_config = {.port = led->port, .pin = led->pin, 
                                    .direction = GPIO_DIRECTION_OUTPUT, 
                                    .logic = led->led_status};
        ret = gpio_pin_initialize(&led_pin_config);
    }
    return ret;    
}

/**
 * @brief Turning The led ON
 * @param led : pointer to structure containing port, pin, and initial status 
 *              of the led
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_ON(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(NULL == led || (led -> pin) > (PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t led_pin_config = {.port = led->port, .pin = led->pin, 
                                    .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        
        ret = gpio_pin_initialize(&led_pin_config);
        ret = gpio_pin_write_logic(&led_pin_config, GPIO_HIGH);
    }
    return ret;  
}

/**
 * 
 * @param led
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_OFF(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(NULL == led || (led -> pin) > (PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t led_pin_config = {.port = led->port, .pin = led->pin, 
                                    .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        
        ret = gpio_pin_initialize(&led_pin_config);
        ret = gpio_pin_write_logic(&led_pin_config, GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param led
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_TOGGLE(const led_t* led){
    Std_ReturnType ret = E_OK;
    if(NULL == led || (led -> pin) > (PIN_MAX_NUMBER - 1)){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t led_pin_config = {.port = led->port, .pin = led->pin, 
                                    .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        ret = gpio_pin_toggle_logic(&led_pin_config);
    }
    return ret;
}

Std_ReturnType led_STATUS(const led_t* led, uint8_t* status) {
    Std_ReturnType ret = E_OK;
    if(NULL == led || (led -> pin) > (PIN_MAX_NUMBER - 1) ){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t led_pin_config = {.port = led->port, .pin = led->pin, 
                                    .direction = GPIO_DIRECTION_OUTPUT, .logic = led->led_status};
        ret = gpio_pin_read_logic(&led_pin_config, status);
    }
    return ret;
}
