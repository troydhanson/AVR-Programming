This ATTiny85 program selectively switches a MOSFET on, to power another
circuit.  It uses a pushbutton (apply power) on pin 5 (PB0) to tell the ATTiny
to do so. In this state, the ATTiny pulls pin 6 (PB1) up. This pin is connected
to the FET gate.  When doing so, the ATTiny also lights an LED on pin 7 (PB2).

The FET has gate, drain and source pins. Driving the gate high allows current
to flow between source and drain. I have a FET embedded in a TinkerKit plug-in
module that has an IC connected to it. This complicates things slightly. In
this setup the FET gate is the middle pin on the TinkerKit plug-in connector; a
Vcc (3.3 or 5v) pin and a ground pin surround it. The other end of the
TinkerKit module has ground, +V, M+, and M- pins. The +V pin is wired to Vcc
(Vin) and M+ to the controlled (external) circuit's Vcc, with M- to the
controlled external circuit's ground.

The program also lights an LED on pin 2 (PB3) when you push the button on pin 3
(PB4). 

The first version of this program lit an LED on pin 1 (PB5) -- but it turns out
that is a reset pin; bringing it low by grounding it through the LED/resistor
held the AVR in reset.

                         ----
  NOT CONNECTED  (PB5) 1|o   |8 (Vcc)
    PRESSED LED  (PB3) 2|    |7 (PB2)  FET GATE LED
         BUTTON  (PB4) 3|    |6 (PB1)  FET GATE
                 (GND) 4|    |5 (PB0)  BUTTON TO DRIVE FET GATE
                         ----

The buttons require the pull up resistors, since they float when the button is
open.  This program configures the ATtiny's internal pull ups on those pins.

The LED anode (longer leg) connects to the ATtiny pin. The LED cathode goes
through a resistor to ground.

To see the point of this program, wire the FET's drain and source to the Vcc
and ground in an external circuit. The ATtiny controls power to that circuit.
The FET sources that current, not the pins of the ATTiny. The FET functions as
a logic-controlled switch.

This program is made the usual way with 

    make; sudo make flash


