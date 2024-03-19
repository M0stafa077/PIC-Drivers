/* 
 * File:   hal_eeprom.c
 * Author: Mostafa Asaad
 *
 * Created on January 16, 2024, 1:23 PM
 */

/* --------------- Section : Includes --------------- */
#include "hal_eeprom.h"

/*---------------  Section: Functions Definitions --------------- */
Std_ReturnType EEPROM_write_byte(uint16_t bAdd, uint8_t bData)
{
    Std_ReturnType ret = E_OK;
    /* 1.Read the interrupt status */
    uint8_t interrupt_status = INTCONbits.GIE;
    
    /* 2.Update Address Registers */
    EEADRH = (uint8_t) ((bAdd >> 8) & (0x03));
    EEADR  = (uint8_t) (bAdd & 0xFF);
    
    /* 3.Update Data Register */
    EEDATA = bData;
    
    /* 4.Access The EEPROM */
    ACCESS_EEPROM();
    ACCESS_EEPROM_FLASH();   
    
    /* 5.Allow the WR operations on the data EEPROM/Flash Program */
    ALLOW_EEPROM_FLASH_WRITE();
    
    /* 6.Disable the General Interrupts */
    INTERRUPT_GIEH_DISABLE();
    
    /* 7. Write the required Section from the dataSheet */
    EECON2 = 0x55;  
    EECON2 = 0xAA;  
    
    /* 8.Initiate Data EEPROM erase/Write Cycle */
    INITIATE_WR_OPERATIONS();
    
    /* 9.Wait with for the operation to complete */ 
    while(READ_WR());
    
    /* 10.Disable the writes to Flash Program/Data EEPROM */
    INHIBIT_EEPROM_FLASH_WRITE();
    
    /* 11.Restore the Interrupt status */
    INTCONbits.GIE = interrupt_status;
    
    return ret;
}
Std_ReturnType EEPROM_read_byte(uint16_t bAdd, uint8_t *bData)
{
    Std_ReturnType ret = E_OK;
    if (NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* 1.Update Address Registers */
        EEADRH = (uint8_t) ((bAdd >> 8) & (0x03));
        EEADR  = (uint8_t) (bAdd & 0xFF);
        
        /* 2.Access The EEPROM */
        ACCESS_EEPROM();
        ACCESS_EEPROM_FLASH(); 
        
        /* 3.Allow the RD operations on the data EEPROM */
        INITIATE_RD_OPERATIONS();
                
        /* 4.Hold your breath -_- */
        __nop();
        __nop();
        
        /* 5.Read the data from EEDATA register to your variable */
        *bData = EEDATA;
    }
    return ret;
}
