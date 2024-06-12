/* 
 * File:   i2c.h
 * Author: Mostafa Asaad
 * https://github.com/M0stafa077
 * Created on April 15, 2024, 10:18 PM
 */

/* --------------- Section : Includes --------------- */
#include "i2c.h"
/* --------------- Section : Helper Functions Declarations --------------- */
static void I2C_Interrupt_Cfg(const i2c_t *i2c_obj);
/* --------------- Section : Global Variables --------------- */
static interrupt_handler_t I2C_Default_Interrupt_Handler = NULL;
static interrupt_handler_t I2C_Default_Write_Collision_Handler = NULL;
static interrupt_handler_t I2C_Default_Overflow_Handler = NULL;
/* --------------- Section : Functions Definitions --------------- */

/**
 * @brief A software interface initializes the 
 * MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Init(const i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable the MSSP module */
        I2C_MODULE_SET_DISABLE();
        
        /* 2. Configure the I2C mode */
        I2C_SET_MODE((i2c_obj->i2c_cfg.i2c_mode_config));
        
        switch(i2c_obj->i2c_cfg.i2c_mode)
        {
            case I2C_MASTER_MODE :
                /* Configure the clock */
                switch(i2c_obj->i2c_cfg.i2c_mode_config)
                {
                    case I2C_MASTER_MODE_SW_CLOCK: /* NOT DETERMINED */
                        break;
                    case I2C_MASTER_MODE_SSPADD_CLOCK:
                        SSPADD = (uint8_t) (((_XTAL_FREQ / 4.0) / (i2c_obj->i2c_master_clock_freq)) - 1);
                        break;
                    default: /* Nothing */
                        break;
                }  
               break;
           case I2C_SLAVE_MODE :
               /* 1. Configure the general call */
               switch(i2c_obj->i2c_cfg.i2c_general_call_stat)
               {
                   case I2C_GENERAL_CALL_ENABLE : I2C_GENERAL_CALL_SET_ENABLE();
                                            break;
                   case I2C_GENERAL_CALL_DISABLE : I2C_GENERAL_CALL_SET_DISABLE();
                                                break;
                   default : I2C_GENERAL_CALL_SET_DISABLE();
                       break;
               }
               
               /* 2. Clear write collision detect bit */
               I2C_CLR_WCOL_BIT();
               
               /* 3. Clear the overflow indicator bit */
               I2C_CLR_SSPOV_BIT();
               
               /* 4. Release the clock line */
               I2C_RELEASE_SCL();
               
               /* 5. Assign the device Slave address */
               SSPADD = (i2c_obj -> i2c_cfg.i2c_slave_address);
               break;
           default : 
               ret = E_NOT_OK;
               break; 
        }
        
        /* Configure the GPIO pins for the I2C mode */
        I2C_SDA_SET_INPUT();
        I2C_SCL_SET_INPUT();
        
        /* Configure the slew rate */
        switch(i2c_obj -> i2c_cfg.i2c_slew_rate_stat)
        {
            case I2C_SLEW_RATE_ENABLE: I2C_SLEW_RATE_SET_ENABLE();
                                    break;  
            case I2C_SLEW_RATE_DISABLE: I2C_SLEW_RATE_SET_DISABLE();
                                    break;  
            default : I2C_SLEW_RATE_SET_DISABLE();
                break;
        }
        
        /* Configure the SMBUS */
        switch(i2c_obj -> i2c_cfg.i2c_SMBus_stat)
        {
            case I2C_SMBUS_ENABLE : I2C_SMBUS_SET_ENABLE();
                                break;  
            case I2C_SMBUS_DISABLE :  /* The same as the default */
            default : I2C_SMBUS_SET_DISABLE();
                                break; 
        }
        
        /* Configure the interrupts */
        I2C_Interrupt_Cfg(i2c_obj);
        
        /* Enable the I2C module */
        I2C_MODULE_SET_ENABLE();
    }
    return ret;
}

/**
 * @brief A software interface de-initializes the 
 * MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_DeInit(const i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/**
 * @brief A software interface sends a start condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Start(const i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Set the START Enable bit */
        I2C_MASTER_START_CONDITION();
        /* Wait for the START condition to be transmitted on the bus */
        WAIT(SSPCON2bits.SEN);
        /* Clear the Interrupt flag */
        INTI_I2C_CLR_FLAG();
        /* Check the detection of the start condition on the bus */
        if(I2C_START_CONDITION_DETECTED == I2C_START_STATUS)
        {
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * @brief A software interface sends a repeated start condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Repeated_Start(const i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Set the START Enable bit */
        I2C_MASTER_START_CONDITION();
        /* Wait for the START condition to be transmitted on the bus */
        WAIT(SSPCON2bits.RSEN);
        /* Clear the Interrupt flag */
        INTI_I2C_CLR_FLAG();
    }
    return ret;
}

/**
 * @brief A software interface sends a stop condition
 * for the MSSP module in I2C mode.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Master_Send_Stop(const i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/**
 * @brief A software interface writes a byte on the
 * I2C bus.
 * @param i2c_obj A pointer to an i2c configuration
 * structure
 * @param data The data to be written on the I2C bus.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType I2C_Write_Byte(const i2c_t *i2c_obj, const uint8_t data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

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
Std_ReturnType I2C_Read_Byte(const i2c_t *i2c_obj, uint8_t ack, uint8_t *data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == i2c_obj || NULL == data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/* --------------- Section : Helper Functions Definitions --------------- */
static void I2C_Interrupt_Cfg(const i2c_t *i2c_obj)
{
/* Enable the Interrupts for the SPI module */
    INTI_I2C_INTERRUPT_ENABLE();
    /* Assign the Interrupt handlers */
    I2C_Default_Interrupt_Handler = i2c_obj -> i2c_default_interrupt_handler;
    I2C_Default_Write_Collision_Handler = i2c_obj->i2c_write_collision_handler;
    I2C_Default_Overflow_Handler = i2c_obj->i2c_receive_overflow_handler;
    
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE
        /* Enable the Interrupt priority feature */
        INTERRUPT_PRIORITY_ENABLE();
        /* Assign the specified interrupt priority */
        if(PRIORITY_HIGH == i2c_obj -> i2c_interrupt_priority)
        {
            INTERRUPT_GIEH_ENABLE();
            INTI_SPI_INTERRUPT_PRIORITY_HIGH();
        }
        else if(PRIORITY_LOW == i2c_obj->i2c_interrupt_priority)
        {
            INTERRUPT_GIEL_ENABLE();
            INTI_SPI_INTERRUPT_PRIORITY_LOW();
        }
        else
            { /* Nothing */ }
#else         
        INTERRUPT_GIEH_ENABLE();
        INTERRUPT_GIEL_ENABLE();
#endif
}

void I2C_ISR(void)
{
    /* Clear the interrupt flag */
    INTI_I2C_CLR_FLAG();
    
    /* 2. Call the interrupt service routine function */
    if(I2C_Default_Interrupt_Handler)
    {
        I2C_Default_Interrupt_Handler();
    }
}

void I2C_Write_Collision_ISr(void)
{
    
}