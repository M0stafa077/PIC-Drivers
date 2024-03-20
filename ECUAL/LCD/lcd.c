/* 
 * File:   lcd.c
 * Author: Mostafa_Asaad
 *
 * Created on December 14, 2023, 7:51 PM
 */

/* Section : Includes */
#include "lcd.h"

/* Section : Helper functions */
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* _lcd, uint8_t data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* _lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* _lcd);

#if LCD_CONFIGURATION==CONFIG_ENABLE
/**
 * @brief : A software interface initializes an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    uint8_t l_data_pins_counter = ZERO_INIT;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_initialize(&(_lcd->lcd_rs_pin));
        ret = gpio_pin_initialize(&(_lcd->lcd_en_pin));
        for( ;l_data_pins_counter < LCD_4BITS; ++l_data_pins_counter){
            ret = gpio_pin_initialize(&(_lcd -> lcd_data_pins[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(_lcd, LCD_CLEAR);
        ret = lcd_4bit_send_command(_lcd, LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(_lcd, LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(_lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(_lcd, LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(_lcd, 0x80);
    }
   return ret;
}
#endif

/** 
 * @brief : A software interface sends command to 
 *          an LCD connected in 4-Bit mode. 
 * @param (_lcd) : A pointer to an LCD object
 * @param (command) : The command needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* _lcd, uint8_t command){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs_pin), GPIO_LOW); // To send command
        ret = lcd_send_4bits(_lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(_lcd);
        ret = lcd_send_4bits(_lcd, command);
        ret = lcd_4bit_send_enable_signal(_lcd);
    }
   return ret; 
}
#endif

/**
 * @brief : A software interface sends one char to
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param data : The character needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* _lcd, uint8_t data){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs_pin), GPIO_HIGH); //To send Data
        ret = lcd_send_4bits(_lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(_lcd);
        ret = lcd_send_4bits(_lcd, data);
        ret = lcd_4bit_send_enable_signal(_lcd);
    }
   return ret;
}
#endif

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
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t* _lcd, 
                                           uint8_t row, uint8_t column, uint8_t data){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_4bit_set_cursor(_lcd, row, column);
        ret = lcd_4bit_send_char_data(_lcd, data);
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends a string to
 *          an LCD connected in 4-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param str : The string needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* _lcd, uint8_t* str){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        while(*str){
            ret = lcd_4bit_send_char_data(_lcd, *str++);
        }
    }
   return ret;
}
#endif

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
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t* _lcd, 
                                        uint8_t row, uint8_t column, uint8_t* str){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_4bit_set_cursor(_lcd, row, column);
        ret = lcd_4bit_send_string(_lcd, str);
    }
   return ret;
}
#endif

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
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* _lcd,
                                         uint8_t row, uint8_t column, 
                                         const uint8_t _char[], uint8_t memory_pos){
        Std_ReturnType ret = E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
       
    }
   return ret;
}
#endif

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
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* _lcd, uint8_t row, uint8_t column){
    Std_ReturnType ret = E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else{
        switch (row) {
        case ROW1:
            ret = lcd_4bit_send_command(_lcd, 0x80 + --column);
            break;
        case ROW2:
            ret = lcd_4bit_send_command(_lcd, 0xC0 + --column);
            break;
        case ROW3:
            ret = lcd_4bit_send_command(_lcd, 0x94 + --column);
            break;
        case ROW4:
            ret = lcd_4bit_send_command(_lcd, 0xD4 + --column);
            break;
        default :
            ret = E_NOT_OK;
            break;
    }
    }
    
    return ret;
}
#endif

/**
 * @brief : A software interface initializes an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_initialize(const lcd_4bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    uint8_t l_data_pins_counter = ZERO_INIT;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_initialize(&(_lcd->lcd_rs_pin));
        ret = gpio_pin_initialize(&(_lcd->lcd_en_pin));
        for( ;l_data_pins_counter < LCD_8BITS; ++l_data_pins_counter){
            ret = gpio_pin_initialize(&(_lcd->lcd_data_pins[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(_lcd, LCD_CLEAR);
        ret = lcd_8bit_send_command(_lcd, LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(_lcd, LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(_lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(_lcd, 0x80);
        
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends command to 
 *          an LCD connected in 8-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param command : The command needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_command(const lcd_4bit_t* _lcd, uint8_t command){
    Std_ReturnType ret =E_OK;
    uint8_t l_pin_counter = ZERO_INIT;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs_pin), GPIO_LOW); // To send command
        for( ; l_pin_counter < LCD_8BITS; ++l_pin_counter){
            ret = gpio_pin_write_logic(&(_lcd->lcd_data_pins[l_pin_counter]), 
                                                 (command >> l_pin_counter) & BIT_MASK);
        }
        ret = lcd_8bit_send_enable_signal(_lcd);
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends one char to
 *          an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @param data : The character needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_char_data(const lcd_4bit_t* _lcd, uint8_t data){
    Std_ReturnType ret =E_OK;
    uint8_t l_pin_counter = ZERO_INIT;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs_pin), GPIO_HIGH); // To send Data
        for( ; l_pin_counter < LCD_8BITS; ++l_pin_counter){
            ret = gpio_pin_write_logic(&(_lcd->lcd_data_pins[l_pin_counter]), 
                                                 (data >> l_pin_counter) & BIT_MASK);
        }
        ret = lcd_8bit_send_enable_signal(_lcd);
        
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends one char to a certain position in
 *          an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the character must be printed
 * @param column : The column at which the character must be printed
 * @param data : The character needed to be sent
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_4bit_t* _lcd, 
                                           uint8_t row, uint8_t column, uint8_t data){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_8bit_set_cursor(_lcd, row, column);
        ret = lcd_8bit_send_char_data(_lcd, data);
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends a string to
 *          an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @param str : The string needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_string(const lcd_4bit_t* _lcd, uint8_t* str){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else { 
        while(*str){
            ret = lcd_8bit_send_char_data(_lcd, *str++);
        }
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends a string to a certain position in
 *          an LCD connected in 8-Bit mode. 
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the string must be printed
 * @param column : The column at which the string must be printed
 * @param str : The string needed to be printed
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_string_pos(const lcd_4bit_t* _lcd, 
                                        uint8_t row, uint8_t column, uint8_t* str){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_8bit_set_cursor(_lcd, row, column);
        ret = lcd_8bit_send_string(_lcd, str);
    }
   return ret;
}
#endif

/**
 * @brief : A software interface sends a special character that doesn't have
 *          an ASCII code to an LCD connected in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object
 * @param row : The row at which the character must be printed.
 * @param column : The column at which the character must be printed.
 * @param _char : The custom character to be printed.
 * @param memory_pos : The position of this character in CGRAM.
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_send_custom_char(const lcd_4bit_t* _lcd,
                                         uint8_t row, uint8_t column, 
                                         const uint8_t _char[], uint8_t memory_pos){
        Std_ReturnType ret =E_OK;
    if(NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        
    }
   return ret;
}
#endif

/**
 * @brief : A software interface that sets the cursor
 *          to a certain position on the LCD connected
 *          in 8-Bit mode.
 * @param _lcd : A pointer to an LCD object.
 * @param row : The row at which the character must be printed.
 * @param column : The column at which the character must be printed.
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* _lcd, uint8_t row, uint8_t column){
    Std_ReturnType ret = E_OK;
    if (NULL == _lcd){
        ret = E_NOT_OK;
    }
    else {
        switch (row) {
            case ROW1:
                ret = lcd_8bit_send_command(_lcd, 0x80 + --column);
                break;
            case ROW2:
                ret = lcd_8bit_send_command(_lcd, 0xC0 + --column);
                break;
            case ROW3:
                ret = lcd_8bit_send_command(_lcd, 0x94 + --column);
                break;
            case ROW4:
                ret = lcd_8bit_send_command(_lcd, 0xD4 + --column);
                break;
            default :
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}
#endif

/**
 * @brief
 * @param value : The value to be converted
 * @param str : A pointer to the string required to store 
 *              the converted data 
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType convert_uint8_to_string(uint8_t value, uint8_t* str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}
#endif

/**
 * @brief
 * @param value : The value to be converted
 * @param str : A pointer to the string required to store 
 *              the converted data
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType convert_uint16_to_string(uint16_t value, uint8_t* str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
    }
    return ret;
}
#endif

/**
 * @brief
 * @param value : The value to be converted
 * @param str : A pointer to the string required to store 
 *              the converted data
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType convert_uint32_to_string(uint32_t value, uint8_t* str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}
#endif

/**
 * @brief
 * @param _lcd
 * @param data_command
 * @return 
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* _lcd, uint8_t data_command) {
    Std_ReturnType ret = E_OK;
    Std_ReturnType ret_0 = gpio_pin_write_logic(&(_lcd->lcd_data_pins[0]), 
                                                 (data_command >> 0) & BIT_MASK);
    Std_ReturnType ret_1 = gpio_pin_write_logic(&(_lcd->lcd_data_pins[1]), 
                                                 (data_command >> 1) & BIT_MASK);
    
    Std_ReturnType ret_2 = gpio_pin_write_logic(&(_lcd->lcd_data_pins[2]), 
                                                 (data_command >> 2) & BIT_MASK);
    
    Std_ReturnType ret_3 = gpio_pin_write_logic(&(_lcd->lcd_data_pins[3]), 
                                                 (data_command >> 3) & BIT_MASK);
    ret = ((ret_0) & (ret_1) & (ret_2) & (ret_3));
    return ret;
}
#endif

/**
 * @brief
 * @param _lcd
 * @return 
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(_lcd->lcd_en_pin), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(_lcd->lcd_en_pin), GPIO_LOW);
    
    return ret;
}
#endif

/**
 * @brief
 * @param _lcd
 * @return 
 */
#if LCD_CONFIGURATION==CONFIG_ENABLE
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* _lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(_lcd->lcd_en_pin), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(_lcd->lcd_en_pin), GPIO_LOW);
    
    return ret;
}
#endif