/* 
 * File:   relay.c
 * Author: Mostafa_Asaad
 *
 * Created on November 30, 2023, 1:50 PM
 */

/* Includes */
#include "relay.h"

/* Functions Definitions */ 

/**
 * @brief: initializing the relay pin  
 * 
 * @param _relay: pointer to structure containing port, pin, and initial status 
 *              of the relay
 * @return: Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_init(relay_t* _relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else {
        pin_config_t relay_config = {
            .port      = _relay->relay_port,
            .pin       = _relay->relay_pin,
            .logic     = _relay->relay_status,
            .direction = GPIO_DIRECTION_OUTPUT
        };
        ret = gpio_pin_initialize(&relay_config);
    }
    return ret;    
}

/**
 * @brief: turning the relay on
 * 
 * @param _relay: pointer to structure containing port, pin, and initial status 
 *              of the relay
 * @return: Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_on(relay_t* _relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else {
        pin_config_t relay_config = {
            .port      = _relay->relay_port,
            .pin       = _relay->relay_pin,
            .logic     = _relay->relay_status,
            .direction = GPIO_DIRECTION_OUTPUT
        };
        ret = gpio_pin_write_logic(&relay_config, GPIO_HIGH);
    }
    return ret; 
}

/**
 * @brief: turning the relay off 
 * 
 * @param _relay: pointer to structure containing port, pin, and initial status 
 *              of the relay
 * @return: Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_off(relay_t* _relay){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else {
        pin_config_t relay_config = {
            .port      = _relay->relay_port,
            .pin       = _relay->relay_pin,
            .logic     = _relay->relay_status,
            .direction = GPIO_DIRECTION_OUTPUT
        };
        ret = gpio_pin_write_logic(&relay_config, GPIO_LOW);
    }
    return ret; 
}