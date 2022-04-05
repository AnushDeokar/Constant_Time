#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUDECT_IMPLEMENTATION
#include "dudect.h"


uint8_t bitMux(uint8_t c, uint8_t a, uint8_t b) {
  uint8_t p = a^b;
  uint8_t q = c&p;
  uint8_t z =  b ^ q;
  return z;
}
uint8_t isLessThan (uint8_t a, uint8_t b) {
  uint8_t c = a - b;
  uint8_t r = bitMux(a^b, a, c) >> 7;
  return r;
}

uint8_t isGreaterThan (uint8_t a, uint8_t b) {
return isLessThan (b, a);
}
uint8_t isLessThanOrEqual (uint8_t a, uint8_t b) {
return !( isGreaterThan (a, b));
}
uint8_t isGreaterThanOrEqual (uint8_t a, uint8_t b) {
return !( isLessThan (a, b));
}

uint8_t get_max(uint8_t *x, int len){
  uint8_t maxi = INT8_MIN;
  for (int i=0;i<len;i++){
    int eq = isGreaterThan(x[i], maxi);
    maxi = x[i]*eq + maxi*(1-eq);
  }
  return maxi;
}


uint8_t get_min(uint8_t *x, int len){
  uint8_t mini = INT8_MAX;
  for (int i=0;i<len;i++){
    int eq = isLessThan(x[i], mini);
    mini = x[i]*eq + mini*(1-eq);
  }
  return mini;
}

uint8_t issanitized(char *str, int len){
  uint8_t valid = 1;
  for (int i=0;i<len;i++){
    valid = valid&&isEqual(str[i], '\'');
    valid = valid&&isEqual(str[i], '\"');
  }
  return valid;
}

uint8_t isNotZero (uint8_t b) {
  return (b | -b) >> 7;
}

void swap(uint8_t *xp, uint8_t *yp)
{
    uint8_t  temp = *xp;
    *xp = *yp;
    *yp = temp;
}

uint8_t isNotEqual (uint8_t a, uint8_t b) {
  return isNotZero (a ^ b);
}


uint8_t arraycheck(uint8_t *x, uint8_t *y, int len){
    //comparing two arrays
    int eq = 1;
    for (int i=0;i<len;i++){
      eq &= ~(x[i] ^ y[i]);
    }
    return eq;
}

uint8_t isEqual(uint8_t a, uint8_t b) {
  return ~( isNotEqual (a, b));
}


void bubble_sort(uint8_t *x, int len){
     //bubbleSort implementation
     for (int i = 0; i < len-1; i++){  
 
       // Last i elements are already in place  
       for (int j = 0;isLessThan(j, len-i-1); j++){
            int temp  = isGreaterThan(x[j], x[j+1]);
            uint8_t b =(x[j+1]*temp+(1-temp)*x[j]);
            swap(&x[j], &b);
           
        }
      }
}