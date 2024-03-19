/* 
 * File:   seven_segment.c
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 10:03 PM
 */

#include <stdio.h>

#include "seven_segment.h"

/**
 * 
 * @param segment : An object defining all the configurations of the 7-segment
 *                  device
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if SEVEN_SEGMENT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType seven_segment_initialize(const seven_segment_t * segment){
    Std_ReturnType ret = E_OK;
    if (NULL == segment)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8_t l_counter = ZERO_INIT;
        for (; l_counter < SEGMENT_PINS_MAX; ++l_counter)
        {
            ret = gpio_pin_initialize(&(segment->segment_pins[l_counter]));
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param segment  : An object defining all the configurations of the 7-segment
 *                  device
 * @param number   : The number to be written on the segment.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if SEVEN_SEGMENT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType seven_segment_write_num(const seven_segment_t * segment, 
                                       uint8_t number){
    Std_ReturnType ret = E_OK;
    if (NULL == segment || number > 9)
    {
        ret = E_NOT_OK;
    }
    else
    {        
        uint8_t l_counter = ZERO_INIT;
        for (; l_counter < SEGMENT_PINS_MAX; ++l_counter)
        {
            ret = gpio_pin_write_logic(&(segment -> segment_pins[l_counter]),  
                                    (number >> l_counter) & 0X01);
        }
    }
    return ret;
}
#endif  