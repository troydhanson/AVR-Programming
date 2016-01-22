The fifth chapter of Make: AVR Programming presents a challenge for those of us with the ATTiny85:
our chip has no USART hardware! But I really wanted to try serial communication. So I learned the
way to do serial communication in software, called bitbanging. It is simply alternating the high/low
state of a GPIO pin with precise timing for the chosen baud rate.

My setup:

* ATTiny85
* Adafruit FTDI friend (to convert serial to USB, so I can see the result)
* Two wires connect the ATTiny85 to the FTDI Friend: GND, and pin 3 (on the ATTiny85) to RX (on the Friend)

The code I wrote sends an alphabetic character each second. To send a character it sends its 8 bits
(LSB to MSB) separated by a baud delay. Well, it also needs to prepend a start bit (0) and a stop bit (1).
See, the quiescent state of the serial line is high (or 1), so the start bit pulls it low (0). That starts
the clock ticking that expects a bit every 1/b seconds (where b is the baud rate). The convention we're 
speaking is called 8N1 which means 8 data bits, no parity bit and 1 stop bit.

To build and run the program, run make and sudo make flash. Wire the pins as described. Plug the FTDI Friend
into something like a Linux host via its USB connector. On the host run a serial program like 

    screen /dev/ttyUSB0 9600

You should see the letters march across the screen one per second. Note change the serial device name above
to whatever device name the Friend acquired (use dmesg|tail if you need help).

Last note: the inter-bit delay when transmitting the bits is 1/b as stated above. For this program that is
1/9600 (or .00010 seconds). This program uses the delay_us routine to provide that delay in microseconds.
