This is a modification of Chapter07_Analog-to-Digital-Conversion-I/slowScope. The 
original program performs continuous A/D conversion, writing the converted values 
to the serial port at a fixed rate. 

This program is a modification that also toggles a speaker pin at the rate the sampled
signal crosses a threshold. In other words, it makes an audio representation of a
signal.

# Edit Makefiles for MCU and PROGRAMMER

This program needs an AVR chip with USART. I use the ATMega328. Make sure the
library Makefile, and this Makefile, are configured for the proper chip and
programmer:

    vi ../AVR-Programming-Library/Makefile
    vi Makefile

Set MCU and PROGRAMMER in both appropriately. For me the values are:

    MCU   = atmega328p
    PROGRAMMER_TYPE = usbtiny

# Physical setup

PC0 (pin 23) - A/D input 
PD1 (pin 3) - serial output (TX)
PD6 (pin 12) - to speaker +
speaker - thru capacitor 10 uF cap to GND
