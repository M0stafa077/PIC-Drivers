/* 
 * File:   buzzer.h
 * Author: Mostafa Asaad
 *
 * Created on January 30, 2024, 7:42 PM
 */
/* --------------- Section : Includes --------------- */
#include "buzzer.h"

/*---------------  Section: Function Definitions --------------- */

/**
 * 
 * @param _buzzer : A pointer to a buzzer object.
 * @brief : A software interface to initialize the pin connected to 
 *          the buzzer device.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType buzzer_init(const Buzzer_t *_buzzer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _buzzer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(_buzzer->buzzer_pin));
    }
    return ret;
}

/**
 * 
 * @param _buzzer : A pointer to a buzzer object.
 * @brief : A software interface to turn on the buzzer device.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType buzzer_turn_on(const Buzzer_t *_buzzer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _buzzer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_buzzer->buzzer_pin), STD_HIGH);
    }
    return ret;
}

/**
 * 
 * @param _buzzer : A pointer to a buzzer object.
 * @brief : A software interface to turn off the buzzer device.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType buzzer_turn_off(const Buzzer_t *_buzzer)
{
    Std_ReturnType ret = E_OK;
    if (NULL == _buzzer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_buzzer->buzzer_pin), STD_LOW);
    }
    return ret;
}