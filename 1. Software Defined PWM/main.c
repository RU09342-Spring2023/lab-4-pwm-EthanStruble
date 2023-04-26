/*
 *      Created: 4/26/2023
 *      Author: Ethan Struble
 *
 */

#include <msp430.h>

void main()
{
  WDTCTL = WDTPW | WDTHOLD; // Watchdog timer disable

  GPIOInit();               // All the pins I need
  TimersInit();             // All the timers I need

  PM5CTL0 &= ~LOCKLPM5;

  __bis_SR_register(LPM0_bits + GIE);
  __no_operation();
}

//Setting up all the pins I need
void GPIOInit()
{
  P1DIR |= BIT0;    // Setting Pin 1.0 to an output
  P1OUT &= ~BIT0;   // Red Led Ready
  P6DIR |= BIT6;    // Setting Pin 6.6 to an output
  P6OUT &= ~BIT6;   // Green Led Ready

  P4DIR &= ~BIT1;   // Setting Pin 4.1 to an input
  P4OUT |= BIT1;
  P4REN |= BIT1;    // using pull up resistor
  P4IE  |= BIT1;    // setting it to an interrupt
  P4IES &= ~BIT1;   // Button 4.1 is ready

  P2DIR &= ~BIT3;   // Setting Pin 2.3 to an input
  P2OUT |= BIT3;
  P2REN |= BIT3;    // using a pull up resistor
  P2IE  |= BIT3;    // Setting it to an interrupt
  P2IES &= ~BIT3;   // Button 2.3 is ready
}

//Timers used for PWM
void TimersInit()
{
  // Initialize Timer 0
  TB0CTL = TBSSEL__SMCLK | MC__UP | TBIE;   // Enabled using SMCLK setting to up mode and enabling the interrupt
  TB0CCTL1 |= CCIE;                         // Enabling capture/compare interrupt
  TB0CCR0 = 1000;                           // CCR0 max will be 1kHZ
  TB0CCR1 = 500;                            // CCR1 will be 50% max (duty cycle)

  // Initialize Timer 1
  TB1CTL = TBSSEL__SMCLK | MC__UP | TBIE;   // Enabled using SMCLK setting to up mode and enabling the interrupt
  TB1CCTL1 |= CCIE;                         // Enable capture/compare interrupt
  TB1CCR0 = 1000;                           // CCR0 max will be 1kHZ
  TB1CCR1 = 500;                            // CCR1 will be 50% max (duty cycle)
}

// Button 2.3 interrupt
#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR()
{
  P2IFG &= ~BIT3;               // Clearing P2.3 IFG

  if (TB0CCR1 >= 1000)          // Checking for overflow
    TB0CCR1 = 0;                // Set duty cycle to 0%

  else
    TB0CCR1 += 100;             // Incrementing duty cycle by 10%
}
// Button 4.1 interrupt
#pragma vector=PORT4_VECTOR
__interrupt void P4_ISR()
{
  P4IFG &= ~BIT1;       // Clearing P4.1 IFG

  if (TB1CCR1 >= 1000)  // Checking for overflow
    TB1CCR1 = 0;        // Set duty cycle to 0%
  else
    TB1CCR1 += 100;     // Incrementing duty cycle by 10%
}

// Timer0_B1 Interrupt
#pragma vector=TIMER0_B1_VECTOR
__interrupt void T0_ISR()
{
  switch (__even_in_range(TB0IV, TB0IV_TBIFG))
  {
    case TB0IV_NONE:    // Nothing happens
      break;
    case TB0IV_TBCCR1:  // CCR1 Set the pin to a 0
      P1OUT &= ~BIT0;
      break;
    case TB0IV_TBCCR2:  // Not used
      break;
    case TB0IV_TBIFG:   // overflow set the pin to 1
      P1OUT |= BIT0;
      break;
    default:            //Default case
      break;
  }
}

// Timer1_B1 Interrupt
#pragma vector=TIMER1_B1_VECTOR
__interrupt void T1_ISR()
{
  switch (__even_in_range(TB1IV, TB1IV_TBIFG))
  {
    case TB1IV_NONE:    // nothing happens
      break;
    case TB1IV_TBCCR1:  // CCR1 Set the pin to a 0
      P6OUT &= ~BIT6;
      break;
    case TB1IV_TBCCR2:  // Not used
      break;
    case TB1IV_TBIFG:   // overflow set the pin to 1
      P6OUT |= BIT6;
      break;
    default:           // Default case
      break;
  }
}
