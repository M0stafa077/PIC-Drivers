/* 
 * File:   dc_motor.c
 * Author: User
 *
 * Created on December 2, 2023, 10:03 PM
 */

#include "dc_motor.h"

Std_ReturnType dc_motor_init(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if((NULL == _dc_motor) || ((_dc_motor->button_pin)->pin) > PIN_MAX_NUMBER - 1
                           || ((_dc_motor->button_pin)->port) > PORT_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_initialize(&(_dc_motor->button_pin[DC_MOTOR_PIN1]));
        ret = gpio_pin_initialize(&(_dc_motor->button_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}
Std_ReturnType dc_motor_move_CW(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
Std_ReturnType dc_motor_move_CCW(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
    return ret;
}
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->button_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}