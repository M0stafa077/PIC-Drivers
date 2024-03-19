/* 
 * File:   seven_segment.h
 * Author: Mostafa_Asaad
 *
 * Created on December 8, 2023, 10:03 PM
 */

#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

/* Section : Includes */
#include "../../MCAL/DIO/DIO.h"
#include "seven_segment_cfg.h"


/* Section: Macro Declarations */
#define SEGMENT_PIN0        0
#define SEGMENT_PIN1        1
#define SEGMENT_PIN2        2
#define SEGMENT_PIN3        3

#define SEGMENT_PINS_MAX    4

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
    
}seven_segment_t;

/* Section: Function Declarations */
Std_ReturnType seven_segment_initialize(const seven_segment_t * segment);
Std_ReturnType seven_segment_write_num(const seven_segment_t * segment, uint8_t num);

#endif	/* SEVEN_SEGMENT_H */

