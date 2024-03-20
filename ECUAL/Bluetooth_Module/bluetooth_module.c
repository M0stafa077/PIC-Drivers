/* 
 * File:   bluetooth_module.h
 * Author: Mostafa Asaad
 *
 * Created on February 18, 2024, 6:59 PM
 */
/* --------------- Section : Includes --------------- */
#include "bluetooth_module.h"

/*---------------  Section: Helper Functions Declarations --------------- */
void BLE_RX_ISR(void);
/* --------------- Section : Global Variables --------------- */
volatile uint8_t read_val = NULL;

usart_t usart_Obj = 
{
    .EUSART_TX_InterruptHandler = NULL,
    .EUSART_RX_InterruptHandler = BLE_RX_ISR,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL,
    
    .baudrate = 9600,
    .baudrate_generator_gonfigs = BAUDRATE_ASYN_8BIT_lOW_SPEED, /* 8-Bit with low speed BRG */
    
    .usart_tx_cfgs.usart_tx_enable = EUSART_ASYNC_TX_ENABLE,
    .usart_tx_cfgs.usart_tx_interrupt_enable = EUSART_ASYNC_INTERRUPT_TX_ENABLE,
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    .usart_tx_cfgs.usart_tx_interrupt_priority = PRIORITY_HIGH,
#endif
    .usart_tx_cfgs.usart_tx_9bit_enable = EUSART_ASYNC_9BIT_TX_DISABLE,

    .usart_rx_cfgs.usart_rx_enable = EUSART_ASYNC_RX_ENABLE,
    .usart_rx_cfgs.usart_rx_interrupt_enable = EUSART_ASYNC_INTERRUPT_RX_ENABLE,
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    .usart_rx_cfgs.usart_rx_interrupt_priority = PRIORITY_HIGH,
#endif
    .usart_rx_cfgs.usart_rx_9bit_enable = EUSART_ASYNC_9BIT_RX_DISABLE
};

/*---------------  Section: Function Definitions --------------- */
Std_ReturnType Bluetooth_Init(void)
{
    Std_ReturnType ret = E_OK;
    
    ret = USART_ASYNC_Init(&usart_Obj);

    return ret;
}

/**
 * A software Interface de-initializes a bluetooth module 
 * device using UART Communication Protocol.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType Bluetooth_DeInit(void)
{
    Std_ReturnType ret = E_OK;
    
    ret = USART_ASYNC_DeInit(&usart_Obj);
    
    return ret;
}

Std_ReturnType Bluetooth_Send_Byte(const uint8_t byte)
{
    Std_ReturnType ret = E_OK;
    
    ret = USART_ASYNC_Write_Byte_With_NoBlocking(byte);
    
    return ret;
}
Std_ReturnType Bluetooth_Get_Byte(uint8_t *byte)
{
    Std_ReturnType ret = E_OK;
    if(NULL == byte)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *byte = read_val;
    }
    return ret;  
}

/*---------------  Section: Helper Functions Declarations --------------- */
void BLE_RX_ISR(void)
{
    USART_ASYNC_Read_Byte_With_NoBlocking(&read_val);
}