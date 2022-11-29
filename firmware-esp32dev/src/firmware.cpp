#include <Arduino.h>

#include "chunking.h"
#include "bitmaps.h"
#include "ble.h"

#include "img.h"




#define FASTLED_ESP32_I2S // This achieves the desired degree of parallelization
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
  updateLEDs();
  FastLED.show();

  delay(100);



}
