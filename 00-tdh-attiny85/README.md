AVR Programming 

The book Make: AVR Programming by Elliot Williams is the basis for these learning projects.
This repo is a fork of his original repo that has the book's projects. I am
adding my own notes and variations in this fork of the repository.

Troy D. Hanson

# Getting started

My setup is:

* Atmel ATTiny85 
* SparkFun Tiny AVR Programmer
* Linux to run avrdude and avr-gcc

Plug the ATTiny85 chip into the Tiny programmer. The circle on the chip goes on the notched end 
of the Tiny socket. Plug the Tiny via USB into the Linux host. I use a powered USB hub to protect
my Linux host from my own electrical mishaps. On the Linux host run:

    sudo avrdude -c usbtiny -p t85

to confirm that avrdude can communicate with the ATTiny85 and the programmer.

