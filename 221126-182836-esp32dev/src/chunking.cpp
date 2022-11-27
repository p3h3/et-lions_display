#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
//
// Created by skip on 18-11-22.
//

#include "constants.h"

void chunking(uint16_t  (*chunks)){
    // declare variables here for performance
    
    for(int y = 0; y < 25; y++){
        int chunky = y / 5;
        for(int x = 0; x < 45; x++){
            int chunkx = x / 5;

            int chunkinterny = y % 5;
            int chunkinternx = x % 5;

            uint16_t led_number = chunky * 25 * 9 + chunkx * 25   +   chunkinterny * 5 + chunkinternx;

            // for debugging xD not needed anymore now that it works but ayo.. what a statement
            //Serial.printf("x: %d, y: %d, chx: %d, chy: %d, cix: %d, ciy: %d, led: %d\n", x,y,chunkx,chunky,chunkinternx,chunkinterny, led_number);


            *(chunks + 45*y + x) = led_number;
        }
    }
}




/*

int main(){
    // just to be sure
    if(WIDTH_PX % WIDTH_CHUNK_PX != 0 || HEIGHT_PX % HEIGHT_CHUNK_PX != 0){
        return 1;
    }

    // filling current bitmap with rainbow stuff
    fill_rainbow();

    // testing output
    uint8_t (*bitmappointer)[45][3] = current_bitmap;
    print_bitmap(bitmappointer);

    printf("\n\n\n");

    uint8_t chunks[(WIDTH_PX/WIDTH_CHUNK_PX)*(HEIGHT_PX/HEIGHT_CHUNK_PX)][HEIGHT_CHUNK_PX][WIDTH_CHUNK_PX][3];

    uint8_t (*chunkspointer)[5][5][3] = chunks;
    chunking(chunkspointer, bitmappointer);

    uint8_t (*chunk0pointer)[5][3] = chunks[2];
    print_chunk(chunk0pointer);

    return 0;
}
*/
