#include <ReceiveOnlySoftwareSerial.h>
/*  visit http://gammon.com.au/Arduino/ReceiveOnlySoftwareSerial.zip 
for the single pin SoftwareSerial interface library.
SoftwareSerial is the alternative, 
but I wanted to define as little pins as possible.
*/

/*
Following the schematic for the RDM6300 (http://wiki.seeed.cc/125Khz_RFID_module-UART/) 
The P1's TX and P2's 5V & GND are the only functional soldered pins to the Leostick.
P1's NC pin can be soldered on for physical strength, but it is not required.

The requirement for this reader to work is for the RDM630 to be placed on the underside
of the Leostick, with the P2's 5V pin lining up with the Leostick 5V,
and the P1 TX pin lining up with Leostick Pin 10 (which also happens to be the RGB's Blue LED)

*/
int data1 = 0;
int ok = -1;

#define redPin 13 //pin used for failed authorisation.
#define soundPin 11 //pin used for successful authorisation, probably should go to a relay.
#define rxPin 10 //receiving pin for the RDM630's TX pin.
// blue pin is receiving the reader data, useful for diagnostics


ReceiveOnlySoftwareSerial RFID(rxPin); // RX only
int const readlength = 13; // how many bytes are being read.

int tag1[readlength] =   {2,52,48,48,48,56,54,66,49,52,70,51,56}; // random numbers
int tag2[readlength] =   {2,0,0,0,0,0,0,0,0,0,0,0,0}; // put your xEM here 
int newtag[readlength] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; // used for read comparisons

void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
  pinMode(soundPin, OUTPUT); // set up the buzzer
  pinMode(redPin, OUTPUT); // set up the red LED
}

boolean comparetag(int aa[readlength], int bb[readlength])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < readlength ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == readlength)
  {
    ff = true;
  }
  return ff;
}

void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true)
  {
    ok++;
  }
  if (comparetag(newtag, tag2) == true)
  {
    ok++;
  }
}

void readTags()
{
  ok = -1;

  if (RFID.available() > 0) 
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.

    for (int z = 0 ; z < readlength ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      Serial.print(data1);
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads

    // do the tags match up?
    checkmytags();
  }

  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    Serial.println("Accepted");
    delay(500);
    tone(soundPin,1000);
    delay(1000); // Change this to how long you want an output to be active
    noTone(soundPin);
    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
    Serial.println("Rejected");
    digitalWrite(redPin,HIGH);
    delay(1000);
    digitalWrite(redPin, LOW);
    ok = -1;
  }
}

void loop()
{
  readTags();
}
