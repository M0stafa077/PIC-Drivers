/* 
 * File:   DIO.c
 * Author: Mostafa_Asaad
 *
 * Created on November 3, 2023, 2:32 PM
 */

/* -------------Includes------------- */
#include "DIO.h"

/* Reference to the Data Direction Control Registers (TRIS) */
volatile uint8_t* tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE}; /*-->accessed with dereferencing <--*/
/* Reference to the Data Latch Register (LAT) (Read and Write to Data Latch) */
volatile uint8_t* lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};       /*-->accessed with dereferencing <--*/
/* Reference to the port status registers (PORT) */
volatile uint8_t* port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE}; /*-->accessed with dereferencing <--*/

/* -------------Functions Definitions------------- */
/**
 * 
 * @param _pin_config : an object describes the pin configurations.
 * @param direction : The direction of the pin.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 *  @brief: --> Sets The direction of the pin (i/p or o/p) <--
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_init(const pin_config_t* _pin_config){ 
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config -> pin > PIN_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else {
        switch(_pin_config -> direction){
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config -> port], _pin_config -> pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config -> port], _pin_config -> pin);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }           
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : an object describes the pin configurations.
 * @param dir_status  : a pointer to the variable receiving the direction 
 *                      status of the pin 
 * @return Status of the function 
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 * @brief             : --> READS THE DIRECTION OF THE PIN <--
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config, direction_t *dir_status){  
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin) > PIN_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    } 
    else {
        *dir_status = READ_BIT(*tris_registers[_pin_config -> port], _pin_config -> pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : an object describes the pin configurations.
 * @param logic       : The logic wanted to be written on the pin.
 * @return Status of the function
 *          (E_OK)    : The function done successfully
 *          (E_NOT_OK): The function has issue to perform this action
 * @brief             : --> Writes desired logic on a pin. <--
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin) > PIN_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else {
        switch(logic){
            case STD_HIGH:
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case STD_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default: ret = E_NOT_OK;    
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config  : an object describes the pin configurations.
 * @param logic        : a pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Reads the logic on a pin. <-- 
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, uint8_t *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config -> pin > PIN_MAX_NUMBER - 1 || NULL == logic)
    {
        ret = E_NOT_OK;
    } else
    {
        *logic = READ_BIT(*port_registers[_pin_config -> port], _pin_config -> pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Toggles the logic on a pin. <--
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin) > PIN_MAX_NUMBER - 1 ){
        ret = E_NOT_OK;
    } else{
        TOGGLE_BIT(*lat_registers[_pin_config -> port], _pin_config -> pin);
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config  : an object describes the pin configurations.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Initializes the direction of the pin
 *                          and writes the desired logic on it also. <-- 
 */
#if DIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || (_pin_config -> pin) > PIN_MAX_NUMBER - 1)
    {
        ret = E_NOT_OK;
    }
    else 
    {
        ret = gpio_pin_direction_init(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

/**
 * 
 * @param port         : The port number or name.
 * @param direction    : The direction of the port (Input or Output)
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Initializes the direction of the whole port <--
 */
#if DIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_init(const port_index_t port, uint8_t direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else {
        *tris_registers[port] = direction;
    } 
    return ret;
}
#endif

/**
 * 
 * @param port         : The port number or name.
 * @param dir_status   : A pointer to the variable in which the logic 
 *                      state of the pin should be stored.
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Reads the direction of the whole port <-- 
 */
#if DIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(const port_index_t port,
                                              uint8_t* dir_status){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else {
        *dir_status = *tris_registers[port];
    }
    
    return ret;
}
#endif
/**
 * 
 * @param port         : The port number or name.
 * @param logic        : The logic to be written on the port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Writes the desired logic on the whole port <-- 
 */
#if DIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(const port_index_t port, logic_t logic){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else {
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif

/**
 * 
 * @param port         : The port number or name.
 * @param value        : a pointer to the variable in which the logic 
 *                       state of the port should be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Reads the logic on the whole port <-- 
 */
#if DIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8_t *value){
    Std_ReturnType ret = E_OK;
    if((port > PORT_MAX_NUMBER - 1 )|| (NULL == value) ){
        ret = E_NOT_OK;
    }
    else {
        *value = *lat_registers[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port         : The port number or name.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @brief              : --> Toggles the logic on the whole port <--
 */

#if DIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        *lat_registers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif