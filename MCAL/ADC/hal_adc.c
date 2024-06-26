/* 
 * File  : hal_adc.c
 * Author: Mostafa Asaad
 * https://github.com/M0stafa077
 * Created on January 27, 2024, 4:03 PM
 */
/* --------------- Section : Includes --------------- */
#include "hal_adc.h"
/* --------------- Section : Global Variables --------------- */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/*
 * @brief A static pointer to the Interrupt Service
 * Routine function for the ADC module interrupts.
 */
static interrupt_handler_t ADC_interrupt_handler = NULL;
#endif
/*---------------  Section: Helper Functions Declaration --------------- */

/**
 * @brief A static software interface configures 
 * the selected adc channel as input pin.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_input_channel_port_cfg(const adc_cfg_t *_adc);
/**
 * @brief A static software interface configures 
 * the result format for the ADC module.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_set_result_format(const adc_cfg_t *_adc);
/**
 * @brief A static software interface configures 
 * the voltage reference for the ADC module.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_set_voltage_ref(const adc_cfg_t *_adc);
/*---------------  Section: Functions Definition --------------- */

/**
 * @brief A software interface initializes the 
 * A/D module.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_init(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable The ADC */
        ADC_DISABLE();
        /* Configure Acquisition time */
        ADC_SET_ACQ_TIME(_adc -> acquisition_time);
        /* Configure Conversion Clock */
        ADC_SET_CONV_CLK(_adc -> conversion_clock);
        /* Configure default Channel */
        ADC_SELECT_CHANNEL(_adc -> adc_channel);
        adc_input_channel_port_cfg(_adc);
        /* Configure the Interrupt */        
#if ADC_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
        INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        // Enable the Interrupt priority.
        INTERRUPT_PRIORITY_ENABLE();
#endif
        // Clear the ADC interrupt flag
        INTI_ADC_CLR_FLAG();
        // Enable the Interrupts for the ADC module
        INTI_ADC_INTERRRUPT_ENABLE();
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
        // Assign the specified priority.
        if (PRIORITY_HIGH == _adc -> priority)
            { INTI_ADC_INTERRUPT_PRIORITY_HIGH(); }
        else if (PRIORITY_LOW == _adc -> priority)
            { INTI_ADC_INTERRUPT_PRIORITY_LOW(); }
        else
            { INTI_ADC_INTERRUPT_PRIORITY_HIGH(); }
#endif
        // Assign the Interrupt handler
        ADC_interrupt_handler = _adc -> ADC_InterruptHandler;
#endif
        /* Configure Result Format */
        adc_set_result_format(_adc);
        /* Configure Voltage Reference */
        adc_set_voltage_ref(_adc);
        /* Enable The ADC */
        ADC_ENABLE();
    }
    return ret;
}
/**
 * @brief A software interface de-initializes the ADC module. 
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType ADC_deInit(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable The ADC */
        ADC_DISABLE();
        /* Disable the Interrupt */
#if ADC_INTERRUPT_FEATURE==INTERRUPT_ENABLE
        INTI_ADC_INTERRRUPT_DISABLE();
#endif
    }
    return ret;
}
/*
 * @brief A software interface selects the channel for the ADC module.
 * @param _adc : Pointer to the adc module object.
 * @param channel : The channel to be selected.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_select_channel(adc_cfg_t *_adc, ADC_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        _adc->adc_channel = channel;
        ADC_SELECT_CHANNEL (channel);
        adc_input_channel_port_cfg(_adc);
    }
    return ret;
}

/**
 * @brief A software interface starts the conversion.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_start_conversion(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    return ret;
}
/**
 * @brief A software interface checks the status
 * of the A/D conversion.
 * @param _adc : Pointer to the adc module object.
 * @param status : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_is_conversion_done(const adc_cfg_t *_adc, uint8_t* status)
{
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == status))
    {
        ret = E_NOT_OK;
    }
    else
    {        
        if (STD_TRUE == ADC_CONVERSION_STATUS())
        {
            *status = ADC_CONVERSION_IN_PROGRESS;
        }
        else if (STD_FALSE == ADC_CONVERSION_STATUS())
        {
            *status = ADC_CONVERSION_COMPLETE;
        }
        else
        { /* Nothing */ }
    }
    return ret;
}
/**
 * @brief A software interface gets the
 * result of the A/D conversion
 * @param _adc : Pointer to the adc module object.
 * @param result : The variable ref to store the result in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_result(const adc_cfg_t *_adc, adc_result_t *result)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc || NULL == result)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* (ADRESH / ADRESL) */
        switch (_adc->result_format)
        {
            case ADC_RESULT_RIGHT : 
                *result = (adc_result_t)((ADRESH << 8) + ADRESL);
                break;
            case ADC_RESULT_LEFT :
                *result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
                break;
            default:
                *result = (adc_result_t)((ADRESH << 8) + ADRESL);
                break;
        }
    }
    return ret; 
}
/*
 * @brief A software interface gets the
 * result of the A/D conversion by blocking.
 * @param _adc : Pointer to the adc module object.
 * @param channel : The Channel to be selected.
 * @param conversion_result : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_blocking(const adc_cfg_t *_adc, adc_result_t *conversion_result)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc || NULL == conversion_result)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = ADC_start_conversion(_adc);
        while(ADC_CONVERSION_STATUS());
        ret = ADC_get_conversion_result(_adc, conversion_result);
    }
    return ret; 
}
/*
 * @brief A software interface starts the A/D
 * conversion using interrupt feature.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_start_conversion_interrupt(const adc_cfg_t *_adc)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = ADC_start_conversion(_adc);
    }
    return ret; 
}
/*---------------  Section: Helper Functions Definition --------------- */

/**
 * @brief A static software interface configures 
 * the selected adc channel as input pin.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_input_channel_port_cfg(const adc_cfg_t *_adc)
{
    switch (_adc->adc_channel)
    {
        case ADC_CHANNEL_AN0  : SET_BIT(TRISA, PIN0_INDEX);
                            break;
        case ADC_CHANNEL_AN1  : SET_BIT(TRISA, PIN1_INDEX);
                            break;
        case ADC_CHANNEL_AN2  : SET_BIT(TRISA, PIN2_INDEX);
                            break;
        case ADC_CHANNEL_AN3  : SET_BIT(TRISA, PIN3_INDEX);
                            break;
        case ADC_CHANNEL_AN4  : SET_BIT(TRISA, PIN5_INDEX);
                            break;
        case ADC_CHANNEL_AN5  : SET_BIT(TRISE, PIN0_INDEX);
                            break;
        case ADC_CHANNEL_AN6  : SET_BIT(TRISE, PIN1_INDEX);
                            break;
        case ADC_CHANNEL_AN7  : SET_BIT(TRISE, PIN2_INDEX);
                            break;
        case ADC_CHANNEL_AN8  : SET_BIT(TRISB, PIN2_INDEX);
                            break;
        case ADC_CHANNEL_AN9  : SET_BIT(TRISB, PIN3_INDEX);
                            break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, PIN1_INDEX);
                            break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, PIN4_INDEX);
                            break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, PIN0_INDEX);
                            break;
    }
}
/**
 * @brief A static software interface configures 
 * the result format for the ADC module.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_set_result_format(const adc_cfg_t *_adc)
{
    switch (_adc -> result_format)
    {
        case ADC_RESULT_RIGHT : ADC_RESULT_RIGHT_FORMAT();
                            break;
        case ADC_RESULT_LEFT : ADC_RESULT_LEFT_FORMAT();
                            break;
        default : ADC_RESULT_RIGHT_FORMAT();
              break;
    }       
}
/**
 * @brief A static software interface configures 
 * the voltage reference for the ADC module.
 * @param _adc : Pointer to the adc module object.
 */
static void adc_set_voltage_ref(const adc_cfg_t *_adc)
{
    switch (_adc->voltage_reference)
    {
        case ADC_VOLTAGE_REFERENCE_ENABLED : ADC_ENABLE_VOLTAGE_REFERENCE();
                                        break;
        case ADC_VOLTAGE_REFERENCE_DISABLED : ADC_DISABLE_VOLTAGE_REFERENCE();
                                        break;
        default : ADC_DISABLE_VOLTAGE_REFERENCE();
              break;         
    }
}

/**
 * @brief ADC module Interrupt Handler.
 */
void INTI_ADC_ISR(void)
{
    /* 1. Clear the interrupt flag */
    INTI_ADC_CLR_FLAG();
    /* 2. Call The ISR */
    if (ADC_interrupt_handler)
        { ADC_interrupt_handler(); }
    else
        { /* Nothing */ }
}
