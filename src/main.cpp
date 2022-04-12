//#include <Arduino.h>
#include <M5Stack.h>
#include <Wire.h>
//#include "PCF8574.h"
#include <Adafruit_LEDBackpack.h>
#include <arduino-timer.h>


#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif


Adafruit_LEDBackpack matrix1 = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix2 = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix3 = Adafruit_LEDBackpack();

uint8_t counter = 0;

void setup() {
    M5.begin(true, true, true);
    M5.Power.begin();
    M5.Lcd.clear(BLACK);

    Serial.begin(9600);
    Serial.println("HT16K33 test");

    matrix1.begin(0x71);  // pass in the address
    matrix2.begin(0x72);  // pass in the address
    matrix3.begin(0x73);  // pass in the address
}

void loop() {
    // paint one LED per row. The HT16K33 internal memory looks like
    // a 8x16 bit matrix (8 rows, 16 columns)
    for (uint8_t i=0; i<8; i++) {
        // draw a diagonal row of pixels
        matrix1.displaybuffer[i] = _BV((counter+i) % 16) | _BV((counter+i+8) % 16)  ;
        matrix2.displaybuffer[i] = _BV((counter+i) % 16) | _BV((counter+i+8) % 16)  ;
        matrix3.displaybuffer[i] = _BV((counter+i) % 16) | _BV((counter+i+8) % 16)  ;
    }
    // write the changes we just made to the display
    matrix1.writeDisplay();
    matrix2.writeDisplay();
    matrix3.writeDisplay();
    delay(100);

    counter++;
    if (counter >= 16) counter = 0;
}
