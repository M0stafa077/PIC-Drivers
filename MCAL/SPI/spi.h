/* 
 * File:   spi.h
 * Author: Mostafa Asaad
 *
 * Created on February 24, 2024, 3:04 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H
/*---------------------- Section : Includes ----------------------*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../DIO/DIO.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/*---------------------- Section : Macro Declarations------------ */
/* SPI OverFlow Error */
#define SPI_OVERFLOW_ERROR_DETECTED                 STD_TRUE
/* SPI Collision Error */
#define SPI_COLLISION_ERROR_DETECTED                STD_TRUE
/*---------------------- Section : Macro Functions Declarations --*/
/*
 * A function-like-macro enables 
 * the SPI Module.
 */
#define SPI_MODULE_ENABLE()                                (SSPCON1bits.SSPEN = STD_ENABLE)
/*
 * A function-like-macro disables
 * the SPI Module.
 */
#define SPI_MODULE_DISABLE()                               (SSPCON1bits.SSPEN = STD_DISABLE)
/* SPI OverFlow Error */
/*
 * A function-like-macro returns the status of
 * the overflow error for the SPI module.
 */
#define SPI_OVERFLOW_ERROR_STATUS()                 (SSPCON1bits.SSPOV) 
/*
 * A function-like-macro clears the overflow error 
 * bit for the SPI module.
 */
#define SPI_OVERFLOW_ERROR_CLEAR_BIT()              (SSPCON1bits.SSPOV = STD_LOW) 
/* SPI Collision Error */
#define SPI_COLLISION_ERROR_STATUS()                (SSPCON1bits.WCOL) 
#define SPI_COLLISION_ERROR_CLEAR_BIT()             (SSPCON1bits.WCOL = STD_LOW)
/*
 * A function-like-macro configures the clock
 * polarity for the SPI module 
 */
#define SPI_CLOCK_POLARITY_CONFIG(_CFG)             (SSPCON1bits.CKP = _CFG)
/*
 * A function-like-macro configures the clock
 * phase for the SPI module. 
 */
#define SPI_CLOCK_PHASE_CONFIG(_CFG)                (SSPSTATbits.CKE = _CFG)
/*
 * A function-like-macro configures the sampling
 * mode for the SPI module.
 */
#define SPI_MASTER_SAMPLED_DATA_CONFIG(_CFG)        (SSPSTATbits.SMP = _CFG)
/*
 * A function-like-macro configures the clock rate
 * for the SPI module in Master mode.
 */
#define SPI_MASTER_CLOCK_RATE(_CFG)                 (SSPCON1bits.SSPM = _CFG)
/*
 * A function-like-macro configures the mode for
 * the SPI module in Slave mode
 */
#define SPI_SLAVE_MODE_SELECT(_CFG)                 (SSPCON1bits.SSPM = _CFG)
/* --------------- Section: Data Type Declarations --------------- */
/*
 * An enum contains the clock polarity
 * configurations (Idle state) for the SPI module.
 */
typedef enum
{
    SPI_CLOCK_IDLE_LOW_LEVEL_CFG = 0,
    SPI_CLOCK_IDLE_HIGH_LEVEL_CFG
}SPI_Clock_Polarity_t;

/*
 * An enum contains the clock phase 
 * configurations for the SPI module. 
 */
typedef enum
{
    SPI_CLOCK_PHASE_TRANSMIT_AT_LEADING_EDGE = 0,
    SPI_CLOCK_PHASE_TRANSMIT_AT_TRAILING_EDGE
}SPI_Clock_Phase_t;

/*
 * An enum contains the sampling mode
 * configurations for the SPI module in Master mode.
 */
typedef enum
{
    SPI_MASTER_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME = 0,
    SPI_MASTER_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME,        
}SPI_Master_Sampled_Mode_t;

/*
 * An enum contains the different clock rate 
 * configurations for the SPI module
 * in Master mode.
 */
typedef enum
{
    SPI_MASTER_MODE_CLOCK_FOSC_DEV_4 = 0,
    SPI_MASTER_MODE_CLOCK_FOSC_DEV_16,
    SPI_MASTER_MODE_CLOCK_FOSC_DEV_64,
    SPI_MASTER_MODE_CLOCK_TMR2_OUTPUT_DEV_2,
}SPI_Master_Clock_Rate_t;

/*
 * An enum contains the different configurations
 * of the SPI module in Slave mode.
 */
typedef enum
{
    SPI_SLAVE_MODE_SS_ENABLED = 4,
    SPI_SLAVE_MODE_SS_DISABLED_USED_AS_I_O_PIN = 5,
}SPI_Slave_Mode_t;

/*
 * A struct configures the SPI module 
 * in Master mode.
 */
typedef struct
{
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE  
    /*
     * The interrupt handler for the 
     * SPI module in Master mode.
     * @ref interrupt_handler_t.
     */
     interrupt_handler_t SPI_Interrupt_Handler;
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE
     /*
      * The interrupt Priority for the SPI module
      * in master mode.
      * @ref interrupt_priority_t
      * @Options
      * PRIORITY_HIGH
      * PRIORITY_LOW
      */
     interrupt_priority_t SPI_Interrupt_Priority;
#endif
#endif
     /*
      * The clock polarity for the SPI module
      * in Master mode.
      * @ref SPI_Clock_Polarity_t
      * @Options
      * SPI_CLOCK_IDLE_LOW_LEVEL_CFG
      * SPI_CLOCK_IDLE_HIGH_LEVEL_CFG
      */
    SPI_Clock_Polarity_t Clock_Idle_State_Mode;
    /*
     * The clock phase configuration for the SPI
     * module in Master mode.
     * @ref SPI_Clock_Phase_t
     * @Options
     * SPI_CLOCK_PHASE_TRANSMIT_AT_LEADING_EDGE
     * SPI_CLOCK_PHASE_TRANSMIT_AT_TRAILING_EDGE
     */
    SPI_Clock_Phase_t Clock_Phase_Mode;
    /*
     * The sampling mode for the SPI module 
     * in Master mode.
     * @ref SPI_Master_Sampled_Mode_t
     * @Options 
     * SPI_MASTER_SAMPLED_AT_MIDDLE_OF_DATA_OUTPUT_TIME
     * SPI_MASTER_SAMPLED_AT_END_OF_DATA_OUTPUT_TIME
     */
    SPI_Master_Sampled_Mode_t sample_data;
    /*
     * The clock rate for the SPI module in 
     * Master mode.
     * @ref: SPI_Master_Clock_Rate_t
     * @Options SPI_MASTER_MODE_CLOCK_FOSC_DEV_4
     * SPI_MASTER_MODE_CLOCK_FOSC_DEV_16
     * SPI_MASTER_MODE_CLOCK_FOSC_DEV_64
     * SPI_MASTER_MODE_CLOCK_TMR2_OUTPUT_DEV_2
     */
    SPI_Master_Clock_Rate_t master_clk_rate;
}SPI_Master_t;

/*
 * A struct configures the SPI module 
 * in Master mode.
 */
typedef struct
{
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    /*
     * The interrupt handler for the 
     * SPI module in slave mode.
     * @ref interrupt_handler_t.
     */
     interrupt_handler_t SPI_InterruptHandler;
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE
    /*
     * The interrupt Priority for the SPI module
     * in slave mode.
     * @ref interrupt_priority_t
     * @Options
     * PRIORITY_HIGH
     * PRIORITY_LOW
     */
    interrupt_priority_t SPI_priority ;
#endif
#endif
     /*
      * The clock polarity for the SPI module
      * in Slave mode.
      * @ref SPI_Clock_Polarity_t
      * @Options
      * SPI_CLOCK_IDLE_LOW_LEVEL_CFG
      * SPI_CLOCK_IDLE_HIGH_LEVEL_CFG
      */
    SPI_Clock_Polarity_t clock_idle;
    /*
     * The clock phase configuration for the SPI
     * module in Slave mode.
     * @ref SPI_Clock_Phase_t
     * @Options
     * SPI_CLOCK_PHASE_TRANSMIT_AT_LEADING_EDGE
     * SPI_CLOCK_PHASE_TRANSMIT_AT_TRAILING_EDGE
     */
    SPI_Clock_Phase_t clock_phase;
    /*
     * The slave select pin configuration for the
     * SPI module in Slave mode
     * @ref SPI_Slave_Mode_t
     * @Options
     * SPI_SLAVE_MODE_SS_ENABLED
     * SPI_SLAVE_MODE_SS_DISABLED_USED_AS_I_O_PIN
     */
    SPI_Slave_Mode_t slave_mode;
}SPI_Slave_t;

/*---------------------- Section : Functions Declarations --------*/

/**
 * @brief software Interface initializes the SPI
 * module as a Master
 * @param _spi : A pointer to the SPI module configurations
 * in Master mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Init_Master(const SPI_Master_t *_spi);
/**
 * A software Interface initializes the SPI
 * module as a Slave.
 * @param _spi : A pointer to the SPI module configurations
 * in Slave mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Init_Slave(const SPI_Slave_t *_spi);

/**
 * A software Interface de-initializes the SPI
 * module as a Master
 * @param _spi : A pointer to the SPI module configurations
 * in Master mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_DeInit_Master(const SPI_Master_t *_spi);
/**
 * A software Interface de-initializes the SPI
 * module as a Slave.
 * @param _spi : A pointer to the SPI module configurations
 * in Slave mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_DeInit_Slave(const SPI_Slave_t *_spi);
/**
 * A software interface reads the data from the SPI module
 * with blocking technique.
 * @param _data : A pointer to the variable in which the 
 * read data will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Read_Byte_Blocking(uint8_t *_data);
/**
 * A software interface reads the data from the SPI module
 * with no-blocking technique.
 * @param _data : A pointer to the variable in which the 
 * read data will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Read_Byte_NoBlocking(uint8_t *_data);
/**
 * A software interface sends data via SPI module
 * with blocking technique.
 * @param _data : The data to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_Byte_Blocking( uint8_t _data);
/**
 * A software interface sends data via SPI module
 * with no-blocking technique.
 * @param _data : The data to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_Byte_NoBlocking( uint8_t _data);
/**
 * A software interface sends a string via SPI module
 * with blocking technique.
 * @param _data : The string to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_String_Blocking( uint8_t *_data);
/**
 * A software interface sends a string via SPI module
 * with no-blocking technique.
 * @param _data : The string to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_String_NoBlocking( uint8_t *_data);

#endif	/* HAL_SPI_H */

