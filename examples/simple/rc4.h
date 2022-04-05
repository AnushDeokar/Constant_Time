#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>  
#include<string.h>
#include <stdint.h>
#define KEY_LENGTH 16
#define ITERATIONS 256*256


uint64_t bitMux(uint64_t c, uint64_t a, uint64_t b) {
return b ^ (c & (a ^ b));
}
uint64_t isLessThan (int64_t a, int64_t b) {
uint64_t c = a - b;
return bitMux(a^b, a, c) >> 63;
}
uint64_t isGreaterThan (int64_t a, int64_t b) {
return isLessThan (b, a);
}
uint64_t isLessThanOrEqual (int64_t a, int64_t b) {
return !( isGreaterThan (a, b));
}
uint64_t isGreaterThanOrEqual (int64_t a, int64_t b) {
return !( isLessThan (a, b));
}




void ksa(int state[], int key[]) {
    int i,j=0,t; 
    for (i=0; isLessThan(i, 256); ++i)
        state[i] = i; 
    for (i=0; isLessThan(i, 256); ++i) {
        j = (j + state[i] + key[i % KEY_LENGTH]) % 256; 
        t = state[i]; 
        state[i] = state[j]; 
        state[j] = t; 
    }
}

void prga(int state[], int out[]) {  
    int i=0,j=0,x,t; 
    int key; 
    for (x=0; isLessThan(x, 256); ++x) {
        i = (i + 1) % 256; 
        j = (j + state[i]) % 256; 
        t = state[i];
        state[i] = state[j];
        state[j] = t;
        out[x] = state[(state[i] + state[j]) % 256];
    }
}

void makeRandomKey(int key[]) {
    int i;
    for (i=0; isLessThan(i, KEY_LENGTH); ++i) 
        key[i] = rand() % 256;
} 

int rc4(int argc, char *argv[]) {


    int state[256];
    int out[256];
    int key[KEY_LENGTH];
    int occurances[256][256];
    int i,j,bytePosition,charOccurance;

    for (i=0; isLessThan(i, 256); ++i) 
        for (j=0; isLessThan(j, 256); ++j)
            occurances[i][j] = 0;

   
    for (i=0; isLessThan(i, ITERATIONS); ++i) {
        makeRandomKey(key);
        ksa(state, key);
        prga(state, out);

        for (j=0; isLessThan(j, 256); ++j)
            ++occurances[j][out[j]];
    }

    // for (bytePosition=0; bytePosition<256; ++bytePosition) {
    //     printf("%d,", bytePosition);
    // }
    // printf("\n");
    // for (charOccurance=0; charOccurance<256; ++charOccurance) {
    //     for (bytePosition=0; bytePosition<256; ++bytePosition) {
    //         printf("%d,", occurances[charOccurance][bytePosition]);
    //     }
    //     printf("\n");
    // }
    printf("final: %d\n", occurances[1][0]);



    return 0;
}