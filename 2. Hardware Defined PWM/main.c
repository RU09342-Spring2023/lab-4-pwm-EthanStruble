/*
 * main.c
 *
 *  Created on: 4/26/2023
 *      Author: Ethan Struble
 */
#define RG 0            // This making switching between LED values this is RED to Green
#define GB 1            // This is Green to Blue
#define BR 2            // This is Blue Red
char LEDColor = RG;     // initial LED value is Red to Green
void GPIOInit();
void TimerInit();

#include <msp430.h>

void main()
{
    WDTCTL = WDTPW | WDTHOLD;       //Stop watchdog timer

    GPIOInit();                     // Starts all of the pins that are required
    TimerInit();                    // Starts up the timer

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);
    __no_operation();
}
//This is setting all of the pins I will use to fade the RGB LEDS
void GPIOInit()
{
    //This is for P6.0
    P6DIR |= BIT0;              // Set output for RGB LED
    P6OUT &= ~BIT0;             // Initialize pin to power-off state
    P6SEL0 |= BIT0;             // Select PWM
    P6SEL1 &= ~BIT0;            // Clear bit
    P6IE |= BIT0;               // Enable interrupt

    //This is for P6.1
    P6DIR |= BIT1;              // Set output for RGB LED
    P6OUT &= ~BIT1;             // Initialize pin to power-off state
    P6SEL0 |= BIT1;             // Select PWM
    P6SEL1 &= ~BIT1;            // Clear bit
    P6IE |= BIT1;               // Enable interrupt

    //This is for P6.2
    P6DIR |= BIT2;              // Set output for RGB LED
    P6OUT &= ~BIT2;             // Initialize pin to power-off state
    P6SEL0 |= BIT2;             // Select PWM
    P6SEL1 &= ~BIT2;            // Clear bit
    P6IE |= BIT2;               // Enable interrupt
}
void TimerInit()
{
    TB3CCR0 = 1000 - 1;                                  // PWM period
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
    TB3CCTL1 = OUTMOD_7;                               // Reset/set CCR1
    TB3CCTL2 = OUTMOD_7;                               // Reset/set CCR2
    TB3CCTL3 = OUTMOD_7;                               // Reset/set CCR3

    // Initial duty cycle for each LED
    TB3CCR1 = 1000 - 1;                                // Setting Red LED to 999
    TB3CCR2 = 0;                                       // Setting Blue LED to 0
    TB3CCR3 = 0;                                       // Setting Green LED to 0

    // Setup timer for fade
    TB1CTL = TBSSEL_1 | MC_2 | ID_3 | TBCLR | TBIE; // ACLK, continuous mode, divide by 8, clear timer, enable interrupt
    TB1CCTL0 |= CCIE;                                  // Enable interrupt
    TB1CCR0 = 1;                                      // Initial period of timer
}
// TimerB1 interrupt
#pragma vector = TIMER1_B0_VECTOR
__interrupt void TIMER1_B0_ISR(void)
{
    switch (LEDColor)
    {
    case RG:                        // Red goes to Green
        TB3CCR1--;                  // decrease Red value by 50%
        TB3CCR3++;                  // increase Green value by 50%
        if (TB3CCR1 == 0)
        {
            LEDColor = GB;
        }
        break;
    case GB:                        // Green goes to Blue
        TB3CCR3--;                  // decrease Green value by 50%
        TB3CCR2++;                  // increase Blue value by 50%
        if (TB3CCR3 == 0)
        {
            LEDColor = BR;
        }
        break;

    case BR:                        // Blue goes to Red
        TB3CCR2--;                  // decrease Blue value by 50%
        TB3CCR1++;                  // increase Red value by 50%
        if (TB3CCR2 == 0)
        {
            LEDColor = RG;
        }
        break;
    }
    // This prevents overflow
    if (TB3R >= 60000)
        TB3R = 1;
    TB1CCR0 += 20;      // Fade speed
}
