Blinking an LED

The second chapter of Make: AVR Programming needs a small adaptation for those of us with an ATTiny
chip. It does not have hardware USART, so in the AVR-Programming/AVR-Programming-Library directory,
rename USART.c to have another suffix (I used USART.c.bak). This prevents it from trying to build
that file. 

In that same directory, change the Makefile to build for the ATTiny85 by changing the MCU line:

    MCU = attiny85
    PROGRAMMER_TYPE = usbtiny

and the programmer as shown. Run 'make' to build the library. Voila. The library has now been built without the 
USART code.

The blinkLED example in the Chapter 2 directory can now be compiled. Make sure the MCU is set in that Makefile too.
Then do:

    make
    sudo make flash

The LED on the Tiny programmer should now be blinking. You can take the ATTiny85 out of the socket, put it on a
breadboard, power it using +5V and GND (I used a USB cable that I cut to expose the wiring, then take the power
wires and run them to the breadboards + and - rails). Then connect an LED's positive lead to pin 0 and its other
lead through a resistor to GND. You now have a standalone circuit blinking the LED through C code executing in
the ATTiny85.
