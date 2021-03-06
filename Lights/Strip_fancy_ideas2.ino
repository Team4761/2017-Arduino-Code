// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>
// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this
// Created 29 March 2006
// This example code is in the public domain.
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"


#define PIN 2
#define LED_COUNT 46
boolean Is_enabled = false;
int value = 0;
long color = RED;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.
  // leds2.begin();  // Call this to start up the LED strip.
  //clearLEDs();   // This function, defined below, turns all LEDs off...
  // leds2.show();   // ...but the LEDs don't actually update until you call this.
  Serial.println("Done with setup");
  cylon(leds, BLUE, 10);
  leds.begin();
 // leds.show();
 // clearLEDs();
  cylon(leds, RED, 10);
 leds.begin();
  //leds.show();
  //sclearLEDs();
  Serial.println("Done with setup2");
  

}

void loop() {
 //cylon(leds,color, 10  );
 //leds.begin();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  Serial.println(howMany);
  Serial.flush();
  Serial.println("Event recieved");
  //while (1 < Wire.available()) { // loop through all but the last
  //char c = Wire.read(); // receive byte as a character
  //Serial.print(c);         // print the character
  //}

  int y = Wire.read();    // receive byte as an integer
  Serial.println(y);
  int x = Wire.read();
  Serial.println(x);// print the integer
  Serial.flush();

  if (x == 1){
    color  = PURPLE;
    Serial.println("received 1");
    }
    else if (x == 2){
    color = YELLOW;
     Serial.println("received 2");
    } 
    else if(x ==3){
      color = BLUE;
       Serial.println("received 3");
    }

     else if(x == 4){
      color = GREEN;
       Serial.println("received 4");
    }
    else if (x == 5){
      color = BROWN;
       Serial.println("received 5");
    }
    else if(x == 6){
      color = WHITE;
       Serial.println("received 6");
    }
}
void cylon(Adafruit_NeoPixel leds, unsigned long color, byte wait)
{

  //Serial.println("Cylon start");
  //Serial.flush();
  // weight determines how much lighter the outer "eye" colors are
  const byte weight = 4;
  // It'll be easier to decrement each of these colors individually
  // so we'll split them out of the 24-bit color value
  byte red = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue = (color & 0x0000FF);

  // Start at closest LED, and move to the outside
  for (int i = 0; i <= LED_COUNT - 1; i++)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
    // Now set two eyes to each side to get progressively dimmer
    for (int j = 1; j < 3; j++)
    {
      if (i - j >= 0)
        leds.setPixelColor(i - j, red / (weight * j), green / (weight * j), blue / (weight * j));
      if (i - j <= LED_COUNT)
        leds.setPixelColor(i + j, red / (weight * j), green / (weight * j), blue / (weight * j));
    }
    leds.show();  // Turn the LEDs on
    delay(wait);  // Delay for visibility
  }

  // Now we go back to where we came. Do the same thing.
  for (int i = LED_COUNT - 2; i >= 1; i--)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);
    for (int j = 1; j < 3; j++)
    {
      if (i - j >= 0)
        leds.setPixelColor(i - j, red / (weight * j), green / (weight * j), blue / (weight * j));
      if (i - j <= LED_COUNT)
        leds.setPixelColor(i + j, red / (weight * j), green / (weight * j), blue / (weight * j));
    }

    leds.show();
    delay(wait);
  }

  // Serial.println("Cylon End");
  // Serial.flush();

}//end cyclon

// Cascades a single direction. One time.
void cascade(Adafruit_NeoPixel leds, unsigned long color, byte direction, byte wait)
{
  while (true) {
    if (direction == TOP_DOWN)
    {
      for (int i = 0; i < LED_COUNT; i++)
      {
        // clearLEDs();  // Turn off all LEDs
        leds.setPixelColor(i, color);  // Set just this one
        leds.show();
        delay(wait);
      }
    }
    else
    {
      for (int i = LED_COUNT - 1; i >= 0; i--)
      {
        //  clearLEDs();
        leds.setPixelColor(i, color);
        leds.show();
        delay(wait);
      }
    }
  }
}

// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.
void clearLEDs()
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
    //leds2.setPixelColor(i, 0);
  }

}

// Prints a rainbow on the ENTIRE LED strip.
//  The rainbow begins at a specified position.
// ROY G BIV!

