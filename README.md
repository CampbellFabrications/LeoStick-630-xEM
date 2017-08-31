# LeoStick-630-xEM
A Freetronics LeoStick and RDM630 RFID reader for the DangerousThings xEM implant (and others)

Please look at the rfid1.jpg file for reference when creating this USB reader.

Preparation:~~~

Cut P2's LED pin, P1's RX, NC, GND, and 5V pins from the RDM630 with flush cutters to prevent them from contacting the Leostick Pins.

Soldering:~~~

Press the RDM630 to the piezo buzzer underneath the Leostick and solder P2's 5V and GND pins to the respective Leostick 5V and GND pins, as well as P1's TX pin to Leostick's D10 pin.

If the other pins were removed, there will be 1mm space between the RDM630 flush-cut header pin and the underside of the LeoStick PCB, and the Antenna pins should be exposed facing upwards.

Updates:~~~

the RX and NC pins are soldered in the photo, however they can be omitted if those pins are needed elsewhere.
