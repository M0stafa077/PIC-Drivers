/* 
 * File:   servo_motor.h
 * Author: Mostafa Asaad
 *
 * Created on February 14, 2024, 3:45 AM
 */
/* --------------- Section : Includes --------------- */
#include "servo_motor.h"
/* --------------- Section : Helper Functions Declarations --------------- */
/* The ISR for configured ccp module */
static void servo_motor_default_ccp_interrupt(void);  

static float map(float x, float in_min, float in_max, float out_min, float out_max); 
/* --------------- Section : Global Variables --------------- */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)

volatile uint8_t servo_ccp_flag_interrupt = 0;
volatile uint16_t Compare_Duty = 1800;

ccp_t Servo_Ccp_Obj = 
{
    .ccp_module_select = CCP1_MODULE,
    
    .ccp_mode = CCP_MODE_COMPARE,
    .ccp_compare_config = CCP_COMPARE_SET_PIN_LOW,
    
    .ccp_compare_timer = CCP1_CCP2_TMR3,
    
    .pin.port = PORTC_INDEX,
    .pin.pin = PIN2_INDEX,
    .pin.direction = GPIO_DIRECTION_OUTPUT,
    .pin.logic = STD_LOW,
    
    .ccp_interrupt_handler = servo_motor_default_ccp_interrupt,
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    .ccp_interrupt_priority = PRIORITY_HIGH     
#endif
};

Timer3_t tmr3_obj = 
{
    .TMR3_INTERRUPT_HANDLER = NULL,
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    .priority = PRIORITY_HIGH,
#endif
    .timer3_mode = TMR3_TIMER_MODE,
    .timer3_rw_mode = TMR3_RW_REG_MODE_16BIT,
    
    .prescaler_value = TMR3_PRESCALAR_RATIO_1,
    .timer3_preloaded_value = 0
};

/*---------------  Section: Function Definitions --------------- */
/**
 * A software Interface initializes a servo motor object.
 * @param _servo : A pointer to a servo motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Servo_Motor_Init(void)
{
    Std_ReturnType ret = E_OK;

    ret = CCP_Compare_SetValue(&Servo_Ccp_Obj, Compare_Duty);
    
    ret = CCP_Init(&Servo_Ccp_Obj);
    
    ret = timer3_init(&tmr3_obj);
    
    return ret;
}
/**
 * A software Interface sets the angle of a servo motor.
 * @param _servo : A pointer to a servo motor object.
 * @param angle : The desired angle.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Servo_Motor_Set_Angle(float angle)
{
    Std_ReturnType ret = E_OK;

    Compare_Duty = (uint16_t) map(angle + 0.26, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, 1850.0, 4000.0);

    return ret;
}
/**
 * A software Interface de-initializes a servo motor object.
 * @param _servo : A pointer to a servo motor object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Servo_Motor_DeInit(const Servo_Motor_t *_servo)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _servo)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = CCP_Compare_SetValue(&Servo_Ccp_Obj, 0);

        ret = CCP_DeInit(&Servo_Ccp_Obj);

        ret = timer3_deInit(&tmr3_obj);
    }
    return ret;
}

/**
 * The Interrupt service routine for the 
 * servo motor.
 */
void servo_motor_default_ccp_interrupt(void)
{
    ++servo_ccp_flag_interrupt;
        
    timer3_write_value(&tmr3_obj, 0);
    
    if (1 == servo_ccp_flag_interrupt)
    {
        CCP_Compare_SetValue(&Servo_Ccp_Obj, Compare_Duty);
        CCP1_SET_MODE(CCP_COMPARE_SET_PIN_HIGH);
    }
    else if(2 == servo_ccp_flag_interrupt)
    {
        CCP_Compare_SetValue(&Servo_Ccp_Obj, 4000.0 - Compare_Duty);
        CCP1_SET_MODE(CCP_COMPARE_SET_PIN_LOW);
        servo_ccp_flag_interrupt = ZERO_INIT;
    }
    else
        { /* Nothing*/ }
}

/**
 * 
 * @param value : The value to be mapped.
 * @param min_from : The minimum value to map from.
 * @param max_from : The maximum value to map from.
 * @param min_to : The minimum value to map to.
 * @param max_to : The maximum value to map to.
 * @return : The new mapped value.
 */
static float map(float value, float min_from, float max_from, float min_to, float max_to)
{
    return (value - min_from) * (max_to - min_to) / (max_from - min_from) + min_to;
}

#endif