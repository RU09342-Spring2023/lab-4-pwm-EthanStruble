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
