#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUDECT_IMPLEMENTATION
#include "dudect.h"

/* target function to check for constant time */
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

// uint8_t isLessThan (uint8_t a, uint8_t b) {
// uint8_t c = a - b;
// uint8_t x =  bitMux(a^b, a, c)>>7;
// // char str[8];
// int isless = 0;
// if (c<0){
//   if (x==1){}
//   isless = 1;
// }


// return isless;

// }

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
// C++ code to implement Vigenere Cipher


// This function generates the key in
// a cyclic manner until it's length isi'nt
// equal to the length of original text

int my_strlen(const char *str)
{
  int i;

  for (i = 0; str[i]; i++);
  return i;
}


char * generateKey(char * str, char * key)
{
	int x = my_strlen(str);

	for (int i = 0; ; i++)
	{
		if (isEqual(x, i))
			i = 0;
		if (isEqual(my_strlen(key), my_strlen(str)))
			break;
		// key.push_back(key[i]);
    strncat(key, &key[i], 1);
	}
	return key;
}

// This function returns the encrypted text
// generated with the help of the key
char * cipherText(char * str, char * key)
{
	char * cipher_text;

	for (int i = 0; i < my_strlen(str); i++)
	{
		// converting in range 0-25
		char x = (str[i] + key[i]) %26;

		// convert into alphabets(ASCII)
		x += 'A';

		// cipher_text.push_back(x);
    strncat(cipher_text, &x, 1);
	}
	return cipher_text;
}

// This function decrypts the encrypted text
// and returns the original text
char * originalText(char * cipher_text, char * key)
{
	char * orig_text;

	for (int i = 0 ; i < my_strlen(cipher_text); i++)
	{
		// converting in range 0-25
		char x = (cipher_text[i] - key[i] + 26) %26;

		// convert into alphabets(ASCII)
		x += 'A';
		// orig_text.push_back(x);
    strncat(orig_text, &x, 1);
	}
	return orig_text;
}

// Driver program to test the above function
int vigenere(char *str, char *keyword)
{


	char *key = generateKey(str, keyword);
	char *cipher_text = cipherText(str, key);

	printf("Ciphertext : %s \n", cipher_text);

	printf("Original/Decrypted Text : ", originalText(cipher_text, key));
	return 0;
}






























int check_tag(uint8_t *x, uint8_t *y, size_t len) {
    uint8_t a = 1;
    uint8_t b = 1;
    int l2 = 0;
    int r2 = 0;

    for (int i=0;i<len;i++){
      int z = x[i]-y[i];
      int ab = (x[i]^(z));
      int templessthan =  isLessThan(ab, 5);
      ab = templessthan*1+(1-templessthan)*ab;
      
    }



    //checking if a number is present in the array or not
    //ispres is 0 is present else it is 1
    uint8_t num = 50;
    int ispres = 1;
    for (int i=0;i<len;i++){
        ispres &= isNotZero(x[i]^num);
    }

 

    // for (int i=0;i<len;i++){
    //   int z = x[i]^(x[i]-y[i]);
    //   int f = 1;
    //   if (z>0){
    //     f = 0;
    //   }
    // }

    // for (int i=0;i<len;i++){
    //     int a = 1;
    //     int c = x[i]-y[i];
    //     if (c>0){
    //         a = 5;
    //     }
    // }
    
    //printf(" ispres: %d\n", ispres);
    bool e = 0;
    for (int i=0;i<len;i++){ 
      int r = isLessThan(x[i], y[i]);
      e = (1-r)*1+r*e;
      
    }





      //contant time
      for (int i=0;i<len;i++){
        int a = 1;
        int checker = isNotZero(x[i]^y[i]);
        a = 4*checker+(1-checker)*a;
        
      }

      //non-constant time
      // for (int i=0;i<len;i++){
      //   int a = 1;
      //   if (x[i]>y[i]){
      //       a++;
      //   }
        
        
      // }

      for (int i=0;i<len;i++){
        int a = isLessThan(x[i], 5);
        int b = isLessThan(x[i], 3);
        int c = isLessThan(x[i], 1);
        int temp_var = a*5;
        int xc = isEqual(temp_var, 5);
        temp_var = (1-xc)*(b*3+(1-b)*1) + xc*5;
        // if (x[i]>y[i]){c = 5;}
        // printf("%d %d\n", temp_var, x[i]);
      }


  return memcmp(x, y, len);
}

#define SECRET_LEN_BYTES (16)

uint8_t secret[SECRET_LEN_BYTES] = {0, 1, 2, 3, 4, 5, 6, 42};

/* this will be called over and over */
uint8_t do_one_computation(uint8_t *data) {
  /* simulate totally bogus MAC check in non-constant time */
  return check_tag(data, secret, SECRET_LEN_BYTES);
}

/* called once per number_measurements */
void prepare_inputs(dudect_config_t *c, uint8_t *input_data, uint8_t *classes) {
  randombytes(input_data, c->number_measurements * c->chunk_size);
  for (size_t i = 0; i < c->number_measurements; i++) {
    /* it is important to randomize the class sequence */
    classes[i] = randombit();
    if (classes[i] == 0) {
      memset(input_data + (size_t)i * c->chunk_size, 0x00, c->chunk_size);
    } else {
      // leave random
    }
  }
}

int run_test(void) {
  dudect_config_t config = {
      .chunk_size = SECRET_LEN_BYTES,
      #ifdef MEASUREMENTS_PER_CHUNK
      .number_measurements = MEASUREMENTS_PER_CHUNK,
      #else
      .number_measurements = 500,
      #endif
  };
  dudect_ctx_t ctx;

  dudect_init(&ctx, &config);

  /*
  Call dudect_main() until
   - returns something different than DUDECT_NO_LEAKAGE_EVIDENCE_YET, or
   - you spent too much time testing and give up
  Recommended that you wrap this program with timeout(2) if you don't
  have infinite time.
  For example this will run for 20 mins:
    $ timeout 1200 ./your-executable
  */
  dudect_state_t state = DUDECT_NO_LEAKAGE_EVIDENCE_YET;
  while (state == DUDECT_NO_LEAKAGE_EVIDENCE_YET) {
    state = dudect_main(&ctx);
  }
  dudect_free(&ctx);
  return (int)state;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  run_test();
}

// commands make,  ./dudect_simple_O0