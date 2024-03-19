/* 
 * File:   spi.c
 * Author: Mostafa Asaad
 *
 * Created on February 24, 2024, 3:04 PM
 */

#include "spi.h"

#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static interrupt_handler_t SPI_Interrupt_Handler = NULL;
static void SPI_Interrupt_Init(const SPI_Slave_t *_spi);
#endif
/*---------------  Section: Function Definitions --------------- */
/**
 * A software Interface initializes the SPI
 * module as a Master
 * @param _spi : A pointer to the SPI module configurations
 * in Master mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Init_Master(const SPI_Master_t *_spi)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _spi)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable SPI MODULE*/
        SPI_MODULE_DISABLE();
        /* 2. Configure SPI GPIO Pins */
        TRISCbits.RC4 = 1;	/* RC4 as input(SDI) */
        TRISCbits.RC3 = 0;	/* RC3 as output(SCK) */
        TRISAbits.RA5 = 0;	/* RA5 as output(SS') */
        TRISCbits.RC5 = 0;	/* RC5 as output(SDO) */
        /* 3. Configure the Interrupts */
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        SPI_Interrupt_Init(_spi);
#endif
        /* 3. Select Clock Polarity */
        SPI_CLOCK_POLARITY_CONFIG(_spi->Clock_Idle_State_Mode);
        /* 4. Select Clock Phase */
        SPI_CLOCK_PHASE_CONFIG(_spi->Clock_Phase_Mode);
        /* 5. Select Sampled master Mode */
        SPI_MASTER_SAMPLED_DATA_CONFIG(_spi->sample_data);
        /* 6. Select Master Clock Rate and Slave Mode*/
        SPI_MASTER_CLOCK_RATE(_spi->master_clk_rate);
        /* 7. Enable SPI MODULE*/        
        SPI_MODULE_ENABLE();
    }
    return ret;
}
/**
 * A software Interface initializes the SPI
 * module as a Slave.
 * @param _spi : A pointer to the SPI module configurations
 * in Slave mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Init_Slave(const SPI_Slave_t *_spi)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _spi)
    {
        ret = E_NOT_OK;
    }
    else{
        /* 1. Disable SPI MODULE*/
        SPI_MODULE_DISABLE();
        /* 2. Configure SPI GPIO Pins */
        TRISCbits.RC4 = 1;	/* RC4 as input(SDI) */
        TRISCbits.RC3 = 1;	/* RC3 as input(SCK) */
        TRISAbits.RA5 = 1;	/* RA5 as input(SS') */
        TRISCbits.RC5 = 0;	/* RC5 as output(SDO) */
        /* 3. Interrupt Configure */
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        SPI_Interrupt_Init(_spi);
#endif
        /* 4. Select Clock Polarity */
        SPI_CLOCK_POLARITY_CONFIG(_spi->clock_idle);
        /* 5. Select Clock Phase */
        SPI_CLOCK_PHASE_CONFIG(_spi->clock_phase);
        /* 6. configure SMP Bit */
        SPI_MASTER_SAMPLED_DATA_CONFIG(0);
        /* 7. Select Slave Mode */
        SPI_SLAVE_MODE_SELECT(_spi->slave_mode);
        /* 8. Enable SPI MODULE*/        
        SPI_MODULE_ENABLE();
    }
    return ret;
}
/**
 * A software Interface de-initializes the SPI
 * module as a Master
 * @param _spi : A pointer to the SPI module configurations
 * in Master mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_DeInit_Master(const SPI_Master_t *_spi)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _spi)
    {
        ret = E_NOT_OK;
    }
    else{
        /* 1. Disable SPI MODULE*/        
        SPI_MODULE_DISABLE();
        /* 2. Disable Interrupt */
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        INTI_SPI_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
/**
 * A software Interface de-initializes the SPI
 * module as a Slave.
 * @param _spi : A pointer to the SPI module configurations
 * in Slave mode.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_DeInit_Slave(const SPI_Slave_t *_spi)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _spi)
    {
        ret = E_NOT_OK;
    }
    else{
        /* 1. Disable SPI MODULE*/        
        SPI_MODULE_DISABLE();
        /* 2. Disable Interrupt */
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
        INTI_SPI_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
/*
 * A software interface reads the data from the SPI module
 * with blocking technique.
 * @param _data : A pointer to the variable in which the 
 * read data will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Read_Byte_Blocking(uint8_t *_data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(!SSPSTATbits.BF); // Wait for the reception to complete
        *_data = SSPBUF;
    }
    return ret;
}
/**
 * A software interface reads the data from the SPI module
 * with no-blocking technique.
 * @param _data : A pointer to the variable in which the 
 * read data will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Read_Byte_NoBlocking(uint8_t *_data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(PIR1bits.SSPIF)
        {
            *_data = SSPBUF;
            PIR1bits.SSPIF = 0;
        }
        else
            { ret = E_NOT_OK; }
    }
    return ret;
}
/**
 * A software interface sends data via SPI module
 * with blocking technique.
 * @param _data : The data to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_Byte_Blocking( uint8_t _data)
{
    Std_ReturnType ret = E_OK;
    
    uint8_t l_buff_removed = 0;
    SSPBUF = _data; 
    
    while(!SSPSTATbits.BF);
    
    PIR1bits.SSPIF = 0;
    l_buff_removed = SSPBUF;
    
    return ret;
}
/**
 * A software interface sends data via SPI module
 * with no-blocking technique.
 * @param _data : The data to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_Byte_NoBlocking( uint8_t _data)
{
    Std_ReturnType ret = E_OK;
    
    if((STD_HIGH == SSPSTATbits.BF) || (STD_LOW == PIR1bits.SSPIF))
    {
        PIR1bits.SSPIF = STD_LOW;
        SSPBUF = _data;
    }
    return ret;
}
/**
 * A software interface sends a string via SPI module
 * with blocking technique.
 * @param _data : The string to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_String_Blocking( uint8_t *_data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*_data)
        {
            SPI_Write_Byte_Blocking(*_data);
            _data++;
        }
    }
    return ret;
}
/**
 * A software interface sends a string via SPI module
 * with no-blocking technique.
 * @param _data : The string to be sent via SPI module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType SPI_Write_String_NoBlocking( uint8_t *_data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _data)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*_data)
        {
            SPI_Write_Byte_NoBlocking(*_data);
            ++_data;
        }
    }
    return ret;
}

void SPI_ISR(void)
{
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    /* 1. Clear the Interrupt Flag */
    INTI_SPI_CLR_FLAG();
    
    /* 2. Call the interrupt service routine function */
    if(SPI_Interrupt_Handler)
        { SPI_Interrupt_Handler(); }
#endif
}


#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE
static void SPI_Interrupt_Init(const SPI_Slave_t *_spi)
{
    /* Enable the Interrupts for the SPI module */
    INTI_SPI_INTERRUPT_ENABLE();
    /* Assign the Interrupt handler */
    SPI_Interrupt_Handler = _spi -> SPI_InterruptHandler;
    
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE
        /* Enable the Interrupt priority feature */
        INTERRUPT_PRIORITY_ENABLE();
        /* Assign the specified interrupt priority */
        if(PRIORITY_HIGH == _spi -> SPI_priority)
        {
            INTERRUPT_GIEH_ENABLE();
            INTI_SPI_INTERRUPT_PRIORITY_HIGH();
        }
        else if(PRIORITY_LOW == _spi->SPI_priority)
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
#endif