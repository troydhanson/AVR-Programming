This example builds on the [previous one](../02-tdh-bitbang-tx/README.md) extending the bitbanging
to receiving. The logic reads a byte and then echoes it back.

It's the same as the previous setup, with the addition of ATTiny85's pin 2 wired to the FTDI Friend's
TX pin (the Friend is transmitting TO the ATTiny). The Friend has helpful little arrows on it to 
help demystify that TX means "from host to chip" and RX means "from chip to host".

This program is made the usual way with make; sudo make flash.

It has a timing glitch; about 80% of characters are echoed properly. The others are missed and then
the following character glitches. I am not sure if this is due to pin 2's pullup resistor setting or
a timing factor, or some other electrical subtlety I have overlooked.
