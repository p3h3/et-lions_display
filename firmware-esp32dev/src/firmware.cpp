#include <Arduino.h>

#include "bitmaps/chunking.h"
#include "bitmaps/bitmaps.h"
#include "ble/ble.h"

#include "images/img.h"



// This is the key to high framerates!
// it enables the 5 output pins to shift out the data in parallel rather than sequentially 
// => 5 times the bandwith!
#define FASTLED_ESP32_I2S 


#include <FastLED.h>

#define LEDS_PER_PIN 225

//uint8_t bm[25][45][3];
uint16_t chunks[25][45];
CRGB leds[5*LEDS_PER_PIN];







void updateLEDs(){
  uint8_t r,g,b;

  for(int y = 0; y < 25; y++){
    for(int x = 0; x < 45; x++){
      uint16_t led_number = chunks[y][x];

      r = bm[y][x][0];
      g = bm[y][x][1];
      b = bm[y][x][2];

      leds[led_number] = CRGB(r, g, b);
    }
  }
}






void setup() {
  Serial.begin(115200);

  Serial.printf("==========\nLED Matrix\n==========\n");
  Serial.printf("==========\nLED Matrix\n==========\n");

  // add the parts of the matrix as segments of the leds array
  FastLED.addLeds<WS2812B, 18, EOrder::GRB>(leds, 0 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 19, EOrder::GRB>(leds, 1 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 21, EOrder::GRB>(leds, 2 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 22, EOrder::GRB>(leds, 3 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 23, EOrder::GRB>(leds, 4 * LEDS_PER_PIN, LEDS_PER_PIN);
    

  // basically a lookup table for led numbers with input parameters y and x
  chunking(&chunks[0][0]);

  bleInitBitmapPointer(&bm[0][0][0]);

  allTogether();

}

void loop() {

  // FastLED show takes about 7ms
  updateLEDs();
  FastLED.show();

  // together it's about 33ms - about 30fps
  delay(26);
}
