/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor
Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/
These sensors use I2C communicate, at least 2 pins are required 
to interface
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/
#include <Wire.h>
#include "Adafruit_MPR121.h" //https://github.com/adafruit/Adafruit_MPR121
#include <Keyboard.h>

Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  Keyboard.begin();         
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    while (1);
  }  
  digitalWrite(13,LOW);
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<10; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Keyboard.print(i);
    }
  }

  // reset our state
  lasttouched = currtouched;
}
