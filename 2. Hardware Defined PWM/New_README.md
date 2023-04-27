# README
This is the README Hardwawre Defined PWM lab, this is refrence to main.c in this repository.
## Definitions:
The image below is all of the definitions for my code. These definitions allow switching between all of the colors easier as showen later in the code.
Each one of these definitions are named accordingly.
![image](https://user-images.githubusercontent.com/113445493/234738858-b43476c2-a1ac-44ee-8655-b4261931ba4d.png)

## Main Function:
The first two lines of code initials all of the functions that are needed. Then in the main function they are called and we do other intialization.
![image](https://user-images.githubusercontent.com/113445493/234738988-5a8c01c8-479b-45c2-9d16-91c8bd626a17.png)

## GIPOInit
This initalizes all of the pins we used for our program. All three of the pins are initialized in the same manner, the pins used are P6.0, P6.1, & P6.2. I first set them to an output this is so we can send a signal to the extrenal RGB LED. Then I made the pin start in the off condition. Next this allows me to choice which PWM this pin receives. This clears the pin. This enables the interrupt condition so we can use interupts for this pin. All of the pin are the same conitions I just explained.  
![image](https://user-images.githubusercontent.com/113445493/234740459-09c34917-a622-46ea-bafc-96bd44f96435.png)

## TimerInit
This timer is used to fade in between all of the RGB values each color depends on how much of red green or blue there is at a given time. So first couple of lines of code sets the limit of TB3CCR0 to a max value of 999, this is because the max value a give RBG color can be set to is 999. Then there are reset conditions for all of the CCR values so we know we start off at red. Next I set the intial conditions for the RBG values. I want to start at the max for red which is 999 and I only want red so the other values are set to 0. Final I have the second timer that I use, this actually does the fading. I have it set so it can cause interupts to happen and it causes an interupt every second. For the clock singal I used the ACLK and set it to its highest value by using 8 clock dividers, I also had enabled interrupt.
![image](https://user-images.githubusercontent.com/113445493/234744529-64e37d45-60fd-4f0a-88f9-f2add79a25da.png)
## Interrupts
This interrupt is triggered from timerB1 every second. Whenever it is interrupted a switch case is checked this switch statement looks defintions that were declared early in the code to check which mode the LEDs are at. Then whatever state its in then it'll decrease that value by 50% then increase the next value by 50% this keeps going until the first value has hit zero. This rinse reapeated for all of the RBG values.
![image](https://user-images.githubusercontent.com/113445493/234747171-5ab4778d-c9a4-4eca-956a-680bb09cb046.png)
