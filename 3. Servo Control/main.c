/*
 * main.c
 *
 *  Created on: 4/26/2023
 *      Author: Ethan Struble
 *
 *
 */

#include <msp430.h> 

void GPIOInit();
void TimerInit();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    GPIOInit();
    TimerInit();

    PM5CTL0 &= ~LOCKLPM5;
    __bis_SR_register(GIE);

    return 0;
}
void GPIOInit()
{
    //Pin used for the Servo
    P6OUT &= ~BIT0;     // Set P6.0 to 0
    P6DIR |= BIT0;      // Set P6.0 as output
    P6SEL0 |= BIT0;     // Select PWM
    P6SEL1 &= ~BIT0;    // Clear bit

    //Config button 4.1
    P4DIR &= ~BIT1;   // Setting Pin 4.1 to an input
    P4OUT |= BIT1;
    P4REN |= BIT1;    // using pull up resistor
    P4IE  |= BIT1;    // setting it to an interrupt
    P4IES &= ~BIT1;   // Button 4.1 is ready
    //Config button 2.3
    P2DIR &= ~BIT3;   // Setting Pin 2.3 to an input
    P2OUT |= BIT3;
    P2REN |= BIT3;    // using a pull up resistor
    P2IE  |= BIT3;    // Setting it to an interrupt
    P2IES &= ~BIT3;   // Button 2.3 is ready
}
void TimerInit()
{
    // Configure Timer_B3
    TB3CTL = TBSSEL_2 | MC__UP | TBCLR | TBIE;
    TB3CCTL0 = OUTMOD_7;                         // CCR1 reset/set
    TB3CCR0 = 20000;                             // 20kHz frequency
    TB3CCR1 = 1500;                              // starting duty cycle
}

// Port 2 interrupt
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;                         // Clearing P2.3 interrupt
    if(TB3CCR1 >= 1000)
        TB3CCR1 -= 100;                     // decreasing the duty cycle by 5%
    else
        TB3CCR1 = TB3CCR1;                  // Hard stop
}
// Port 4 interrupt
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT1;                         // Clearing P4.1 interrupt
    if(TB3CCR1 <= 1000)
        TB3CCR1 += 100;                     // increasing the duty cycle by 5%
    else
        TB3CCR1 = TB3CCR1;                  //Hard stop
}
