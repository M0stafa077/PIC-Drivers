/* 
 * File:   bluetooth_module.h
 * Author: Mostafa Asaad
 *
 * Created on February 18, 2024, 6:59 PM
 */

#ifndef BLUETOOTH_MODULE_H
#define	BLUETOOTH_MODULE_H

/* --------------- Section : Includes --------------- */
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/USART/usart.h"
/* --------------- Section: Macro Declarations --------------- */

/* --------------- Section: Macro Functions Declarations --------------- */

/* --------------- Section: Data Type Declarations --------------- */
typedef struct 
{
    
} bluetooth_module_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * A software Interface initializes a bluetooth module 
 * device using UART Communication Protocol.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Bluetooth_Init(void);
/**
 * A software Interface de-initializes a bluetooth module 
 * device using UART Communication Protocol.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Bluetooth_DeInit(void);
/**
 * A software Interface Sends a byte over the bluetooth module.
 * @param byte : The byte to be sent.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType Bluetooth_Send_Byte(const uint8_t byte);
/**
 * A software Interface Reads a byte with the bluetooth module.
 * @param byte : Pointer to the variable in which
 * the byte will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType Bluetooth_Get_Byte(uint8_t *byte);


#endif	/* BLUETOOTH_MODULE_H */

