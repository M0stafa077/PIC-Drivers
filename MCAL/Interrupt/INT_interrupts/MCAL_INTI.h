/* 
 * File:   MCAL_INTI.h
 * Author: Mostafa Asaad
 *
 * Created on January 14, 2024, 9:19 PM
 */

#ifndef MCAL_INTI_H
#define	MCAL_INTI_H

/* Section : Includes */
#include "../MCAL_interrupt_cfg.h"

/* Section: Macro Declarations */
#define ADC_INTERRUPT_FEATURE                       INTERRUPT_ENABLE

#define TMR0_INTERRUPT_FEATURE                      INTERRUPT_ENABLE
#define TMR1_INTERRUPT_FEATURE                      INTERRUPT_ENABLE
#define TMR2_INTERRUPT_FEATURE                      INTERRUPT_ENABLE
#define TMR3_INTERRUPT_FEATURE                      INTERRUPT_ENABLE

#define CCP1_INTERRUPT_FEATURE                      INTERRUPT_ENABLE
#define CCP2_INTERRUPT_FEATURE                      INTERRUPT_ENABLE

#define EUSART_TX_INTERRUPT_FEATURE                 INTERRUPT_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE                 INTERRUPT_ENABLE

#define SPI_INTERRUPT_FEATURE                       INTERRUPT_ENABLE
/* -------- Section: Macro Functions Declarations -------- */

/* ===========================================================================*/

/* -------- Section: ADC INTERRUPT CONFIGURATIONs -------- */
#if ADC_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Disable the Interrupts for the (A/D) */
#define INTI_ADC_INTERRRUPT_DISABLE()               (PIE1bits.ADIE = STD_LOW)     
/* Enable the Interrupts for the (A/D) */
#define INTI_ADC_INTERRRUPT_ENABLE()                (PIE1bits.ADIE = STD_HIGH)
/* Clear the Interrupt flag for the (A/D) */
#define INTI_ADC_CLR_FLAG()                         (PIR1bits.ADIF = STD_LOW)

/* Handle The Interrupt priority feature for the (A/D) module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_ADC_INTERRUPT_PRIORITY_HIGH()          (IPR1bits.ADIP = STD_HIGH)
#define INTI_ADC_INTERRUPT_PRIORITY_LOW()           (IPR1bits.ADIP = STD_LOW)
#endif

#endif
/* -------- Section: End of ADC INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: Timer0 INTERRUPT CONFIGURATIONs -------- */
#if TMR0_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the Timer0 */
#define INTI_TMR0_INTERRRUPT_ENABLE()               (INTCONbits.T0IE = STD_HIGH)
/* Disable the Interrupts for the Timer0 */
#define INTI_TMR0_INTERRRUPT_DISABLE()              (INTCONbits.T0IE = STD_LOW)     
/* Clear the Interrupt flag for the Timer0 */
#define INTI_TMR0_CLR_FLAG()                        (INTCONbits.T0IF = STD_LOW)

/* Handle The Interrupt priority feature for the Timer0 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_TMR0_INTERRUPT_PRIORITY_HIGH()         (INTCON2bits.TMR0IP = PRIORITY_HIGH)
#define INTI_TMR0_INTERRUPT_PRIORITY_LOW()          (INTCON2bits.TMR0IP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of Timer0 INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: Timer1 INTERRUPT CONFIGURATIONs -------- */

#if TMR1_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the Timer1 */
#define INTI_TMR1_INTERRRUPT_ENABLE()               (PIE1bits.TMR1IE = STD_HIGH)
/* Disable the Interrupts for the Timer1 */
#define INTI_TMR1_INTERRRUPT_DISABLE()              (PIE1bits.TMR1IE = STD_LOW)     
/* Clear the Interrupt flag for the Timer1 */
#define INTI_TMR1_CLR_FLAG()                        (PIR1bits.TMR1IF = STD_LOW)

/* Handle The Interrupt priority feature for the Timer1 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_TMR1_INTERRUPT_PRIORITY_HIGH()         (IPR1bits.TMR1IP = PRIORITY_HIGH)
#define INTI_TMR1_INTERRUPT_PRIORITY_LOW()          (IPR1bits.TMR1IP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of Timer1 INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: Timer2 INTERRUPT CONFIGURATIONs -------- */
#if TMR2_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the Timer2 */
#define INTI_TMR2_INTERRRUPT_ENABLE()               (PIE1bits.TMR2IE = STD_HIGH)
/* Disable the Interrupts for the Timer2 */
#define INTI_TMR2_INTERRRUPT_DISABLE()              (PIE1bits.TMR2IE = STD_LOW)     
/* Clear the Interrupt flag for the Timer2 */
#define INTI_TMR2_CLR_FLAG()                        (PIR1bits.TMR2IF = STD_LOW)

/* Handle The Interrupt priority feature for the Timer2 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_TMR2_INTERRUPT_PRIORITY_HIGH()         (IPR1bits.TMR2IP = PRIORITY_HIGH)
#define INTI_TMR2_INTERRUPT_PRIORITY_LOW()          (IPR1bits.TMR2IP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of Timer2 INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: Timer 3 INTERRUPT CONFIGURATIONs -------- */
#if TMR3_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the Timer 3 */
#define INTI_TMR3_INTERRRUPT_ENABLE()               (PIE2bits.TMR3IE = STD_HIGH)
/* Disable the Interrupts for the Timer 3 */
#define INTI_TMR3_INTERRRUPT_DISABLE()              (PIE2bits.TMR3IE = STD_LOW)     
/* Clear the Interrupt flag for the Timer 3 */
#define INTI_TMR3_CLR_FLAG()                        (PIR2bits.TMR3IF = STD_LOW)

/* Handle The Interrupt priority feature for the Timer 3 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_TMR3_INTERRUPT_PRIORITY_HIGH()         (IPR2bits.TMR3IP = PRIORITY_HIGH)
#define INTI_TMR3_INTERRUPT_PRIORITY_LOW()          (IPR2bits.TMR3IP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of Timer 3 INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: CCP 1 INTERRUPT CONFIGURATIOs -------- */
#if CCP1_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the CCP 1 */
#define INTI_CCP1_INTERRRUPT_ENABLE()               (PIE1bits.CCP1IE = STD_HIGH)
/* Disable the Interrupts for the CCP 1 */
#define INTI_CCP1_INTERRRUPT_DISABLE()              (PIE1bits.CCP1IE = STD_LOW)     
/* Clear the Interrupt flag for the CCP 1 */
#define INTI_CCP1_CLR_FLAG()                        (PIR1bits.CCP1IF = STD_LOW)

/* Handle The Interrupt priority feature for the CCP 1 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_CCP1_INTERRUPT_PRIORITY_HIGH()         (IPR1bits.CCP1IP = PRIORITY_HIGH)
#define INTI_CCP1_INTERRUPT_PRIORITY_LOW()          (IPR1bits.CCP1IP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of CCP 1 INTERRUPT CONFIGURATIONs -------- */

/* ===========================================================================*/

/* -------- Section: CCP 2 INTERRUPT CONFIGURATIONs -------- */
#if CCP2_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* Enable the Interrupts for the CCP 2 */
#define INTI_CCP2_INTERRRUPT_ENABLE()               (PIE2bits.CCP2IE = STD_HIGH)
/* Disable the Interrupts for the CCP 2 */
#define INTI_CCP2_INTERRRUPT_DISABLE()              (PIE2bits.CCP2IE = STD_LOW)     
/* Clear the Interrupt flag for the CCP 2 */
#define INTI_CCP2_CLR_FLAG()                        (PIR2bits.CCP2IF = STD_LOW)

/* Handle The Interrupt priority feature for the CCP2 module */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_CCP2_INTERRUPT_PRIORITY_HIGH()         (IPR2bits.CCP2IP = PRIORITY_HIGH)
#define INTI_CCP2_INTERRUPT_PRIORITY_LOW()          (IPR2bits.CCP2IP = PRIORITY_LOW)
#endif  

#endif
/* -------- Section: End of CCP 2 INTERRUPT CONFIGURATIOs -------- */

/* ===========================================================================*/

/* -------- Section: EUSART Transmission mode INTERRUPT CONFIGURATIONs -------- */
#if EUSART_TX_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* 
 * Enable the Interrupts for the Transmission
 * mode in the USART module. 
 */
#define INTI_EUSART_TX_INTERRRUPT_ENABLE()          (PIE1bits.TXIE = STD_HIGH)
/* 
 * Disable the Interrupts for the Transmission
 * mode in the USART module. 
 */
#define INTI_EUSART_TX_INTERRRUPT_DISABLE()         (PIE1bits.TXIE = STD_LOW)     
/* 
 * Clear the Interrupt flag for 
 * the Transmission mode in the USART module. 
 */
#define INTI_EUSART_TX_CLR_FLAG()                   (PIR1bits.TXIF = STD_LOW)

/* 
 * Handle The Interrupt priority feature for the 
 * Transmission mode in the USART module.  
 */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_EUSART_TX_INTERRUPT_PRIORITY_HIGH()    (IPR1bits.TXIP = PRIORITY_HIGH)
#define INTI_EUSART_TX_INTERRUPT_PRIORITY_LOW()     (IPR1bits.TXIP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of EUSART Transmission mode INTERRUPT CONFIGURATIOs -------- */

/* ===========================================================================*/

/* -------- Section: EUSART Reception mode INTERRUPT CONFIGURATIONs -------- */
#if EUSART_RX_INTERRUPT_FEATURE==INTERRUPT_ENABLE

/* 
 * Enable the Interrupts for the Reception
 * mode in the USART module. 
 */
#define INTI_EUSART_RX_INTERRRUPT_ENABLE()          (PIE1bits.RCIE = STD_HIGH)

/* 
 * Disable the Interrupts for the Reception
 * mode in the USART module. 
 */
#define INTI_EUSART_RX_INTERRRUPT_DISABLE()         (PIE1bits.RCIE = STD_LOW)     

/* 
 * Clear the Interrupt flag for 
 * the Reception mode in the USART module. 
 */
#define INTI_EUSART_RX_CLR_FLAG()                   (PIR1bits.RCIF = STD_LOW)

/* 
 * Handle The Interrupt priority feature for the 
 * Reception mode in the USART module.  
 */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_EUSART_RX_INTERRUPT_PRIORITY_HIGH()    (IPR1bits.RCIP = PRIORITY_HIGH)
#define INTI_EUSART_RX_INTERRUPT_PRIORITY_LOW()     (IPR1bits.RCIP = PRIORITY_LOW)
#endif

#endif
/* -------- Section: End of EUSART Reception mode INTERRUPT CONFIGURATIOs -------- */

/* ===========================================================================*/

/* -------- Section: EUSART Reception mode INTERRUPT CONFIGURATIONs -------- */
#if SPI_INTERRUPT_FEATURE == INTERRUPT_ENABLE

/* 
 * Enable the Interrupts for the SPI module.
 */
#define INTI_SPI_INTERRUPT_ENABLE()                 (PIE1bits.SSPIE = STD_ENABLE)

/* 
 * Disable the Interrupts for the SPI module.
 */
#define INTI_SPI_INTERRUPT_DISABLE()                (PIE1bits.SSPIE = STD_DISABLE)     

/* 
 * Clear the Interrupt flag for 
 * the Reception mode in the USART module. 
 */
#define INTI_SPI_CLR_FLAG()                         (PIR1bits.SSPIF = STD_LOW)

/* 
 * Handle The Interrupt priority feature for the 
 * Reception mode in the USART module.  
 */
#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
#define INTI_SPI_INTERRUPT_PRIORITY_HIGH()          (IPR1bits.SSPIP = STD_HIGH)
#define INTI_SPI_INTERRUPT_PRIORITY_LOW()           (IPR1bits.SSPIP = STD_LOW)
#endif

#endif
/* -------- Section: End of EUSART Reception mode INTERRUPT CONFIGURATIOs -------- */

/* ===========================================================================*/

#endif	/* MCAL_INTI_H */

