ATMega328 

I use the SparkFun AVR Pocket Programmer. I made an adapter board like the one on p.32
of MAKE: AVR Programming by Elliot Williams. This breaks the six-pin ISP connector out
to the proper pins on the ATMega328. It sits over the chip on a breadboard with the pins
going down around the outside perimeter of the chip.

    sudo avrdude -c usbtiny -p m328p

