#include <stdio.h>
//#include "bandb.h" 
#include <string.h>
#include <stdlib.h>
#define FALSE 0 

/////////////////////////////////////////////////////////////////////////
void getbytes (unsigned char dest[], int bytes, void *src, int reverse) {
	if (reverse == FALSE){      
		 memcpy(dest, src, bytes);  
		 dest[bytes] = '\0';
		
	} else  {
		unsigned char *string = src;
		int start = bytes;
		int i; 
		int j = 0; 

		for(i = start - 1; i >= 0; i--) {
			dest[j] = string[i]; 
		//copies from the max index based on bytes into the first
		//index of reverse. i decreases and  j increases
			j++; 
	        }  
		dest[start] = '\0';
	}

}//end of void getbytes 
////////////////////////////////////////////////////////////////////////////
// Retrive individual bits from a computer memory and represent their value
//as the char "0" and "1' and store them in string dest  
void getbits (char dest[], int bytes, void *src, int start, int end) {
	unsigned char *num_src = src;
	//start  is the location of the ffirst vut to be added to string(de?
	//last bit to be added is end + 1 
	int s = start; 
	int quotient;
	int remainder;  
	int i = 0;
	int j = 0;
	while (start > end) {
		quotient = start/8;
		remainder = start%8;
		i = bytes - quotient - 1;
		if ( (num_src[i] >>  remainder) & 1){//looks if bit it a 1 
			dest[j] = '1'; //if 1 store 1 in dest
			j++; 
		} else {
			dest[j] = '0'; //else it's  0 and store 0 in dest
			j++;  
		} 
		start--; 
	}  
	dest[s - end] = '\0';//null terminate  at index = start - end 
	
} //end of getbits  
//////////////////////////////////////////////////////////////////////////////
//read chracters from string bits and process up to, but not including
//the terminating null character
unsigned long long bits2ull (char *bits) { 
        unsigned long long converted_value = 0;//will hold converted binary numbers 
        unsigned long long length = strlen (bits); 
        unsigned long long   shift  = length - 1; //binary lsb is 2^0
        int position = 0;//track the index position in bits
       //will go each index from 0 to length and  check if there is a 1 
       for (position = 0; position < length; position++) {
                if (bits [position] == '1') {  // if there is a '1' shift left by 1 by 2^shift
                        converted_value += (unsigned long long)1ULL << shift;//adds 2^shift
			/*casted  to handle a number larger than 32 bits*/ 
                }
                shift --;
        }

        return converted_value; 
}// end of bit2ull
//reads  in char 1's or 0's that is 2's compliment number and convert value
//to long long 
long long bits2ll (char *bits ) { 

	long long converted_value = 0;//will hold the binary converted value  
	long long length = strlen (bits); 
	long long   shift  = length - 1;//will use to bitwise left shift to 2^shift
	//shift is length bmak/c 2^0
	int position = 0; //will keep track of position in bit index 
	if (bits[position] == '1') { //if msb is 1
		converted_value += (unsigned long long)1ULL << shift;// adds 2^shift 
	 	converted_value *= -1; //first bit is negative in 2's compl...
	} shift --; 
	for (position = 1; position < length; position++) {
		if (bits [position] == '1') { 
			converted_value += (unsigned long long)1ULL << shift;// adds 2^shift
			/*casted  to handle a number larger than 32 bits*/ 
		}
		shift --;
	}
	
	return converted_value; 
}// end of bits2ll
//////////////////////////////////////////////////////////////
#include <math.h>
void *spff(char *sign, char *exponent, char *significand, float *src) { 	
	char binary_num[32];//will hold the floating point value
	unsigned char bytes[4]; 
    
	getbytes (bytes, sizeof(float), src, 1); 
	getbits(binary_num,sizeof(float), bytes, 31, -1);
    
	int i = 0;
	int k = 0;
	int j = 0; 
	sign[0] = binary_num[0]; //first bit is sign bit 
	for (i = 1; i <= 8; i++) { //next 8 bit are exponent
		exponent[k] = binary_num[i];
		k++;
	} 
	for (i = 9; i<= 32; i++) { //next 23 is mantissa
		significand[j] = binary_num[i];
		j++;
	}
    return 0; 
}
////////////////////////////////////////////////////////////////////////////
void *dpff(char *sign, char *exponent, char *significand, double *src) { 	
	char binary_num[64];//will hold the floating point value
	unsigned char bytes[8]; 

	getbytes (bytes, sizeof(double), src, 1); 
	getbits(binary_num,sizeof(double), bytes, 63, -1);//64bits
    
	int i = sizeof(double);
	int k = sizeof(double);

	sign[0] = binary_num[0]; //first bit is sign bits
	getbytes (bytes, i, src, 1); 
	getbits(exponent,i, bytes, 62, 51);//11 bits 
	 
	getbytes (bytes, k, src, 1); 
	getbits(significand,k, bytes, 51, -1); //52 bits
 

    return 0; 
} //end of dpff
