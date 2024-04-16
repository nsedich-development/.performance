#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>

int main(int argc, char ** argv) {
    printf("WebAssembly module loaded\n");
}

int EMSCRIPTEN_KEEPALIVE roll_dice() {
    srand ( time(NULL) );
    return rand() % 6 + 1;
}

int EMSCRIPTEN_KEEPALIVE iteration_test() {
	float d;
	
	for( float i = 0; i <= 100000000; i++ ) {
      d = i;
    }
   
   return d;
}


int EMSCRIPTEN_KEEPALIVE addNums (float *buf, int bufSize) {

    int total = 0;

    for (int i=0; i<bufSize; i++) {
        total+= buf[i];
    }

    return total;
}