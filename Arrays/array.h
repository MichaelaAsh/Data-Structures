#ifndef ARRAY_H
#define ARRAY_H
#endif

struct Array {
    unsigned int width;  //size in bytes of each element
    unsigned int nel;    //the number of elements currently in the array 
    unsigned int capacity;  // total number of elemts that can be stores in the array
    void *data;           //pointer to the contents of the array
};  //array data structure 

struct Performance {
    unsigned int reads;      //number of reads
    unsigned int writes;     //number of writes 
    unsigned int mallocs;    //number of memory allocations
    unsigned int frees;      //number of free operations 
}; // measure the performance of code 
/////////////////////////////////////////////////////////////////////////////////////
//allocate memory for performance struct 
struct Performance *newPerformance ();  

//allocate memory tp Array structure, set variables, allocate memory for Array -> data, increment performanc malloc
struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity);

void getbytes (unsigned char dest[], int bytes, void *src, int reverse); 

//copies array -> data into dest
void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest);

//copies src into array -> data
void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src);

//descrease array-> nel by 1 (number of elements in array - 1)
void contract (struct Performance *performance, struct Array *array); 

void freeArray (struct Performance *performance, struct Array *array);

// adds src to the end of array->data
void appendItem (struct Performance *performance, struct Array *array, void *src); 

//insert item from src into array-> data at a given index
void insertItem (struct Performance *performance, struct Array *array, unsigned int index, void *src); 

//adds src to the beginning of array -> data
void prependItem (struct Performance *performance, struct Array *array, void* src); 

//deletes element in array -> data. Index specified in parameter 
void deleteItem (struct Performance *performance, struct Array *array, unsigned int index);

//retrieve elements from array using readItem starting from the first element in the array and proceeding incrementally.
int findItem (struct Performance *performance, struct Array *array, int (*compare)(const void *, const void *), void *target); 

//perform binary search for array-> data given a target
int searchItem (struct Performance *performance, struct Array *array, int (*compare)(const void *, const void *_), void *target); 