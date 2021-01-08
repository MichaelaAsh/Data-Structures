#define FALSE 0 
#include <string.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////
void getbytes (unsigned char dest[], int bytes, void *src, int reverse); 
////////////////////////////////////////////////////////////////////////////
// Retrive individual bits from a computer memory and represent their value
//as the char "0" and "1' and store them in string dest  
void getbits (char dest[], int bytes, void *src, int start, int end); 
//////////////////////////////////////////////////////////////////////////////
//read chracters from string bits and process up to, but not including
//the terminating null character
unsigned long long bits2ull (char *bits);
//////////////////////////////////////////////////////////////////////////////
//reads  in char 1's or 0's that is 2's compliment number and convert value
//to long long 
long long bits2ll (char *bits );
//////////////////////////////////////////////////////////////////////////////
void *spff(char *sign, char *exponent, char *significand, float *src); 	
////////////////////////////////////////////////////////////////////////////
void *dpff(char *sign, char *exponent, char *significand, double *src); 