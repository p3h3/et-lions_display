//
// Created by skip on 18-11-22.
//
#include <cmath>
#include "bitmaps.h"


void chunking(uint8_t  (*chunks)[HEIGHT_CHUNK_PX][WIDTH_CHUNK_PX][3], uint8_t  (*bitmap)[WIDTH_PX][3]){
    // declare variables here for performance
    int chunk_x;
    int chunk_y;
    int bitmap_x;
    int bitmap_y;

    for(int chunk = 0; chunk < (WIDTH_PX/WIDTH_CHUNK_PX)*(HEIGHT_PX/HEIGHT_CHUNK_PX); chunk++){
        chunk_x = chunk % WIDTH_CHUNK_PX;
        chunk_y = floor(chunk / HEIGHT_CHUNK_PX);
        for(int x = 0; x < WIDTH_CHUNK_PX; x++){
            for(int y = 0; y < HEIGHT_CHUNK_PX; y++){
                // calculate bitmap pixel positions for the chunk
                bitmap_x = x + (chunk_x*WIDTH_CHUNK_PX);
                bitmap_y = y + (chunk_y*HEIGHT_CHUNK_PX);

                // copy pixel data from bitmap to chunk
                chunks[chunk][y][x][0] = bitmap[bitmap_y][bitmap_x][0];
                chunks[chunk][y][x][1] = bitmap[bitmap_y][bitmap_x][1];
                chunks[chunk][y][x][2] = bitmap[bitmap_y][bitmap_x][2];
            }
        }
    }
}




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