#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef ET_LIONS_DISPLAY_BITMAPS_H
#define ET_LIONS_DISPLAY_BITMAPS_H

#endif //ET_LIONS_DISPLAY_BITMAPS_H

// already defined in the header
extern uint8_t current_bitmap[25][45][3];

// lookup table for HSV
const uint8_t HSVlights[61] =
        {0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
         81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
         149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
         212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};

void fill_rainbow(){
    for(int y = 0; y < 25; y++){
        for(int x = 0; x < 45; x++){
            if((x+y) % 3 == 0){
                current_bitmap[y][x][0] = 255; // red
                current_bitmap[y][x][1] = 50; // green
                current_bitmap[y][x][2] = 50; // blue
            }
            if((x+y) % 3 == 1){
                current_bitmap[y][x][0] = 50; // red
                current_bitmap[y][x][1] = 255; // green
                current_bitmap[y][x][2] = 50; // blue
            }
            if((x+y) % 3 == 2){
                current_bitmap[y][x][0] = 50; // red
                current_bitmap[y][x][1] = 50; // green
                current_bitmap[y][x][2] = 255; // blue
            }
            if((x+y) % 10 == 0){
                current_bitmap[y][x][0] = 0; // red
                current_bitmap[y][x][1] = 0; // green
                current_bitmap[y][x][2] = 0; // blue
            }
        }
    }
}


void print_bitmap(uint8_t  (*bitmap)[45][3]){
    for(int y = 0; y < 25; y++){
        char line[45*2];
        memset(line, ' ', 45*2); // set line to empty string
        line[(45*2)-1] = '\0';

        for(int x = 0; x < 45; x++){
            uint8_t red = bitmap[y][x][0];
            uint8_t green = bitmap[y][x][1];
            uint8_t blue = bitmap[y][x][2];

            if(red == 255){
                line[x*2] = 'r';
            }
            if(green == 255){
                line[x*2] = 'g';
            }
            if(blue == 255){
                line[x*2] = 'b';
            }
            if(red == 0 && green == 0 && blue == 0){
                line[x*2] = ' ';
            }
        }

        printf("%s\n", line);
    }
}



void print_chunk(uint8_t  (*chunk)[5][3]){
    for(int y = 0; y < 5; y++){
        char line[5*2];
        memset(line, ' ', 5*2); // set line to empty string
        line[(5*2)-1] = '\0';

        for(int x = 0; x < 5; x++){
            uint8_t red = chunk[y][x][0];
            uint8_t green = chunk[y][x][1];
            uint8_t blue = chunk[y][x][2];

            if(red == 255){
                line[x*2] = 'r';
            }
            if(green == 255){
                line[x*2] = 'g';
            }
            if(blue == 255){
                line[x*2] = 'b';
            }
            if(red == 0 && green == 0 && blue == 0){
                line[x*2] = ' ';
            }
        }

        printf("%s\n", line);
    }
}