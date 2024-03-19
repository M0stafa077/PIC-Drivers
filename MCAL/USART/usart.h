    /* 
 * File:   usart.h
 * Author: Mostafa Asaad
 *
 * Created on February 15, 2024, 4:34 PM
 */

#ifndef USART_H
#define	USART_H

/* --------------- Section : Includes --------------- */
#include "usart.h"
#include "../DIO/DIO.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */
/*
 * The USART Module is enabled.
 */
#define EUSART_ENABLE                       STD_ENABLE
/*
 * The USART Module is disabled.
 */
#define EUSART_DISABLE                      STD_DISABLE
/*
 * EUSART Module Synchronous mode.
 */
#define EUSART_SYNC_MODE                    STD_TRUE
/*
 * EUSART Module ASynchronous mode.
 */
#define EUSART_ASYNC_MODE                   STD_FALSE
/*
 * EUSART Baud Rate Generator high speed
 * in Asynchronous mode.
 */
#define EUSART_ASYNC_BRG_HIGH_SPEED         STD_TRUE
/*
 * EUSART Baud Rate Generator low speed
 * in Asynchronous mode.
 */
#define EUSART_ASYNC_BRG_LOW_SPEED          STD_FALSE
/*
 * EUSART Baud Rate Generator 
 * with 16-bit Register.
 */
#define EUSART_BRG_16BIT_REG                STD_TRUE
/*
 * EUSART Baud Rate Generator 
 * with 8-bit Register.
 */
#define EUSART_BRG_8BIT_REG                 STD_FALSE
/* ============== EUSART TX Configurations ============== */
/*  
 * EUSART ASynchronous transmission 
 * mode enable.
 */
#define EUSART_ASYNC_TX_ENABLE              STD_ENABLE
/*
 * EUSART ASynchronous transmission 
 * mode disable.
 */
#define EUSART_ASYNC_TX_DISABLE             STD_DISABLE
/* 
 * EUSART ASynchronous transmission 
 * Interrupt enable.
 */
#define EUSART_ASYNC_INTERRUPT_TX_ENABLE    STD_TRUE
/* 
 * EUSART ASynchronous transmission 
 * Interrupt disable. 
 */
#define EUSART_ASYNC_INTERRUPT_TX_DISABLE   STD_FALSE
/* 
 * EUSART ASynchronous 9-Bit 
 * transmission enable. 
 */
#define EUSART_ASYNC_9BIT_TX_ENABLE         STD_TRUE
/* 
 * EUSART ASynchronous 9-Bit 
 * transmission disable. 
 */
#define EUSART_ASYNC_9BIT_TX_DISABLE        STD_FALSE
/* ============== EUSART RX Configurations ============== */
/*
 * EUSART ASynchronous reception 
 * mode enable.
 */
#define EUSART_ASYNC_RX_ENABLE              STD_ENABLE
/*
 * EUSART ASynchronous reception 
 * mode disable.
 */
#define EUSART_ASYNC_RX_DISABLE             STD_DISABLE
/* 
 * EUSART ASynchronous reception 
 * Interrupt enable. 
 */
#define EUSART_ASYNC_INTERRUPT_RX_ENABLE    STD_TRUE
/* 
 * EUSART ASynchronous reception 
 * Interrupt disable.
 */
#define EUSART_ASYNC_INTERRUPT_RX_DISABLE   STD_FALSE
/* 
 * EUSART ASynchronous 9-Bit 
 * reception enable.
 */
#define EUSART_ASYNC_9BIT_RX_ENABLE         STD_TRUE
/* 
 * EUSART ASynchronous 9-Bit 
 * reception disable.
 */
#define EUSART_ASYNC_9BIT_RX_DISABLE        STD_FALSE
/* ===================== EUSART Framing Error ===================== */
/*
 * EUSART Framing Error occurred.
 */
#define EUSART_FRAMING_ERROR_DETECTED       STD_TRUE
/*
 * EUSART Framing Error cleared.
 */
#define EUSART_FRAMING_ERROR_CLEARED        STD_FALSE
/* ===================== EUSART Overrun Error ===================== */
/*
 * EUSART Overrun Error occurred.
 */
#define EUSART_OVERRUN_ERROR_DETECTED       STD_TRUE
/*
 * EUSART Overrun Error cleared.
 */
#define EUSART_OVERRUN_ERROR_CLEARED        STD_FALSE

/* --------------- Section: Macro Functions Declarations --------------- */
/*
 * A function-like-macro 
 * enables the EUSART Module.
 */
#define EUSART_MODULE_ENABLE()              (RCSTAbits.SPEN = EUSART_ENABLE)

/*
 * A function-like-macro 
 * disables the EUSART Module.
 */
#define EUSART_MODULE_DISABLE()             (RCSTAbits.SPEN = EUSART_DISABLE)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * synchronous mode.
 */
#define EUSART_SET_SYNC()                   (TXSTAbits.SYNC = EUSART_SYNC_MODE)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * Asynchronous mode.
 */
#define EUSART_SET_ASYNC()                  (TXSTAbits.SYNC = EUSART_ASYNC_MODE)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * Asynchronous high speed mode.
 */
#define EUSART_SET_HIGH_SPEED()             (TXSTAbits.BRGH = EUSART_ASYNC_BRG_HIGH_SPEED)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * Asynchronous low speed mode.
 */
#define EUSART_SET_LOW_SPEED()              (TXSTAbits.BRGH = EUSART_ASYNC_BRG_LOW_SPEED)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * 16-Bit Register mode.
 */
#define EUSART_SET_16_BIT()                 (BAUDCONbits.BRG16 = EUSART_BRG_16BIT_REG)

/*
 * A function-like-macro 
 * configures the EUSART Module in the 
 * 8-Bit Register mode.
 */
#define EUSART_SET_8_BIT()                  (BAUDCONbits.BRG16 = EUSART_BRG_8BIT_REG)

/*
 * A function-like-macro 
 * enables the transmission mode.
 */
#define EUSART_ASYNC_TX_SET_ENABLE()        (TXSTAbits.TXEN = EUSART_ASYNC_TX_ENABLE)
/*
 * A function-like-macro 
 * disables the transmission mode.
 */
#define EUSART_ASYNC_TX_SET_DISABLE()       (TXSTAbits.TXEN = EUSART_ASYNC_TX_DISABLE)

/*
 * A function-like-macro 
 * enables the 9-bits transmission mode.
 */
#define EUSART_9BIT_TX_SET_ENABLE()         (TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_ENABLE)
/*
 * A function-like-macro 
 * disables the 9-bits transmission mode.
 */
#define EUSART_9BIT_TX_SET_DISABLE()        (TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_DISABLE)

/*
 * A function-like-macro 
 * enables the reception mode.
 */
#define EUSART_ASYNC_RX_SET_ENABLE()        (RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE)
/*
 * A function-like-macro 
 * disables the reception mode.
 */
#define EUSART_ASYNC_RX_SET_DISABLE()       (RCSTAbits.CREN = EUSART_ASYNC_RX_DISABLE)

/*
 * A function-like-macro 
 * enables the 9-bits reception mode.
 */
#define EUSART_9BIT_RX_SET_ENABLE()         (RCSTAbits.RC9 = EUSART_ASYNC_9BIT_RX_ENABLE)
/*
 * A function-like-macro 
 * disables the 9-bits reception mode.
 */
#define EUSART_9BIT_RX_SET_DISABLE()        (RCSTAbits.RC9 = EUSART_ASYNC_9BIT_RX_DISABLE)

/*
 * A function-like-macro 
 * Configures pin 6 in portc
 * as input pin.
 */
#define EUSART_SET_PORTC_PIN6()             (TRISCbits.RC6 = GPIO_DIRECTION_INPUT)
/*
 * A function-like-macro 
 * Configures pin 7 in portc
 * as input pin.
 */
#define EUSART_SET_PORTC_PIN7()             (TRISCbits.RC7 = GPIO_DIRECTION_INPUT)
/* --------------- Section: Data Type Declarations --------------- */
/*
 * BRG Configurations.
 */
typedef enum
{
    /*
     * For Asynchronous, Low speed BRG 
     * with 8-Bit Register.
     */
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    /*
     * For Asynchronous, High speed BRG 
     * with 8-Bit Register.
     */
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    /*
     * For Asynchronous, Low speed BRG 
     * with 16-Bit Register.
     */
    BAUDRATE_ASYN_16BIT_lOW_SPEED,
    /*
     * For Asynchronous, High speed BRG 
     * with 16-Bit Register.
     */
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    /*
     * For Synchronous mode
     * with 8-bit BRG register.
     */
    BAUDRATE_SYN_8BIT,
    /*
     * For Synchronous mode
     * with 16-bit BRG register.
     */
    BAUDRATE_SYN_16BIT
}  BRG_t;

/*
 * USART Transmission mode configurations.
 */
typedef struct
{
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /*
     * The interrupt priority for the 
     * transmission mode.
     *  (PRIORITY_HIGH) 
     *  or 
     *  (PRIORITY_LOW)
     */
    interrupt_priority_t usart_tx_interrupt_priority;
    /*
     * The status of the transmission mode.
     * (EUSART_ASYNC_TX_ENABLE) 
     * or 
     * (EUSART_ASYNC_TX_DISABLE).
     */
#endif
#endif
	uint8_t usart_tx_enable             : 1;
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /*
     * The interrupt status for the transmission mode.
     * (EUSART_ASYNC_INTERRUPT_TX_ENABLE) 
     * or 
     * (EUSART_ASYNC_INTERRUPT_TX_DISABLE)
     */
	uint8_t usart_tx_interrupt_enable   : 1;
#endif
    /*
     * The 9bit configuration for the transmission mode.
     * (EUSART_ASYNC_9BIT_TX_ENABLE) 
     * or 
     * (EUSART_ASYNC_9BIT_TX_DISABLE)
     */
	uint8_t usart_tx_9bit_enable        : 1;
    /*
     * Five reserved bits.
     * (Not Implemented).
     */
    uint8_t usart_tx_reserved           : 5;
} usart_tx_cfg_t;

/*
 * USART Reception mode configurations.
 */
typedef struct
{
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /*
     * The interrupt priority for the 
     * reception mode.
     */
    interrupt_priority_t usart_rx_interrupt_priority;
#endif
    /*
     * The status of the reception mode.
     * (EUSART_ASYNC_RX_ENABLE) 
     * or 
     * (EUSART_ASYNC_RX_DISABLE).
     */
	uint8_t usart_rx_enable             : 1;
#if EUSART_RX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /*
     * The interrupt status for the reception mode.
     * (EUSART_ASYNC_INTERRUPT_RX_ENABLE) 
     * or 
     * (EUSART_ASYNC_INTERRUPT_RX_DISABLE)
     */
	uint8_t usart_rx_interrupt_enable   : 1;
#endif
    /*
     * The 9bit configuration for the reception mode.
     * (EUSART_ASYNC_9BIT_RX_ENABLE) 
     * or 
     * (EUSART_ASYNC_9BIT_RX_DISABLE)
     */
	uint8_t usart_rx_9bit_enable        : 1;
    /*
     * Five reserved bits.
     * (Not Implemented).
     */
    uint8_t usart_rx_reserved           : 5;
} usart_rx_cfg_t;

/*
 * USART Module error status.
 */
typedef union
{
	struct
    {
        /*
         * Six reserved bits.
         * (Not Implemented).
        */
		uint8_t usart_tx_reserved   : 6;
        /*
         * USART Framing error status.
         */
		uint8_t usart_frame_error   : 1;
        /*
         * USART Framing overrun error status.
         */
		uint8_t usart_overrun_error : 1;
	};
    /*
     * USART Module error status.
     */
	uint8_t usart_error_status;
} usart_error_status_t;

/*
 * A struct describes an object of the USART module.
 */
typedef struct
{
    /*
     * The interrupt service routine 
     * for the transmission mode.
     */
    interrupt_handler_t EUSART_TX_InterruptHandler;
    /*
     * The interrupt service routine 
     * for the reception mode.
     */
    interrupt_handler_t EUSART_RX_InterruptHandler;
    /*
     * The interrupt service routine 
     * for the framing error.
     */
    interrupt_handler_t EUSART_FramingErrorHandler;
    /*
     * The interrupt service routine 
     * for the overrun error.
     */
    interrupt_handler_t EUSART_OverrunErrorHandler;
    /*
     * The operating baud rate 
     * for the USART module.
     */
    uint32_t baudrate;
    /*
     * The configurations for the BRG.
     */
    BRG_t baudrate_generator_gonfigs;
    /*
     * The configurations for the
     * transmission mode.
     */
    usart_tx_cfg_t usart_tx_cfgs;
    /*
     * The configurations for the
     * reception mode.
     */
	usart_rx_cfg_t usart_rx_cfgs;
    /*
     * The error status for 
     * the USART module.
     */
	usart_error_status_t error_status;
} usart_t;
/*---------------  Section: Function Declarations --------------- */
/**
 * A helper software interface initializes the 
 * usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Init(const usart_t *usart_Obj);
/*
 * A helper software interface de-initializes the
 * usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_DeInit(const usart_t *usart_Obj);
/**
 * A helper software interface reads a byte with 
 * the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @param byte_read
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Read_Byte_With_Blocking(uint8_t *byte_read);
/**
 * A helper software interface reads a byte with 
 * the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @param byte_read : A pointer to the byte in which the data
 *                      will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Read_Byte_With_NoBlocking(uint8_t *byte_read);
/**
 * A helper software interface sends/writes a 
 * byte with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_Byte_With_Blocking(const uint8_t byte_written);
/**
 * A helper software interface sends/writes a 
 * byte with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_read : The byte to be written.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_Byte_With_NoBlocking(const uint8_t byte_written);

/**
 * A helper software interface sends/writes a 
 * string with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_String_With_Blocking(const uint8_t *string_written);
/**
 * A helper software interface sends/writes a 
 * byte with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_String_With_NoBlocking(const uint8_t *string_written);
/**
 * A helper software interface sends/writes a 
 * number with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_Number_With_Blocking(const sint32_t number_written);
/**
 * A helper software interface sends/writes a 
 * number with the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Write_Number_With_NoBlocking(const sint32_t number_written);

#endif	/* USART_H */
