#include <Arduino.h>

#include "bitmaps/chunking.h"
#include "bitmaps/bitmaps.h"
#include "ble/ble.h"

#include "images/obam.h"
#include "images/img_obama.h"

#include "images/ohne.h"
#include "images/strom.h"
#include "images/waer.h"
#include "images/hier.h"
#include "images/garnix.h"
#include "images/los.h"



// This is the key to high framerates!
// it enables the 5 output pins to shift out the data in parallel rather than sequentially
// => 5 times the bandwith!
#define FASTLED_ESP32_I2S 


#include <FastLED.h>

#define LEDS_PER_PIN 225

uint8_t bm[25][45][3];
uint16_t chunks[25][45];
CRGB leds[5*LEDS_PER_PIN];


// matrix max brightness per led
uint8_t brightness = 100;

uint8_t animation = 0;

uint8_t ohne_strom_slide = 0;

long slide_time_counter = 0;






void updateLEDs(){
  uint8_t r,g,b;

  for(int y = 0; y < 25; y++){
    for(int x = 0; x < 45; x++){
      uint16_t led_number = chunks[y][x];

      // you just got integer math'ed
      r = bm[y][x][0] * (brightness / 90.0);
      g = bm[y][x][1] * (brightness / 90.0);
      b = bm[y][x][2] * (brightness / 90.0);

      leds[led_number] = CRGB(r, g, b);
    }
  }
}






void setup() {
  Serial.begin(115200);

  Serial.printf("====================\n===  LED Matrix  ===\n====================\n");
  Serial.printf("     Ohne Strom     \n  waer hier garnix  \n        los        \n");

  // add the parts of the matrix as segments of the leds array
  FastLED.addLeds<WS2812B, 18, EOrder::GRB>(leds, 0 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 19, EOrder::GRB>(leds, 1 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 21, EOrder::GRB>(leds, 2 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 22, EOrder::GRB>(leds, 3 * LEDS_PER_PIN, LEDS_PER_PIN);
  FastLED.addLeds<WS2812B, 23, EOrder::GRB>(leds, 4 * LEDS_PER_PIN, LEDS_PER_PIN);
    

  // basically a lookup table for led numbers with input parameters y and x
  chunking(&chunks[0][0]);

  memcpy(bm, obama_bm, sizeof(bm));


  // start all the ble stack
  bleInitPointers(&bm[0][0][0], &brightness, &animation);
  bleStartAll();

}

void loop() {

  if(animation != 0){

    bool first_loop_for_new_pic = false;

    if(slide_time_counter == 0){
      slide_time_counter = millis();
      first_loop_for_new_pic = true;
    }

    // ohne strom
    if(animation == 1){
      
      if(ohne_strom_slide == 0 && first_loop_for_new_pic){
        memcpy(bm, ohne_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 0 && (millis() - slide_time_counter) > 900){
        ohne_strom_slide = 1;
        slide_time_counter = 0;

        return;
      }



      if(ohne_strom_slide == 1 && first_loop_for_new_pic){
        memcpy(bm, strom_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 1 && (millis() - slide_time_counter) > 800){
        ohne_strom_slide = 2;
        slide_time_counter = 0;
        return;
      }



      if(ohne_strom_slide == 2 && first_loop_for_new_pic){
        memcpy(bm, waer_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 2 && (millis() - slide_time_counter) > 280){
        ohne_strom_slide = 3;
        slide_time_counter = 0;
        return;
      }



      if(ohne_strom_slide == 3 && first_loop_for_new_pic){
        memcpy(bm, hier_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 3 && (millis() - slide_time_counter) > 280){
        ohne_strom_slide = 4;
        slide_time_counter = 0;
        return;
      }




      if(ohne_strom_slide == 4 && first_loop_for_new_pic){
        memcpy(bm, garnix_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 4 && (millis() - slide_time_counter) > 480){
        ohne_strom_slide = 5;
        slide_time_counter = 0;
        return;
      }




      if(ohne_strom_slide == 5 && first_loop_for_new_pic){
        memcpy(bm, los_bm, sizeof(bm));
      }
      if(ohne_strom_slide == 5 && (millis() - slide_time_counter) > 500){
        ohne_strom_slide = 6;
        slide_time_counter = 0;
        return;
      }




      if(ohne_strom_slide == 6 && first_loop_for_new_pic){
        memset(bm, 0, sizeof(bm));
      }
      if(ohne_strom_slide == 6 && (millis() - slide_time_counter) > 400){
        ohne_strom_slide = 0;
        slide_time_counter = 0;
      }
    }


  // FastLED show takes about 7ms
  updateLEDs();
  FastLED.show();

  // together it's about 33ms - about 30fps
  delay(24);

    

    return;
  }

  // FastLED show takes about 7ms
  updateLEDs();
  FastLED.show();

  // together it's about 33ms - about 30fps
  delay(26);
}
