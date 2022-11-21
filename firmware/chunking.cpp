//
// Created by skip on 18-11-22.
//

#include "chunking.h"

#define WIDTH_CHUNK_PX 5
#define HEIGHT_CHUNK_PX 5

#define WIDTH_PX 45
#define HEIGHT_PX 25

int main(){
    // just to be sure
    if(WIDTH_PX % WIDTH_CHUNK_PX != 0 || HEIGHT_PX % HEIGHT_CHUNK_PX != 0){
        return 1;
    }



    return 0;
}