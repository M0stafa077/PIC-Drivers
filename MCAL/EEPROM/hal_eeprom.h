/* 
 * File:   hal_eeprom.h
 * Author: Mostafa Asaad
 *
 * Created on January 16, 2024, 1:23 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* --------------- Section : Includes --------------- */
#include "../MCAL_std_types.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"

/* --------------- Section: Macro Declarations --------------- */
    
/* --------------- Section: Macro Functions Declarations --------------- */

/* EEPGD: Flash Program or Data EEPROM Memory Select bit */
/* 1 = Access Flash Program memory */
/* 0 = Access data EEPROM memory */
#define ACCESS_FLASH_PROGRAM_MEM()      (EECON1bits.EEPGD = STD_HIGH)
#define ACCESS_EEPROM()                 (EECON1bits.EEPGD = STD_LOW) 

/* CFGS: Flash Program/Data EEPROM or Configuration Select bit */
/* 1 = Access Configuration registers */
/* 0 = Access Flash program or data EEPROM memory */
#define ACCESS_CFG_REG()                (EECON1bits.CFGS  = STD_HIGH)
#define ACCESS_EEPROM_FLASH()           (EECON1bits.CFGS  = STD_LOW)

/* WREN : Flash Program/Data EEPROM Write Enable bit */
/* 1 = Allows write cycles to Flash program/data EEPROM */
/* 0 = Inhibits write cycles to Flash program/data EEPROM */ 
#define ALLOW_EEPROM_FLASH_WRITE()      (EECON1bits.WREN = STD_HIGH)
#define INHIBIT_EEPROM_FLASH_WRITE()    (EECON1bits.WREN = STD_LOW)


/* WR: Write Control bit */
/* 1 = Initiates a data EEPROM erase/write cycle or a program memory erase 
 * cycle or write cycle
 * (The operation is self-timed and the bit is cleared by hardware once write 
 * is complete. 
 * The WR bit can only be set (not cleared) in software.) */
/* 0 = Write cycle to the EEPROM is complete */
#define INITIATE_WR_OPERATIONS()        (EECON1bits.WR = STD_HIGH)
#define READ_WR()                       (EECON1bits.WR)


/* RD: Read Control bit */
/* 1 = Initiates an EEPROM read (Read takes one cycle. RD is cleared in hardware.
 *  The RD bit can only be set (not cleared) in software. 
 * RD bit cannot be set when EEPGD = 1 or CFGS = 1.)*/
#define INITIATE_RD_OPERATIONS()        (EECON1bits.RD = STD_HIGH)



/* --------------- Section: Data Type Declarations --------------- */

/*---------------  Section: Function Declarations --------------- */
Std_ReturnType EEPROM_write_byte(uint16_t bAdd, uint8_t bData);
Std_ReturnType EEPROM_read_byte(uint16_t bAdd, uint8_t *bData);

#endif	/* HAL_EEPROM_H */

