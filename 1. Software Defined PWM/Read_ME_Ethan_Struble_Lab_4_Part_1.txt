Ethan Struble Lab 4 Part 1
This project utilises the use of LED, button, and timers to increase the brightness of an LED.
It doesn't increase linearly but it will keep increasing by 10 percent depending on how many times the button is pressed.
For my code I declared P1.0 and P6.6 as output because they are my LEDS and I declared P2.4 and P4.1 inputs because they are my buttons.
For my Timers I used TimerB0 and TimerB1 because I just had to use a timer doesn't matter which ones.
I then initialised them to use the SMCLK in continuous mode with interrupts enabled, this is so I can increase the CCR1 once an interrupt flag is fired.
The starting value for CCR0 is 1000(100%) and the starting value for CCR1 is 500(50%). This is what the project called for.
CCR0 is responsible for setting the max period height and CCR1 is the brightness of the LED, it starts off at 50%(500) brightness then will will keep increasing by 10%(100) until it reaches
100%(1000) which then it shall drop to 0%.
The interrupts that I created for port 2 and 4 check for these button presses and will know when to increase the brightness.
Each of these buttons run off different timers but serve the same purpose.
