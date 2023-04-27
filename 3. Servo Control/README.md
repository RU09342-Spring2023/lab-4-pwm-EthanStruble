# Servo Control
Servos can be controlled with PWM, determining which angle should be taken by how wide the duty cycle is. You will need to build a manual control for a servo using the two buttons on the development board.

## Task
You can chose whichever pin you want to control your Servo (but I might recommend one with hardware PWM control). Your will use the two buttons on your development board to control the position of your servo. The button on the left side of the board should turn the servo counterclockwise, the button on the right side of the board should turn it clockwise.

The servo will have a limit to the amount of degree it can rotate, so make sure you take a look at that before coding.

The servo will need to be most likely powered from the power supply on the bench. If you do this, you need to make sure you connect common ground between the supply and your board. Otherwise, your system will not work or you risk damaging your board.

## Deliverables
You will need to upload the .c file and a README explaining your code and any design decisions made.
# README
## Main Function
This is the standard main function, it calls your functions that initialises all my pins and timers.
![image](https://user-images.githubusercontent.com/113445493/234754193-b9044c7d-58e9-4e18-ac73-cf4971de0bf5.png)
## GIPOInit
Similar to the main function, this is pretty standard initialization of button P2.3 & P4.1. The other pin initalised are used for the Servos I set P6.0 to an output so the servo can recieve the signal then the other two pins allow the servo to recieve a PWM signal and to clear all of the bits.
![image](https://user-images.githubusercontent.com/113445493/234755734-f9eb5d05-d16c-4844-b66c-4f5362878162.png)\
## TimerInit
For the timer I used the SMCLK this allows me to use a higher frequency compared to the ACLK. Then I cleared out the CCR1 so its value is zero. Then I set a hard limit using CCR0 at 20,000 then had a duty cycle starting at 1,500 this will be used to move the servo left and right. CCR0 will be used to make sure the servo does exceed its max limits
![image](https://user-images.githubusercontent.com/113445493/234756724-0e1b2ed6-9533-409e-b74c-40b7673a0f81.png)
## Interrupts
These interrupts allow the Servo to move left and right. The interrupt for Port 2 is controlled using button P2.3 this port moves the servo to the left by subtracting the values from CCR1 thus lowering its. Then it's stopped when it hits its hard limit set by CCR1 this prevents the servo from turning too much causing drastic issues. The interrupt for port 4 is about the same as port 2 but it moves the servo to the right by adding values to the duty cycle, other than that they are the same. 
![image](https://user-images.githubusercontent.com/113445493/234757706-37abbe33-bcdf-49ad-b30d-19b0749dfcd6.png)
