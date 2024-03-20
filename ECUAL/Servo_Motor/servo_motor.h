/* 
 * File:   servo_motor.h
 * Author: Mostafa Asaad
 *  ========> Not Completed <========
 * Created on February 14, 2024, 3:45 AM
 */
#ifndef SERVO_MOTOR_H
#define	SERVO_MOTOR_H

/* --------------- Section : Includes --------------- */
#include "../../MCAL/TIMER1/timer1.h"
#include "../../MCAL/TIMER3/timer3.h"
#include "../../MCAL/CCP/ccp.h"
/* --------------- Section: Macro Declarations --------------- */
#define SERVO_MIN_90_DEG_TON        (uint16_t)900
#define SERVO_MIN_90_DEG_TOFF       (uint16_t)19100

#define SERVO_MIN_45_DEG_TON        (uint16_t)1150
#define SERVO_MIN_45_DEG_TOFF       (uint16_t)18850

#define SERVO_0_DEG_TON             (uint16_t)1400
#define SERVO_0_DEG_TOFF            (uint16_t)18600

#define SERVO_45_DEG_TON            (uint16_t)1650
#define SERVO_45_DEG_TOFF           (uint16_t)18350

#define SERVO_90_DEG_TON            (uint16_t)1900
#define SERVO_90_DEG_TOFF           (uint16_t)18100

#define SERVO_MIN_ANGLE             0.0
#define SERVO_MAX_ANGLE             180.0
/* --------------- Section: Data Type Declarations --------------- */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
typedef struct
{
    /*
     * Which ccp module operates the servo.
     * (CCP1_MODULE) or (CCP2_MODULE)
     */
    ccp_select_t servo_ccp_module_select;
} Servo_Motor_t;
#endif
/*---------------  Section: Function Declarations --------------- */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
/**
 * A software Interface initializes a servo motor object.
 * @param _servo : A pointer to a servo motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
//Std_ReturnType Servo_Motor_Init(const Servo_Motor_t *_servo);
Std_ReturnType Servo_Motor_Init(void);
/**
 * A software Interface sets the angle of a servo motor.
 * @param _servo : A pointer to a servo motor object.
 * @param angle : The desired angle.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
//Std_ReturnType Servo_Motor_Set_Angle(const Servo_Motor_t *_servo, sint8_t angle);
Std_ReturnType Servo_Motor_Set_Angle(float angle);
/**
 * A software Interface de-initializes a servo motor object.
 * @param _servo : A pointer to a servo motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Servo_Motor_DeInit(const Servo_Motor_t *_servo);
#endif
#endif	/* SERVO_MOTOR_H */

