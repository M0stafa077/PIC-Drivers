/* 
 * File:   MCAL_interrupt_manager.c
 * Author: Mostafa Asaad
 *
 * Created on January 14, 2024, 9:16 PM
 */

/* Section : Includes */
#include "MCAL_interrupt_manager.h"

#if INTERRUPT_PRIORITY_FEATURE==INTERRUPT_ENABLE
void __interrupt() InterruptManagerHigh(void)
{    
    if (INTERRUPT_OCCURED == PIR1bits.ADIF)
    {
        INTI_ADC_ISR();
    }
    else
        { /* Nothing */ }
    
    if (INTERRUPT_OCCURED == INTCONbits.T0IF)
    {
        INTI_TMR0_ISR();
    }
    else
        { /* Nothing */ }
    
    if (INTERRUPT_OCCURED == PIR1bits.TMR1IF)
    {
        INTI_TMR1_ISR();
    }
    else
        { /* Nothing */ }
    
    if (INTERRUPT_OCCURED == PIR1bits.TMR2IF)
    {
        INTI_TMR2_ISR();
    }
    else
        { /* Nothing */ }
    
    if (INTERRUPT_OCCURED == PIR2bits.TMR3IF)
    {
        INTI_TMR3_ISR();
    }
    else
        { /* Nothing */ }
    
    if ((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURED == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else
        { /* Nothing */ }
    
    if (INTERRUPT_OCCURED == PIR2bits.CCP2IF)
    {
        CCP2_ISR();
    }
    else
        { /* Nothing */ }
    
    if ((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURED == PIR1bits.TXIF))
    {
        USART_TX_ISR();
    }
    else
        { /* Nothing */ }
    
    if ((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCURED == PIR1bits.RCIF))
    {
        USART_RX_ISR();
    }
    else
        { /* Nothing */ }
    if ((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCURED == PIR1bits.SSPIF))
    {
        SPI_ISR();
    }
    else
        { /* Nothing */ }
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    
}
#else
void __interrupt() InterruptManager(void)      /* IVT */  /* Address = 0x08 */    
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCURED == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else 
        { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCURED == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else
        { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCURED == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else
        { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF))
    {
        
    }
    else
        { /* Nothing */ }
    
    if ( (INTERRUPT_ENABLE == INTCONbits.T0IE) && (INTERRUPT_OCCURED == INTCONbits.T0IF) )
    {
        INTI_TMR0_ISR();
    }
    else
        { /* Nothing */ }
}
#endif
