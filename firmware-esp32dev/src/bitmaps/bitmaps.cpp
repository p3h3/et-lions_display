#include <Arduino.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"


uint8_t current_bitmap[25][45][3];

uint8_t * current_bitmap_pointer(){
    return &current_bitmap[0][0][0];
}


void fill_rainbow(uint8_t  (*bitmap)){
    for(int y = 0; y < 25; y++){
        for(int x = 0; x < 45; x++){
            if((x+y) % 3 == 0){
                *(bitmap + 3*x + 45*3*y + 0) = 10; // red
                *(bitmap + 3*x + 45*3*y + 1) = 0; // green
                *(bitmap + 3*x + 45*3*y + 2) = 0; // blue
            }
            if((x+y) % 3 == 1){
                *(bitmap + 3*x + 45*3*y + 0) = 0; // red
                *(bitmap + 3*x + 45*3*y + 1) = 10; // green
                *(bitmap + 3*x + 45*3*y + 2) = 0; // blue
            }
            if((x+y) % 3 == 2){
                *(bitmap + 3*x + 45*3*y + 0) = 0; // red
                *(bitmap + 3*x + 45*3*y + 1) = 0; // green
                *(bitmap + 3*x + 45*3*y + 2) = 10; // blue
            }
            if((x+y) % 10 == 0){
                *(bitmap + 3*x + 45*3*y + 0) = 0; // red
                *(bitmap + 3*x + 45*3*y + 1) = 0; // green
                *(bitmap + 3*x + 45*3*y + 2) = 0; // blue
            }
        }
    }
}


void print_bitmap(uint8_t  (*bitmap)){

    for(int y = 0; y < 25; y++){
        char line[45*2];
        memset(line, ' ', 45*2); // set line to empty string
        line[(45*2)-1] = '\0';

        for(int x = 0; x < 45; x++){
            uint8_t red = *(bitmap + 3*x + 45*3*y);
            uint8_t green = *(bitmap + 3*x + 45*3*y + 1);
            uint8_t blue = *(bitmap + 3*x + 45*3*y + 2);

            if(red == 25){
                line[x*2] = 'r';
            }
            if(green == 25){
                line[x*2] = 'g';
            }
            if(blue == 25){
                line[x*2] = 'b';
            }
            if(red == 0 && green == 0 && blue == 0){
                line[x*2] = 'n';
            }
        }

        Serial.printf("%s\n", line);
    }
}