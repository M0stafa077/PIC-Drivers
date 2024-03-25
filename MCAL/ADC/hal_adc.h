/* 
 * File  : hal_adc.h
 * Author: Mostafa Asaad
 * https://github.com/M0stafa077
 * Created on January 27, 2024, 4:03 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* --------------- Section : Includes --------------- */
#include "hal_adc_cfg.h"
#include "../DIO/DIO.h"
#include "../Interrupt/INT_interrupts/MCAL_INTI.h"
/* --------------- Section: Macro Declarations --------------- */

/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *          AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */

#define ADC_AN0_ANALOG_FUNCTIONALITY        0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY        0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY        0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY        0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY        0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY        0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY        0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY        0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY        0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY        0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY       0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY       0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY       0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY        0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY       0x0F

#define ADC_RESULT_RIGHT                    0x01U
#define ADC_RESULT_LEFT                     0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED       STD_ENABLE
#define ADC_VOLTAGE_REFERENCE_DISABLED      STD_DISABLE

#define ADC_CONVERSION_COMPLETE             STD_TRUE
#define ADC_CONVERSION_IN_PROGRESS          STD_FALSE
/* --------------- Section: Macro Functions Declarations --------------- */

/**
 * @brief Enable the ADC module
 */
#define ADC_ENABLE()                        (ADCON0bits.ADON = STD_ENABLE)
/**
 * @brief Disable the ADC module.
 */
#define ADC_DISABLE()                       (ADCON0bits.ADON = STD_DISABLE)

/**
 * @brief Start the Analog-To-Digital Conversion
 */
#define ADC_START_CONVERSION()              (ADCON0bits.GODONE = STD_ACTIVE)
/**
 * @brief Stops the Analog-To-Digital Conversion
 */
#define ADC_STOP_CONVERSION()               (ADCON0bits.GODONE = STD_IDLE)

/* @brief (A/D) Conversion Status (A/D) conversion
 * in progress or (A/D) Idle.
 */
#define ADC_CONVERSION_STATUS()             (ADCON0bits.GO_nDONE)

/* @brief (A/D) Channel selector.
 * @note  in (ADCON0 register), bits (2 => 5)
 *                  13 Channels need 4 bits.
 *                  (0000) = Channel 0  (AN0)  (RA0)
 *                  (0001) = Channel 1  (AN1)  (RA1)
 *                  (0010) = Channel 2  (AN2)  (RA2)
 *                  (0011) = Channel 3  (AN3)  (RA3)
 *                  (0100) = Channel 4  (AN4)  (RA5)
 *                  (0101) = Channel 5  (AN5)  (RE0)
 *                  (0110) = Channel 6  (AN6)  (RE1)
 *                  (0111) = Channel 7  (AN7)  (RE2)
 *                  (1000) = Channel 8  (AN8)  (RB2)
 *                  (1001) = Channel 9  (AN9)  (RB3)
 *                  (1010) = Channel 10 (AN10) (RB1)
 *                  (1011) = Channel 11 (AN11) (RB4)
 *                  (1100) = Channel 12 (AN12) (RB0)
 */
#define ADC_SELECT_CHANNEL(_CHANNEL)        (ADCON0bits.CHS = _CHANNEL)
    
/**
 * @brief (A/D) Acquisition Time Configuration.
 * @note  ACQT2:ACQT0: (A/D) Acquisition Time Select bits
 *          111 = 20 TAD
 *          110 = 16 TAD
 *          101 = 12 TAD
 *          100 = 8  TAD
 *          011 = 6  TAD
 *          010 = 4  TAD
 *          001 = 2  TAD
 *          000 = 0  TAD
 */
#define ADC_SET_ACQ_TIME(_ACQT)            (ADCON2bits.ACQT = _ACQT)

/**
 * @brief : (A/D) Acquisition Time Configuration.
 * @note  : ADCS2:ADCS0: A/D Conversion Clock Select bits
 *          111 = FRC (clock derived from A/D RC oscillator)
 *          110 = FOSC/64
 *          101 = FOSC/16
 *          100 = FOSC/4
 *          011 = FRC (clock derived from A/D RC oscillator)
 *          010 = FOSC/32
 *          001 = FOSC/8
 *          000 = FOSC/2
 */
#define ADC_SET_CONV_CLK(_CLK)              (ADCON2bits.ADCS = _CLK)

/**
 * @brief : Voltage Reference Configuration
 * @note  : ADC_ENABLE_VOLTAGE_REFERENCE()  : Voltage Reference is VREF+ & VREF-
 *          ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage Reference is VSS & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()      do{ADCON1bits.VCFG1 = STD_HIGH;\
                                                ADCON1bits.VCFG0 = STD_HIGH;\
                                            }while(STD_FALSE)
#define ADC_DISABLE_VOLTAGE_REFERENCE()     do{ADCON1bits.VCFG1 = STD_LOW;\
                                                ADCON1bits.VCFG0 = STD_LOW;\
                                            }while(STD_FALSE)

/**
 * @brief  (A/D) Port Configuration Control
 * @note : Example : 
 *           ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
		   When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *         AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 *         @ref Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/**
 * @brief : (A/D) Result Format Select.
 */
#define ADC_RESULT_RIGHT_FORMAT()           (ADCON2bits.ADFM = STD_TRUE)
#define ADC_RESULT_LEFT_FORMAT()            (ADCON2bits.ADFM = STD_FALSE)
#define ADC_RESULT_FORMAT()                 (ADCON2bits.ADFM)

/* --------------- Section: Data Type Declarations --------------- */

/*
 * @note an unsigned short value.
 */
typedef uint16_t adc_result_t;
/*
 * @brief Analog Channel Selectors
 */
typedef enum
{
    ADC_CHANNEL_AN0  = 0b0000,   //0
    ADC_CHANNEL_AN1  = 0b0001,   //1
    ADC_CHANNEL_AN2  = 0b0010,   //2
    ADC_CHANNEL_AN3  = 0b0011,   //3
    ADC_CHANNEL_AN4  = 0b0100,   //4
    ADC_CHANNEL_AN5  = 0b0101,   //5
    ADC_CHANNEL_AN6  = 0b0110,   //6
    ADC_CHANNEL_AN7  = 0b0111,   //7 
    ADC_CHANNEL_AN8  = 0b1000,   //8 
    ADC_CHANNEL_AN9  = 0b1001,   //9
    ADC_CHANNEL_AN10 = 0b1010,   //10    
    ADC_CHANNEL_AN11 = 0b1011,   //11    
    ADC_CHANNEL_AN12 = 0b1100    //12    
} ADC_channel_select_t;

/**
 * @brief  (A/D) Acquisition Time Select 
 * @note   Acquisition time (sampling time) is the time required for the 
 *         (ADC) to capture the input voltage during sampling.
 * @note   Acquisition time of a Successive Approximation Register (SAR) ADC
 *         is the amount of time required to charge the holding capacitor
 *         (CHOLD) on the front end of an ADC.
 */
typedef enum
{
    ADC_0_ATD = 0,
    ADC_2_ATD,
    ADC_4_ATD,
    ADC_6_ATD,
    ADC_8_ATD,
    ADC_12_ATD,
    ADC_16_ATD,
    ADC_20_ATD   
} ADC_acquisition_time_t;

/**
 * @brief  A/D Conversion Clock Select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *         is added before the A/D clock starts.
 * @note   This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

/*
 * @brief A structure for the ADC module 
 * configurations.
 */
typedef struct 
{
#if ADC_INTERRUPT_FEATURE==INTERRUPT_ENABLE
    /*
     * @brief The interrupt handler for
     * the ADC module.
     */
    interrupt_handler_t ADC_InterruptHandler;
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
    /*
     * @brief The priority for the ADC module
     * Interrupts.
     * @options PRIORITY_HIGH or PRIORITY_LOW
     */
    interrupt_priority_t priority;
#endif
#endif
    /*
     * @brief The ADC module acquisition time.
     * @note ADC_0_ATD or ADC_12_ATD till ADC_20_ATD
     * @ref hal_adc.h/ADC_acquisition_time_t
     */
    ADC_acquisition_time_t acquisition_time;
    /*
     * @brief The ADC conversion clock
     * configurations.
     * @ref hal_adc.h/adc_conversion_clock_t
     */
    adc_conversion_clock_t conversion_clock;
    /*
     * @brief The ADC channel on the MCU.
     * @note ADC_CHANNEL_AN3 or ADC_CHANNEL_AN6
     * @ref hal_adc.h/ADC_channel_select_t
     */
    ADC_channel_select_t   adc_channel;
    /*
     * @brief The voltage reference for 
     * the ADC module
     * @note ADC_VOLTAGE_REFERENCE_ENABLED 
     * or ADC_VOLTAGE_REFERENCE_ENABLED
     */
    uint8_t voltage_reference :1;
    /*
     * @brief The result format for
     * the ADC module.
     * @note ADC_RESULT_RIGHT or ADC_RESULT_LEFT
     */
    uint8_t result_format     :1;
    /*
     * @note Six reserved bits
     * for the ADC configurations
     * structure.
     */
    uint8_t adc_reserved      :6;  
} adc_cfg_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * @brief A software interface initializes the 
 * A/D module.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_init(const adc_cfg_t *_adc);
/**
 * @brief A software interface de-initializes the ADC module. 
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType ADC_deInit(const adc_cfg_t *_adc);
/*
 * @brief A software interface selects the channel for the ADC module.
 * @param _adc : Pointer to the adc module object.
 * @param channel : The channel to be selected.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_select_channel(adc_cfg_t *_adc, ADC_channel_select_t channel);
/**
 * @brief A software interface starts the conversion.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_start_conversion(const adc_cfg_t *_adc);
/**
 * @brief A software interface checks the status
 * of the A/D conversion.
 * @param _adc : Pointer to the adc module object.
 * @param status : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_is_conversion_done(const adc_cfg_t *_adc, uint8_t* status);
/**
 * @brief A software interface gets the
 * result of the A/D conversion
 * @param _adc : Pointer to the adc module object.
 * @param result : The variable ref to store the result in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_result(const adc_cfg_t *_adc, adc_result_t *result);
/*
 * @brief A software interface gets the
 * result of the A/D conversion by blocking.
 * @param _adc : Pointer to the adc module object.
 * @param channel : The Channel to be selected.
 * @param conversion_result : The variable ref to store the status in.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_blocking(const adc_cfg_t *_adc, adc_result_t *conversion_result);
/*
 * @brief A software interface starts the A/D 
 * conversion using interrupt feature.
 * @param _adc : Pointer to the adc module object.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_start_conversion_interrupt(const adc_cfg_t *_adc);
#endif	/* HAL_ADC_H */
