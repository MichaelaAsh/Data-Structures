#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "array.h"
#define FALSE  0

//allocate memory for a performance structure 
struct Performance *newPerformance () {
    struct Performance *new = malloc(sizeof(struct Performance)); //allocate memory  
    if (new == NULL) {
         // if malloc fails print error message to std error and exit 
        fprintf(stderr, "Error: malloc failed"); 
        exit(-1); 
    }
    new -> reads = 0; 
    new -> writes = 0; 
    new -> mallocs = 0; 
    new -> frees = 0; 

    return new; 
}// end of *newPerformance 
///////////////////////////////////////////////////////////////////////////////////
//allocate memory tp Array structure, set variables, allocate memory for Array -> data, increment performanc malloc
struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity) {
    struct Array *new = malloc(sizeof(struct Array)); //allocate memory 
    if (new == NULL) {
         // if malloc fails print error message to std error and exit 
        fprintf(stderr, "Error: malloc failed\n"); 
        exit(-1); 
    }
  
    new -> width = width; 
    new -> capacity = capacity; 
    new  -> nel = 0; 
    performance -> mallocs = (performance -> mallocs) + 1; //increment malloc 
    new -> data =  malloc (width*capacity); //allocate memory in data 
    return new;
}//end of *newArray
////////////////////////////////////////////////////////////////////////////////////
//copies array -> data into dest
void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest) {
    if (index >= (array -> nel)) {
        //print an error message to standard error stream and exit 
        fprintf(stderr, "Error: index is greater than 0 or index == number of elements in array\n "); 
        exit(-1); 
    }    
    index = (array -> width ) * index; 
    unsigned int bytes = array -> width; 
    memcpy (dest,(unsigned char*)(array -> data) + index, bytes);

    performance -> reads = (performance -> reads) + 1 ; //increment reads

}//end of readItem
/////////////////////////////////////////////////////////////////////////////////////
//copies src into array -> data
void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src) {

    if (index > (array -> nel) || index >= (array -> capacity) ) {
        //print an error message to standard error stream and exit 
        fprintf(stderr, "Error: index is greater than  number elements currently in the array or index is equal to or greater than capacity of array\n"); 
        exit(-1); 
    }
     
    if (index == (array -> nel)) {
        array -> nel += 1;
    }
   
    index = (array->width) * index;
    unsigned int bytes = array -> width; 
    memcpy((unsigned char* )(array -> data) + index, src, bytes);

    performance -> writes = (performance -> writes) + 1;  //increment 1

}// end of writeItem
//////////////////////////////////////////////////////////////////////////////////////
//descrease array-> nel by 1 (number of elements in array - 1)
void contract (struct Performance *performance, struct Array *array) {
    if ((array -> nel) == 0 ) {
        //print an error message to standard error stream and exit 
        fprintf(stderr, "Error: number of element in array is currently 0\n"); 
        exit(-1);  
    } else {
        array -> nel -= 1; //decrement the number of elements in array;
    }

}
//////////////////////////////////////////////////////////////////////////////////////
void freeArray (struct Performance *performance, struct Array *array) {
    
    free(array -> data);   //free each element in array
    free (array);  //free array structure 
    performance -> frees = (performance -> frees) + 1; 
}
///////////////////////////////////////////////////////////////////////////////////////
// adds src to the end of array->data
void appendItem (struct Performance *performance, struct Array *array, void *src) {
       writeItem (performance, array, array -> nel, src); 
}
///////////////////////////////////////////////////////////////////////////////////////
//insert item from src into array-> data at a given index
void insertItem (struct Performance *performance, struct Array *array, unsigned int index, void *src) {
    
    unsigned int i; 
    unsigned int j = array -> nel; // number of elements in the array
    unsigned int nel = array -> nel; // number of elemts in the array 
    unsigned char *dest = malloc(array->width); 
    unsigned char *source; 

    for (i = nel; i > index; i--) {  //starting from the end of the array and decrementing 
         j  = j - 1;  //decrementing 
        readItem (performance, array, j,  dest); //reads index before 
        source = dest;  
        writeItem (performance, array, i,source); //write to the next  
    }
        writeItem (performance, array, index,src); //write item from src into array 

    free(dest); 

}
//////////////////////////////////////////////////////////////////////////////////////
//adds src to the beginning of array -> data
void prependItem (struct Performance *performance, struct Array *array, void* src) {
    insertItem (performance, array, 0, src); //insert item at position 0 (start of the array)
}

//////////////////////////////////////////////////////////////////////////////////////////
//deletes element in array -> data. Index specified in parameter 
void deleteItem (struct Performance *performance, struct Array *array, unsigned int index) {

   //move each item in array by 1 
    unsigned int i; 
    unsigned int j = index; //item your deleting 
    unsigned int nel = array -> nel;//number of elements in the array 
    unsigned char *dest = malloc(array->width); 
    unsigned char *src; 

    for (i = index; i < nel -1; i++) {  // starting from the given index value and adding 
         j  = j + 1;  
        readItem (performance, array, j,  dest);   //read item of the next
        src = dest;
        writeItem (performance, array, i, src);   //storing each item 1 less it's original position
    }

    free(dest); 
    contract (performance, array); //array-> nel -1; b/c 1 less element in the array 
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////
int findItem (struct Performance *performance, struct Array *array, int (*compare)(const void *, const void *), void *target){
//retrieve elements from array using readItem starting from the first element in the array and proceeding incrementally.

    int i = 0; 
    unsigned char *dest = malloc(array->width);
    unsigned int match = -1;//if the function process the entire array without finding a match it should return -1;

    for (i = 0; i < array -> nel; i++) {  // reads through array->data and stores in dest after each iteration
        readItem (performance, array, i,  dest); 
        if (compare (dest,target) == 0) { 
            match = i; 
            free  (dest); 
            return match; //if the compare function return 0(match) thus function should return the index of the matching element. 
        } //if the compare function a non -zero (not match) it should proceed with the next element.
    }//end of loop

    free  (dest); 
    return match; //not a match 
}//end of findItem 
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int searchItem (struct Performance *performance, struct Array *array, int (*compare)(const void *, const void *_), void *target) {
    //perform binary search for array-> data given a target
    //from zybooks 
    unsigned int mid = 0; 
    unsigned int low = 0; 
    unsigned int high = (array -> nel) - 1; 
    unsigned char *dest = malloc(array->width);

    while (high >= low) {
        mid = (high + low)/2;  //retrieve elements from readItem starting from the middle element of the array rounded down
        readItem (performance, array, mid,  dest);

        if (compare(dest, target) < 0) { //if the compare function retrieves less than 0. it should repeat search on all higher indexed elements 
            low = mid + 1; 
        } else  if (compare(dest, target) > 0) {  //if the compare function return a value greater =than zero, it should repeat search on lower indexed elements
            high = mid - 1; 
        } else if (compare(dest, target) == 0){
            free  (dest); 
            return mid; //return index 
        }

    }
    free(dest); 
    return -1; //not found 
}//end of search