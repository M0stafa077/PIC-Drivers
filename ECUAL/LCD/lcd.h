/* 
 * File:   lcd.h
 * Author: Mostafa_Asaad
 *
 * Created on December 14, 2023, 7:51 PM
 */

#ifndef LCD_H
#define	LCD_H

/* Section : Includes */
#include "../../MCAL/DIO/DIO.h"
#include "lcd_cfg.h"

/* Section: Macro Declarations */
#define LCD_CLEAR                       0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE                  0x06
#define LCD_CURSOR_OFF_DISPLAY_ON       0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF      0x08
#define LCD_CURSOR_ON_BLINK_ON          0x0F
#define LCD_CURSOR_ON_BLINK_OFF         0x0E
#define LCD_DISPLAY_SHIFT_RIGHT         0x1C
#define LCD_DISPLAY_SHIFT_LEFT          0x18
#define LCD_8BIT_MODE_2_LINE            0x38
#define LCD_4BIT_MODE_2_LINE            0x28
#define LCD_CGRAM_START                 0x40
#define LCD_DDRAM_START                 0x80
#define LCD_4BITS                       4
#define LCD_8BITS                       8
#define ROW1                            1
#define ROW2                            2
#define ROW3                            3
#define ROW4                            4

/* Section: Data Type Declarations */

/*
 * A struct for lcd configuration in 4-bit
 * mode
 */
typedef struct 
{
    /*
     * The pin configuration for the 
     * RS pin of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_rs_pin;                // RS pin
    /*
     * The pin configuration for the 
     * Enable pin of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_en_pin;                // E pin
    /*
     * The four pins configuration for the 
     * Data pins of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_data_pins[LCD_4BITS];  // Data pins     
    
} lcd_4bit_t;

/*
 * A struct for lcd configuration in 8-bit
 * mode
 */
typedef struct 
{
    /*
     * The pin configuration for the 
     * RS pin of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_rs_pin;                // RS pin
    /*
     * The pin configuration for the 
     * Enable pin of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_en_pin;                // E pin
    /*
     * The eight pins configuration for the 
     * Data pins of the LCD.
     * @ref pin_config_t
     */
    pin_config_t lcd_data_pins[LCD_8BITS];  // Data pins      
} lcd_8bit_t;

/* Section: Function Declarations */

/*
 * @brief : A software interface initializes an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* _lcd);
/* @brief : A software interface sends command to 
 *          an LCD connected in 4-Bit mode. 
 * @param (_lcd) : A pointer to an LCD object
 * @param (command) : The command needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd, uint8_t command);
/**
 * @brief : A software interface sends one char to
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param data : The character needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* _lcd, uint8_t data);
/**
 * @brief : A software interface sends one char to a certain position in
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the character must be printed
 * @param columnw : The column at which the character must be printed
 * @param data : The character needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t* _lcd, 
                                           uint8_t row, uint8_t column, uint8_t data);
/**
 * @brief : A software interface sends a string to
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param str : The string needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* _lcd, uint8_t* str);
/**
 * @brief : A software interface sends a string to a certain position in
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the string must be printed
 * @param column : The column at which the string must be printed
 * @param str : The string needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t* _lcd, 
                                        uint8_t row, uint8_t column, uint8_t* str);
/**
 * @brief : A software interface sends a special character that doesn't have
 *          an ASCII code to an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the character must be printed
 * @param column : The column at which the character must be printed
 * @param _char : The custom character to be printed
 * @param memory_pos : The position of this character in CGRAM
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd,
                                         uint8_t row, uint8_t column, 
                                         const uint8_t _char[], uint8_t memory_pos);
/**
 * @brief : A software interface that sets the cursor
 *          to a certain position on the LCD connected
 *          in 4-Bit mode.
 * @param _lcd : A pointer to an LCD object.
 * @param row : The row at which the character must be printed.
 * @param column : The column at which the character must be printed.
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd, uint8_t row, uint8_t column);
/**
 * @brief : A software interface initializes an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_initialize(const lcd_4bit_t* _lcd);
/**
 * @brief : A software interface sends command to 
 *          an LCD connected in 8-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param command : The command needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const lcd_4bit_t* _lcd, uint8_t command);
/**
 * @brief : A software interface sends one char to
 *          an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @param data : The character needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_4bit_t* _lcd, uint8_t data);

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_4bit_t* _lcd, 
                                           uint8_t row, uint8_t column, uint8_t data);
Std_ReturnType lcd_8bit_send_string(const lcd_4bit_t* _lcd, uint8_t* str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_4bit_t* _lcd, 
                                        uint8_t row, uint8_t column, uint8_t* str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_4bit_t* _lcd,
                                         uint8_t row, uint8_t column, 
                                         const uint8_t _char[], uint8_t memory_pos);
Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd, uint8_t row, uint8_t column);

Std_ReturnType convert_uint8_to_string(uint8_t value, uint8_t* str);
Std_ReturnType convert_uint16_to_string(uint16_t value, uint8_t* str);
Std_ReturnType convert_uint32_to_string(uint32_t value, uint8_t* str);

#endif	/* LCD_H */

