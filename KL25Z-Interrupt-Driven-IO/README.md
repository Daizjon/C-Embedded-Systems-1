Works with I/O, Interrupts, Stack Use, and Timing <br/>

***The main.c file is the completed version of this project*** <br/>
To see other files such as the system info as well as the early uncompleted stages check out the sources, include and device folders.<br/>

Hardware bill of materials (beyond NXP FRDM-KL25Z and breadboard): <br/>
• 3x Momentary Switch <br/>
• 3x 1uF Capacitor (This is optional. You may use one for each switch if available) <br/> <br/>

Task 1: Set up the breadboard, and configure microcontroller settings within Keil uVision5 as normal. Then begin new project. <br/>
Task 2: Implement a system that measures how quickly a person can press a switch in response
to an LED being lit. This will require setting up the hardware as specified in task 1
and creating a new Keil MDK project for software development. <br/>

Hardware Setup and I/O – Use momentary switches SW1-SW3 to control the system. You can
use an external resistor R1 or enable the internal pull-up resistor in the MCU. Use the Freedom
RGB LEDs as the output device. Capacitors may be used to debounce your button signals, but
are not strictly required. <br/> <br/>
Wrote a C program to perform the following: <br/>
• Initialize peripherals
• Declare a counter
• Enable IRQ (Interrupt Request)
• Loop while performing the following:
• Turn on one of the LEDs indicated by a state variable.
• Loop while polling to see if a button has been pressed.
• If SW1 has been pressed, perform the following
◦ Modify the LED state variable.
◦ Change the LED color.
• If SW2 has been pressed, perform the following
◦ Turn off all LEDs
◦ Clear the counter
◦ Clear flag(s)
◦ Wait a random amount of time (e.g. within 1-3 seconds)
◦ Turn on the LED indicated by the state variable.
◦ Loop while incrementing the counter.
◦ Repeat until the ISR has been triggered by pressing SW3, as indicated by a
flag being set
◦ Save the counter value in memory
◦ Wait for approximately 5 seconds
The interrupt service routing (ISR) should perform the following:
If SW3 is pressed, set a flag indicating that the ISR was triggered by SW3.
This flag will break your counter loop.
You will also need some support functions:
• Use the LEDs.c module from the tutorial to initialize and control the RGB LEDs.
• Use the C standard library function rand() to generate a random integer.
• Create and calibrate a delay-loop function Delay_millisec(unsigned int time_del)
which creates a delay of approximately “time_del” milliseconds. Tune your
delay loop through experimentation.

Task 3: Record the average number of iteration counts it takes, for several people, for each of the
primary colors of LED: Red, Blue, and Green. Your LED state variable will allow you to change
which color you are testing without restarting your microcontroller. You can either set a
breakpoint in your code and manually record the number of iteration counts, or you can simply
set up your code to loop a number of times storing the result in an array to be averaged after the
final loop.
Typical iteration counts are 500 thousand to 1-2 million.
