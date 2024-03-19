/* 
 * File:   DIO.h
 * Author: Mostafa_Asaad
 *
 * Created on November 3, 2023, 2:32 PM
 */

#ifndef DIO_H
#define	DIO_H

/* Includes */
#include "../MCAL_std_types.h"
#include "dio_cfg.h"
#include "../device_config.h"

/* Macros Declaration */
#define BIT_MASK                    (uint8_t)0x01
#define PORTA_MASK                  0xFF
#define PORTB_MASK                  0xFF
#define PORTC_MASK                  0xFF
#define PORTD_MASK                  0xFF

#define PIN_MAX_NUMBER              8
#define PORT_MAX_NUMBER             5

/* Function-like Macros Declaration */
#define HWREG8(_x)                  (*((volatile uint8_t*)(_x)))
    
#define SET_BIT(REG, BIT_POS)       REG |= (BIT_MASK << BIT_POS)    
#define CLEAR_BIT(REG, BIT_POS)     REG &= ~(BIT_MASK << BIT_POS)    
#define TOGGLE_BIT(REG, BIT_POS)    REG ^= (BIT_MASK << BIT_POS)    
#define READ_BIT(REG, BIT_POS)      ((REG >> BIT_POS) & BIT_MASK)

/* Datatype Declarations: */
typedef enum{
    GPIO_LOW                        = 0x00,
    GPIO_HIGH                       = 0x01
} logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT           = 0,
    GPIO_DIRECTION_INPUT
} direction_t;

typedef enum{
    PIN0_INDEX                      = 0,
    PIN1_INDEX,
    PIN2_INDEX,
    PIN3_INDEX,
    PIN4_INDEX,
    PIN5_INDEX,
    PIN6_INDEX,
    PIN7_INDEX
} pin_index_t;

typedef enum{
    PORTA_INDEX                     = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
} port_index_t;

typedef struct{                     
    uint8_t port                    :3;
    uint8_t pin                     :3;
    uint8_t direction               :1;
    uint8_t logic                   :1;
} pin_config_t;


/* Functions Prototypes */
Std_ReturnType gpio_pin_direction_init(const pin_config_t* _pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config,
                                             direction_t *dir_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config,
                                    logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config,
                                   uint8_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config);

Std_ReturnType gpio_port_direction_init(const port_index_t port,
                                        uint8_t direction);
Std_ReturnType gpio_port_get_direction_status(const port_index_t port, 
                                              uint8_t* dir_status);
Std_ReturnType gpio_port_write_logic(const port_index_t port, logic_t logic);
Std_ReturnType gpio_port_read_logic(const port_index_t port, uint8_t *value);
Std_ReturnType gpio_port_toggle_logic(const port_index_t port);

#endif	/* GPIO_H */

