/* 
 * File:   ccp.h
 * Author: Mostafa Asaad
 *
 * Created on February 12, 2024, 5:28 PM
 */

#ifndef CCP_H
#define	CCP_H

/* --------------- Section : Includes --------------- */
#include "../compiler.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
#include "../DIO/DIO.h"
#include "ccp_cfg.h"
/* --------------- Section: Macro Declarations --------------- */
/**
 * CCP module Capture mode configurations
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)

#define CCP_CAPTURE_EVERY_FALLING_EDGE  ((uint8_t)(0X04))
#define CCP_CAPTURE_EVERY_RISING_EDGE   ((uint8_t)(0X05))
#define CCP_CAPTURE_4TH_RISING_EDGE     ((uint8_t)(0X06))
#define CCP_CAPTURE_16TH_RISING_EDGE    ((uint8_t)(0X07))

#define CCP_CAPTURE_READY               (STD_HIGH)
#define CCP_CAPTURE_NOT_READY           (STD_LOW)

#endif
/**
 * CCP module Compare mode configurations
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)

#define CCP_COMPARE_PIN_TOGGLE_ON_MATCH ((uint8_t)(0X02))
#define CCP_COMPARE_SET_PIN_LOW         ((uint8_t)(0X08))
#define CCP_COMPARE_SET_PIN_HIGH        ((uint8_t)(0X09))
#define CCP_COMPARE_SW_INTERRUPT        ((uint8_t)(0X0A))
#define CCP_COMPARE_GEN_EVENT           ((uint8_t)(0x0B))

#define CCP_COMPARE_READY               (STD_HIGH)
#define CCP_COMPARE_NOT_READY           (STD_LOW)
#endif

/**
 * CCP module PWM mode configurations
 */
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
#define CCP_PWM_MODE                    ((uint8_t)(0b00001100))
#endif

/* --------------- Section: Macro Functions Declarations --------------- */
#define CCP1_MODULE_SET_DISABLE()       (CCP1CONbits.CCP1M = STD_LOW)
#define CCP2_MODULE_SET_DISABLE()       (CCP2CONbits.CCP2M = STD_LOW)
/**
 * CCP1 and CCP2 Modules selecting modes.
 */
#define CCP1_SET_MODE(_MODE_)           (CCP1CONbits.CCP1M = _MODE_)
#define CCP2_SET_MODE(_MODE_)           (CCP2CONbits.CCP2M = _MODE_)

/* --------------- Section: Data Type Declarations --------------- */
typedef union
{
    struct
    {
        uint8_t cppr_low;
        uint8_t cppr_high;
    };
    struct
    {
        uint16_t ccpr_16bit;
    };
} ccp_period_reg_t;
/*
 * Chose the mode of the ccp module.
 * (CCP_MODE_CAPTURE), (CCP_MODE_COMPARE),
 *  or (CCP_MODE_PWM).
 */
typedef enum
{
    CCP_MODE_CAPTURE = 0,
    CCP_MODE_COMPARE,
    CCP_MODE_PWM
} ccp_mode_t;

/*
 * Which ccp module to use.
 * CCP1_MODULE or CCP2_MODULE
 */
typedef enum
{
    CCP1_MODULE = 0,
    CCP2_MODULE
} ccp_select_t;


/*
 * Which timer operate with the ccp modules.
 */
typedef enum
{
    CCP1_CCP2_TMR3  = 0,
    CCP1_TMR1_CCP2_TMR3,
    CCP1_CCP2_TMR1
} ccp_timer_cfg_t;
/*
 * A struct describes an object of the CCP module.
 */
typedef struct
{
#if (CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE) || (CCP2_INTERRUPT_FEATURE==INTERRUPT_ENABLE)
    /*
     * CCP module interrupt handler.
     */ 
    interrupt_handler_t ccp_interrupt_handler;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /*
     * CCP module interrupt priority.
     */ 
    interrupt_priority_t ccp_interrupt_priority;
#endif
#endif
    
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
    /*
     * CCP module capture mode configurations.
     */ 
    uint8_t ccp_capture_config;
    /*
     * Chose which timer operate with the ccp modules.
     * CCP1_CCP2_TMR3 or CCP1_TMR1_CCP2_TMR3 or CCP1_CCP2_TMR1
     */
    ccp_timer_cfg_t ccp_capture_timer;
#endif
    
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
    /*
     * CCP module compare mode configurations.
     * ex (CCP_COMPARE_SET_PIN_HIGH) or (CCP_COMPARE_SW_INTERRUPT).
     */ 
    uint8_t ccp_compare_config;
    /*
     * Chose which timer operate with the ccp modules.
     * CCP1_CCP2_TMR3 or CCP1_TMR1_CCP2_TMR3 or CCP1_CCP2_TMR1
     */
    ccp_timer_cfg_t ccp_compare_timer;
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    /*
     * CCP module pwm mode frequency.
     */ 
    uint32_t ccp_pwm_frequency;
    uint8_t timer2_prescaler_value;
    uint8_t timer2_postscaler_value;
#endif
    /*
     * CCP module mode selection.
     * CCP1_MODULE or CCP2_MODULE
     */ 
    ccp_select_t ccp_module_select;
    /*
     * Chose the mode of the ccp module.
     * (CCP_MODE_CAPTURE), (CCP_MODE_COMPARE),
     *  or (CCP_MODE_PWM).
     */
    ccp_mode_t ccp_mode;
    /*
     * The ccp module pin configurations object.
     */
    pin_config_t pin;
} ccp_t;


/* ---------------  Section: Function Declarations --------------- */
/**
 * A software interface initializes the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Init(const ccp_t *ccp_obj);
/**
 * A software Interface deInitializes the ccp module.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj);

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
/**
 * A software Interface checks for the capture status.(Ready or Not)
 * @param ccp_obj : A pointer to a ccp module object.
 * @param capture_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Capture_Is_Ready(const ccp_t *ccp_obj, uint8_t *capture_status);
/**
 * A software Interface reads the value of the capture mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param capture_value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Capture_Read_Value(const ccp_t *ccp_obj, uint16_t *capture_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
/**
 * A software Interface checks if the comparing is completed or not.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param compare_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Compare_IsCompleted(const ccp_t *ccp_obj, uint8_t *compare_status);
/**
 * A software Interface sets the value for the comparison.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param compare_value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_Compare_SetValue(const ccp_t *ccp_obj, uint16_t compare_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
/**
 * A software Interface sets the duty cycle for the ccp module in pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @param dutyCycle
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_SetDutyCycle(const ccp_t *ccp_obj, const uint8_t dutyCycle);
/**
 * A software Interface starts the pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj);
/**
 * A software Interface stops the pwm mode.
 * @param ccp_obj : A pointer to a ccp module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj);
#endif

#endif	/* CCP_H */
