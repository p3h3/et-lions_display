#include <stdint.h>
#include <stdio.h>
#include <string.h>

//
// Created by skip on 21-11-22.
//

#ifndef ET_LIONS_DISPLAY_BITMAPS_H
#define ET_LIONS_DISPLAY_BITMAPS_H


// bitmap and chunk stuff
#define WIDTH_CHUNK_PX 5
#define HEIGHT_CHUNK_PX 5

#define WIDTH_PX 45
#define HEIGHT_PX 25


#endif //ET_LIONS_DISPLAY_BITMAPS_H


uint8_t current_bitmap[25][45][3];

void fill_rainbow();

void print_bitmap(uint8_t  (*bitmap)[45][3]);
void print_chunk(uint8_t  (*chunk)[5][3]);