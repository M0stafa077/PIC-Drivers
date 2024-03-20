/* 
 * File:   dc_motor.h
 * Author: User
 *
 * Created on December 2, 2023, 10:03 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/* ------ Includes -----*/
#include "dc_motor_cfg.h"
#include "../../MCAL/DIO/DIO.h"

/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS    0x01U
#define DC_MOTOR_OFF_STATUS   0x00U

#define DC_MOTOR_PIN1   0x00U
#define DC_MOTOR_PIN2   0x01U

/* ----------------- Data Type Declarations -----------------*/
typedef struct {
    pin_config_t button_pin[2];
} dc_motor_t;


/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType dc_motor_init(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_CW(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_CCW(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);


#endif	/* DC_MOTOR_H */

