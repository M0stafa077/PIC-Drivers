/* 
 * File:   i2c.h
 * Author: Mostafa Asaad
 * https://github.com/M0stafa077
 * Created on April 15, 2024, 10:18 PM
 */

#ifndef I2C_H
#define	I2C_H

/* --------------- Section : Includes --------------- */
#include <pic18f4620.h>
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */
#define I2C_MODULE_ENABLE               STD_ENABLE 
#define I2C_MODULE_DISABLE              STD_DISABLE

#define I2C_MASTER_MODE                 STD_HIGH
#define I2C_SLAVE_MODE                  STD_LOW

#define I2C_START_CONDITION_DETECTED    STD_HIGH
#define I2C_STOP_CONDITION_DETECTED     STD_HIGH

#define I2C_ACK_RECEIVED                STD_LOW
#define I2C_NOT_ACK_RECEIVED            STD_HIGH

#define I2C_GENERAL_CALL_ENABLE         STD_ENABLE
#define I2C_GENERAL_CALL_DISABLE        STD_DISABLE

#define I2C_SLEW_RATE_ENABLE            STD_ENABLE
#define I2C_SLEW_RATE_DISABLE           STD_DISABLE

#define I2C_SMBUS_ENABLE                STD_ENABLE
#define I2C_SMBUS_DISABLE               STD_DISABLE

#define I2C_MASTER_ACK                  STD_LOW
#define I2C_MASTER_NACK                 STD_HIGH
/* --------------- Section: Macro Functions Declarations --------------- */

/*
 * A function-like-macro enables the MSSP module.
 */
#define I2C_MODULE_SET_ENABLE()         (SSPCON1bits.SSPEN = I2C_MODULE_ENABLE)
/*
 * A function-like-macro disables the MSSP module
 */
#define I2C_MODULE_SET_DISABLE()        (SSPCON1bits.SSPEN = I2C_MODULE_DISABLE)
/*
 * A function-like-macro configures the SDA pin
 * as output.
 */
#define I2C_SDA_SET_OUTPUT()            (TRISCbits.RC4 = GPIO_DIRECTION_OUTPUT)
/*
 * A function-like-macro configures the SDA pin
 * as input.
 */
#define I2C_SDA_SET_INPUT()             (TRISCbits.RC4 = GPIO_DIRECTION_INPUT)
/*
 * A function-like-macro configures the SCL pin
 * as output.
 */
#define I2C_SCL_SET_OUTOUT()            (TRISCbits.RC3 = GPIO_DIRECTION_OUTPUT)
/*
 * A function-like-macro configures the SCL pin
 * as input.
 */
#define I2C_SCL_SET_INPUT()             (TRISCbits.RC3 = GPIO_DIRECTION_INPUT)
/*
 * A function-like-macro configures the I2C mode.
 * @ref Chose mode from i2c_mode_config_t ENUM.
 * @note any selection of I2C modes forces The SDA and SCL
 * dio pins to be open-drain configured. So external pull-up
 * resistors must be provided to the SCL and SDA lines.
 */
#define I2C_SET_MODE(MODE)              (SSPCON1bits.SSPM = MODE)

/*
 * A function-like-macro sends a START condition.
 */
#define I2C_MASTER_START_CONDITION()    (SSPCON2bits.SEN = STD_HIGH)

/*
 * A function-like-macro sends a STOP condition.
 */
#define I2C_MASTER_STOP_CONDITION()    (SSPCON2bits.PEN = STD_HIGH)
/*
 * A function-like-macro clears the write collision
 * detect bit
 */
#define I2C_CLR_WCOL_BIT()              (SSPCON1bits.WCOL = STD_LOW)
/*
 * A function-like-macro gets the value of the write collision
 * detect bit
 */
#define I2C_WRITE_COLLISION_STATE()     (SSPCON1bits.WCOL)
/*
 * A function-like-macro clears the overflow
 * indicator bit
 */
#define I2C_CLR_SSPOV_BIT()             (SSPCON1bits.SSPOV = STD_LOW)
/*
 * A function-like-macro gets the value of the overflow
 * indicator bit.
 */
#define I2C_OVERFLOW_STATE()            (SSPCON1bits.SSPOV)

/*
 * A function-like-macro enables the 
 * general call for the I2C slave mode.
 */
#define I2C_GENERAL_CALL_SET_ENABLE()   (SSPCON2bits.GCEN = I2C_GENERAL_CALL_ENABLE)
/*
 * A function-like-macro disables the 
 * general call for the I2C slave mode.
 */
#define I2C_GENERAL_CALL_SET_DISABLE()  (SSPCON2bits.GCEN = I2C_GENERAL_CALL_DISABLE)

/*
 * A function-like-macro releases the
 * clock line of the I2C mode.
 */
#define I2C_RELEASE_SCL()               (SSPCON1bits.CKP = STD_HIGH)

/*
 * A function-like-macro holds the
 * clock line of the I2C mode (clock stretching).
 */
#define I2C_HOLD_SCL()                  (SSPCON1bits.CKP = STD_LOW)

/*
 * A function-like-macro enables the 
 * slew-rate for the i2c mode.
 */
#define I2C_SLEW_RATE_SET_ENABLE()      (SSPSTATbits.SMP = I2C_SLEW_RATE_ENABLE)

/*
 * A function-like-macro disables the 
 * slew-rate for the i2c mode.
 */
#define I2C_SLEW_RATE_SET_DISABLE()     (SSPSTATbits.SMP = I2C_SLEW_RATE_DISABLE)

/*
 * A function-like-macro enables the 
 * SMBUS in the I2C mode.
 */
#define I2C_SMBUS_SET_ENABLE()          (SSPSTATbits.CKE = I2C_SMBUS_ENABLE)
/*
 * A function-like-macro disables the 
 * SMBUS in the I2C mode.
 */
#define I2C_SMBUS_SET_DISABLE()         (SSPSTATbits.CKE = I2C_SMBUS_DISABLE)  

/*
 * A function-like-macro waits blockingly 
 * for an event.
 */
#define WAIT(SOME_THING)                (while(SOME_THING))

#define I2C_START_STATUS()              (SSPSTATbits.START)
#define I2C_STOP_STATUS()               (SSPSTATbits.STOP)

#define I2C_MASTER_RECEIVE_ENABLE()     (SSPCON2bits.RCEN = STD_HIGH)
/* --------------- Section: Data Type Declarations --------------- */
typedef enum
{
    I2C_SLAVE_MODE_7BIT_ADDRESS_NO_INTERRUPT    = 0b0110,
    I2C_SLAVE_MODE_10BIT_ADDRESS_NO_INTERRUPT   = 0b0111,
    I2C_MASTER_MODE_SSPADD_CLOCK                = 0b1000,
    I2C_MASTER_MODE_SW_CLOCK                    = 0b1011,
    I2C_SLAVE_MODE_7BIT_ADDRESS_WITH_INTERRUPT  = 0b1110,
    I2C_SLAVE_MODE_10BIT_ADDRESS_WITH_INTERRUPT = 0b1111
} i2c_mode_config_t;

typedef struct 
{
    /* The device address if in Slave mode */
    uint8_t i2c_slave_address;
    i2c_mode_config_t i2c_mode_config;
    /*
     * I2C Mode.
     * Master or Slave
     */
    uint8_t i2c_mode                    :1;
    uint8_t i2c_slew_rate_stat          :1;
    uint8_t i2c_SMBus_stat              :1;
    uint8_t i2c_general_call_stat       :1;
    uint8_t i2c_master_receiver_stat    :1;
    uint8_t i2c_reserved_bits           :3;
} i2c_config_t;

typedef struct
{
    /*
     * The master clock frequency.
     */
    uint32_t i2c_master_clock_freq;
    /*
     * A callBack pointer to function handles 
     * the write collision
     */
    interrupt_handler_t i2c_write_collision_handler;
    /*
     * A callBack pointer to function handles 
     * the receive overflow
     */
    interrupt_handler_t i2c_receive_overflow_handler;
    /*
     * I2C default interrupt handler
     */
    interrupt_handler_t i2c_default_interrupt_handler;
    /*
     * I2C interrupt priority.
     */
    interrupt_priority_t i2c_interrupt_priority;
    /*
     * The I2C configurations
     */
    i2c_config_t i2c_cfg;
} i2c_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief A software interface initializes the 
 * MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Init(const i2c_t *i2c_obj);
/**
 * @brief A software interface de-initializes the 
 * MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj);
/**
 * @brief A software interface sends a start condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Start(const i2c_t *i2c_obj);
/**
 * @brief A software interface sends a repeated start condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj);
/**
 * @brief A software interface sends a stop condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Stop(const i2c_t *i2c_obj);
/**
 * @brief A software interface writes a byte on the
 * I2C bus.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @param data The data to be written on the I2C bus.
 * @param ack_state a pointer to a uint8_t to hold the 
 * acknowledge state received from the receiver.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Write_Byte_Blocking(const i2c_t *i2c_obj, const uint8_t data, uint8_t *ack_state);
/**
 * @brief A software interface reads from the 
 * I2C bus.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @param data A pointer to the variable holding the read byte.
 * @param ack Acknowledge or not Acknowledge 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Read_Byte_Blocking(const i2c_t *i2c_obj, uint8_t ack, uint8_t *data);

#endif	/* I2C_H */

