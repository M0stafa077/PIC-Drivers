/* 
 * File:   usart.h
 * Author: Mostafa Asaad
 *
 * Created on February 15, 2024, 4:34 PM
 */
/* --------------- Section : Includes --------------- */
#include "usart.h"
/* --------------- Section : Global Variables --------------- */
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t USART_TX_Interrupt_Handler = NULL;
#endif
#if EUSART_RX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
static interrupt_handler_t USART_RX_Interrupt_Handler = NULL;
#endif
static interrupt_handler_t USART_Framing_Error_Handler = NULL;
static interrupt_handler_t USART_Overrun_Error_Handler = NULL;
/*---------------  Section: Helper Functions Declarations --------------- */
/**
 * A helper software interface initializes 
 * the baud rate with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 */
static void USART_ASYNC_BR_Init(const usart_t *usart_Obj);

/**
 * A helper software interface initializes 
 * transmission mode with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 */
static void USART_ASYNC_TX_Init(const usart_t *usart_Obj);

/**
 * A helper software interface initializes 
 * reception mode with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 *                    the USART module.  
 */
static void USART_ASYNC_RX_Init(const usart_t *usart_Obj);
/*---------------  Section: Function Definitions --------------- */
/**
 * A helper software interface initializes the 
 *  usart module.
 * @param usart_Obj : A pointer to an object of 
 *                    the USART module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Init(const usart_t *usart_Obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == usart_Obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable The USART module */
        EUSART_MODULE_DISABLE();
        
        /* 2. Configure pins <6, 7> in PORTC as Input pins */
        EUSART_SET_PORTC_PIN6();
        EUSART_SET_PORTC_PIN7();
        
        /* 3. Initialize the Baud Rate Generator */
        USART_ASYNC_BR_Init(usart_Obj);
        
        /* 4. Initialize the Transmission mode */
        USART_ASYNC_TX_Init(usart_Obj);

        /* 5. Initialize the Reception mode */
        USART_ASYNC_RX_Init(usart_Obj);
        
        /* 6. Assign the Interrupt Handlers for Framing and Overrun errors */
        USART_Framing_Error_Handler = usart_Obj -> EUSART_FramingErrorHandler;
        USART_Overrun_Error_Handler = usart_Obj -> EUSART_OverrunErrorHandler;
        
        /* 7. Enable The USART module */
        EUSART_MODULE_ENABLE();
    }
    return ret;
}
/**
 * A helper software interface de-initializes the
 * usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_DeInit(const usart_t *usart_Obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL == usart_Obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1. Disable The USART module */
        EUSART_MODULE_DISABLE();
        
        /* 2. Disable the TX & RX Interrupts */
        INTI_EUSART_TX_INTERRRUPT_DISABLE();
        INTI_EUSART_RX_INTERRRUPT_DISABLE();
    }
    return ret;
}
/**
 * A helper software interface reads a byte with 
 * the usart module.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @param byte_read : A pointer to the byte to be read.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Read_Byte_With_Blocking(uint8_t *byte_read)
{
    Std_ReturnType ret = E_OK;
    if (NULL == byte_read)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(!PIR1bits.RCIF);
        
      
        /* Read the RC register */
        *byte_read = RCREG;
    }
    return ret;
}

/**
 * A helper software interface reads a byte with 
 * the usart module. => Check the returned value <=
 * @param usart_Obj : A pointer to an object of 
 * the USART module.
 * @param byte_read
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType USART_ASYNC_Read_Byte_With_NoBlocking(uint8_t *byte_read)
{
    Std_ReturnType ret = E_OK;
    if (NULL == byte_read)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(PIR1bits.RCIF)
        { 
            /* Read the RC register */
            *byte_read = RCREG; 
        }
        else
            { ret = E_NOT_OK; }        
    }
    return ret;
}
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
Std_ReturnType USART_ASYNC_Write_Byte_With_Blocking(const uint8_t byte_written)
{
    Std_ReturnType ret = E_OK;

    /* Poll till the shift register becomes empty */
    while (!TXSTAbits.TRMT);

    /* Enable the Interrupt for the transmit mode */
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    INTI_EUSART_TX_INTERRRUPT_ENABLE();
#endif
    
    /* Write the value in the transmit register */
    TXREG = byte_written;

    return ret;
}
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
Std_ReturnType USART_ASYNC_Write_Byte_With_NoBlocking(const uint8_t byte_written)
{
    Std_ReturnType ret = E_OK;

    if(TXSTAbits.TRMT)
    {
        TXREG = byte_written;
        
    /* Enable the Interrupt for the transmit mode */
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    INTI_EUSART_TX_INTERRRUPT_ENABLE();
#endif
    }
    else
        { ret = E_NOT_OK; }

//    /* Enable the Interrupt for the transmit mode */
//#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
//    INTI_EUSART_TX_INTERRRUPT_ENABLE();
//#endif

    return ret;
}

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
Std_ReturnType USART_ASYNC_Write_String_With_Blocking(const uint8_t *string_written)
{
    Std_ReturnType ret = E_OK;
    if (NULL == string_written)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint16_t l_counter = ZERO_INIT;
        for (l_counter = ZERO_INIT; string_written[l_counter] != NULL; ++l_counter)
            { ret = USART_ASYNC_Write_Byte_With_Blocking(string_written[l_counter]); }
    }
    return ret;
}
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
Std_ReturnType USART_ASYNC_Write_Number_With_Blocking(const sint32_t number_written)
{
    Std_ReturnType ret = E_OK;
    uint8_t number_string[30];
    
    // Convert the number to a string
    snprintf(number_string, sizeof(number_string), "%ld", number_written);
    
    ret = USART_ASYNC_Write_String_With_Blocking(number_string);
    
    free(number_string);
    return ret;
}
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
Std_ReturnType USART_ASYNC_Write_Number_With_NoBlocking(const sint32_t number_written)
{
    Std_ReturnType ret = E_OK;
    uint8_t number_string[30];
    
    // Convert the number to a string
    snprintf(number_string, sizeof(number_string), "%ld", number_written);
    
    ret = USART_ASYNC_Write_String_With_NoBlocking(number_string);
    
    free(number_string);
    return ret;
}
/* ---------------  Section: Helper Functions Definitions --------------- */
/**
 * A helper software interface initializes 
 * the baud rate with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 */
static void USART_ASYNC_BR_Init(const usart_t *usart_Obj)
{
    float temp_baud_rate = 0;
    switch(usart_Obj->baudrate_generator_gonfigs)
    {
        case BAUDRATE_ASYN_8BIT_lOW_SPEED :
            EUSART_SET_ASYNC();         /* ASynchronous Mode */
            EUSART_SET_8_BIT();         /* 8-Bits Register Mode */
            EUSART_SET_LOW_SPEED();     /* Low Speed Mode */
            temp_baud_rate = ((_XTAL_FREQ / (64.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED :
            EUSART_SET_ASYNC();         /* ASynchronous Mode */
            EUSART_SET_8_BIT();         /* 8-Bits Register Mode */
            EUSART_SET_HIGH_SPEED();    /* High Speed Mode */
            temp_baud_rate = ((_XTAL_FREQ / (16.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED :
            EUSART_SET_ASYNC();         /* ASynchronous Mode */
            EUSART_SET_16_BIT();        /* 16-Bits Register Mode */
            EUSART_SET_LOW_SPEED();     /* Low Speed Mode */
            temp_baud_rate = ((_XTAL_FREQ / (16.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED :
            EUSART_SET_ASYNC();         /* ASynchronous Mode */
            EUSART_SET_16_BIT();        /* 16-Bits Register Mode */
            EUSART_SET_HIGH_SPEED();    /* High Speed Mode */
            temp_baud_rate = ((_XTAL_FREQ / (4.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        case BAUDRATE_SYN_8BIT :
            EUSART_SET_SYNC();          /* Synchronous Mode */
            EUSART_SET_8_BIT();         /* 8-Bits Register Mode */
            temp_baud_rate = ((_XTAL_FREQ / (4.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        case BAUDRATE_SYN_16BIT :
            EUSART_SET_SYNC();          /* ASynchronous Mode */
            EUSART_SET_16_BIT();        /* 16-Bits Register Mode */
            temp_baud_rate = ((_XTAL_FREQ / (4.0 * (usart_Obj -> baudrate))) - 1); 
            break;
        default :   /* Nothing */
            break;
    }
    SPBRG  = (uint8_t)((uint32_t)temp_baud_rate);
    SPBRGH = (uint8_t)(((uint32_t)temp_baud_rate) >> 8);
} 

/**
 * A helper software interface initializes 
 * transmission mode with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 */
static void USART_ASYNC_TX_Init(const usart_t* usart_Obj)
{
    switch (usart_Obj -> usart_tx_cfgs.usart_tx_enable)
    {
        case EUSART_ASYNC_TX_ENABLE : 
            /* Disable the Transmit mode */
            EUSART_ASYNC_TX_SET_DISABLE();
            
            /* Configure the interrupt feature for the Transmit mode */
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
            switch (usart_Obj -> usart_tx_cfgs.usart_tx_interrupt_enable)
            {
                case EUSART_ASYNC_INTERRUPT_TX_ENABLE : 
                    /* Enable the Interrupts for the usart module */
                    INTI_EUSART_TX_INTERRRUPT_ENABLE();
                    // Enable Global & Peripheral Interrupts
                    INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
                    INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
                    /* Configure the Interrupt Priority */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
                    // Enable the Interrupt Priority.
                    INTERRUPT_PRIORITY_ENABLE();
                    // Assign the Specified priority.
                    switch (usart_Obj -> usart_tx_cfgs.usart_tx_interrupt_priority)
                    {
                        case PRIORITY_HIGH : INTI_EUSART_TX_INTERRUPT_PRIORITY_HIGH();
                                        break;
                        case PRIORITY_LOW: INTI_EUSART_TX_INTERRUPT_PRIORITY_LOW();
                                        break;
                        default :   /* Nothing */
                            break;  
                    }
#endif
                    // Assign the interrupt handler.
                    USART_TX_Interrupt_Handler = usart_Obj -> EUSART_TX_InterruptHandler;
                    break;
                
                case EUSART_ASYNC_INTERRUPT_TX_DISABLE : 
                    // Disable the USART Interrupts.
                    INTI_EUSART_TX_INTERRRUPT_DISABLE(); 
                    break;
                default :   /* Nothing */
                    break;
            }            
#endif
            /* Configure the 9th bit of data */
            switch (usart_Obj -> usart_tx_cfgs.usart_tx_9bit_enable)
            {
                case EUSART_ASYNC_9BIT_TX_ENABLE : EUSART_9BIT_TX_SET_ENABLE();
                                                break;
                case EUSART_ASYNC_9BIT_TX_DISABLE : EUSART_9BIT_TX_SET_DISABLE(); 
                                                break;
                default :   /* Nothing */
                    break;
            }
            
            /* Enable the Transmit mode */
            EUSART_ASYNC_TX_SET_ENABLE();
            break;
        
         case EUSART_ASYNC_TX_DISABLE : 
            EUSART_ASYNC_TX_SET_DISABLE();
            break;
        
        default :   
            /* Nothing */
            break;
    }
} 

/**
 * A helper software interface initializes 
 * reception mode with the specified configurations.
 * @param usart_Obj : A pointer to an object of 
 * the USART module.  
 */
static void USART_ASYNC_RX_Init(const usart_t *usart_Obj)
{
switch (usart_Obj -> usart_rx_cfgs.usart_rx_enable)
    {
        case EUSART_ASYNC_RX_ENABLE : 
            /* Disable the Reception mode */
            EUSART_ASYNC_RX_SET_DISABLE();
            /* Configure the interrupt feature for the Reception mode */
#if EUSART_RX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
            switch (usart_Obj -> usart_rx_cfgs.usart_rx_interrupt_enable)
            {
                case EUSART_ASYNC_INTERRUPT_RX_ENABLE : 
                    /* Enable the Interrupts for the usart module */
                    INTI_EUSART_RX_INTERRRUPT_ENABLE();
                    // Enable Global & Peripheral Interrupts
                    INTERRUPT_GIEH_ENABLE();    /* Enable Global Interrupts */
                    INTERRUPT_GIEL_ENABLE();    /* Enable Peripheral Interrupts */
                    /* Configure the Interrupt Priority */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
                    INTERRUPT_PRIORITY_ENABLE();
                    // Assign the Specified priority.
                    switch (usart_Obj -> usart_rx_cfgs.usart_rx_interrupt_priority)
                    {
                        case PRIORITY_HIGH : INTI_EUSART_RX_INTERRUPT_PRIORITY_HIGH();
                                        break;
                        case PRIORITY_LOW: INTI_EUSART_RX_INTERRUPT_PRIORITY_LOW();
                                        break;
                        default :   /* Nothing */
                            break;  
                    }
#endif
                    // Assign the interrupt handler.
                    USART_RX_Interrupt_Handler = usart_Obj -> EUSART_RX_InterruptHandler;
                    break;
                case EUSART_ASYNC_INTERRUPT_RX_DISABLE : 
                    INTI_EUSART_RX_INTERRRUPT_DISABLE(); 
                    break;
                default :   /* Nothing */
                    break;
            }            
#endif
            /* Configure the 9th bit of data */
            switch (usart_Obj -> usart_rx_cfgs.usart_rx_9bit_enable)
            {
                case EUSART_ASYNC_9BIT_RX_ENABLE : EUSART_9BIT_RX_SET_ENABLE();
                                                break;
                case EUSART_ASYNC_9BIT_RX_DISABLE : EUSART_9BIT_RX_SET_DISABLE(); 
                                                break;
                default :   /* Nothing */
                    break;
            }
            
            /* Enable the Reception mode */
            EUSART_ASYNC_RX_SET_ENABLE();
            break;
        
         case EUSART_ASYNC_RX_DISABLE : 
            EUSART_ASYNC_RX_SET_DISABLE();
            break;
        
        default :   
            /* Nothing */
            break;
    }
}

void USART_TX_ISR(void)
{
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    INTI_EUSART_TX_INTERRRUPT_DISABLE();
#endif
    
    if(USART_TX_Interrupt_Handler)
        { USART_TX_Interrupt_Handler(); }
    
}

void USART_RX_ISR(void)
{    
    if(USART_RX_Interrupt_Handler)
        { USART_RX_Interrupt_Handler(); }
    else
        { /* Nothing */ }
    
    if(USART_Framing_Error_Handler)
        { USART_Framing_Error_Handler(); }
    else
        { /* Nothing */ }
    
    if(USART_Overrun_Error_Handler)
        { USART_Overrun_Error_Handler(); }
    else
        { /* Nothing */ }
}