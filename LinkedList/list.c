#include "list.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define TRUE 1
#define FALSE 0

//allocate memory for a performance structure 
struct Performance *newPerformance () {
    struct Performance *new = malloc(sizeof(struct Performance)); //allocate memory  
    if (new == NULL) {
         // if malloc fails print error message to std error and exit 
        fprintf(stderr, "Error: malloc failed\n"); 
        exit(-1); 
    }
    new -> reads = 0; 
    new -> writes = 0; 
    new -> mallocs = 0; 
    new -> frees = 0; 

    return new; 
}// end of *newPerformance 

//////////////////////////////////////////////////////////////////////////////////////////////////////
//this functions adds an element to the beginning (head) of the list 
void push ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width) {

    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node)); 
    if (new_node == NULL) {
         // if malloc fails print error message to std error and exit 
        fprintf(stderr, "Error: malloc failed\n"); 
        exit(-1); 
    }

    new_node -> data = malloc (width); 
    
    memcpy((unsigned char* )(new_node-> data), src, width); //copie src into new_node -> data

   new_node -> next =  *list_ptr; 
   *list_ptr = new_node; 

   performance -> mallocs += 1; 
   performance -> writes += 1; 


} // end of push 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//check if the list is empty 
int isEmpty (struct Performance *performance, struct Node **list_ptr) {
    
    if ((*list_ptr) == NULL) {
        return  TRUE;  
    }
    return FALSE; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void readHead ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width) {

     if (isEmpty(performance, list_ptr) == TRUE ) {
         fprintf(stderr, "Error: List is empty\n");
         exit (-1); // if the list is empty print to stderr ad exits
     }
     //copy data from the head into dest
     memcpy(  dest, (*list_ptr) -> data, width);

     performance -> reads += 1; //increment reads by 1
} //end of readHead

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//remove an item from the head of list
void pop ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {

    if (isEmpty(performance, list_ptr) == TRUE ) {
        fprintf(stderr, "Error: List is empty\n");
        exit(-1);  // if the list is empty print to stderr and exits
    }
    memcpy( dest, (*list_ptr)-> data, width); //copy width bytes from data to dest

    struct Node *temp =  *list_ptr;  // make temp current list_ptr
    *list_ptr = (*list_ptr) -> next; //make list_ptr equal to next struct it's pointing to
                                              
     free(temp ->data); //free 
     free(temp); 

     performance-> reads += 1; //increment reads by 1
     performance -> frees += 1; //increment fress by 1 
    
  

} //end of pop 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//return pointer to the pointer to the second item in the list
struct Node **next (struct Performance *performance, struct Node **list_ptr) {

    if (isEmpty(performance, list_ptr) == TRUE ) {
        fprintf(stderr, "Error: List is empty\n");
        exit(-1); // if the list is empty print to stderr and exits
    }
    performance -> reads += 1; //increment reads by 1

    return &((*list_ptr) -> next);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//pop item of the list until list isEmpty 
void freeList (struct Performance *performance, struct Node **list_ptr) {
    
   // unsigned width; 
    while (isEmpty(performance, list_ptr) == FALSE ) { // while list isn't empty, iterate through thr list and free the head of the list
        unsigned char * dest = (*list_ptr) -> data; 
        pop (performance, list_ptr, dest, sizeof( (*list_ptr) -> data) ); //free head
    }
}// end of freeList 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//will use next and readItem to find Node i (where i = 0 for the first node in the list), to retrieve 
//data from the given position in the list
void readItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index,  void *dest, unsigned int width ) {
  
    if (index == 0) {
        readHead (performance, list_ptr, dest, width);  
   } else {
        int i = 0; 
        for (i = 0; i < index; i ++) {
             list_ptr = next (performance, list_ptr);
        }
       readHead (performance, list_ptr, dest, width); 
   }
} // end of readItem 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//adds an element to the end of the list
void appendItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ) {
    

    if (isEmpty(performance, list_ptr) == TRUE) {
         push (performance, list_ptr, src, width);
    } else {
        while (isEmpty(performance, list_ptr) == FALSE) {
                list_ptr = next (performance, list_ptr);
        }
        push (performance, list_ptr, src, width);
    }

     
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//insert element in the list 
void insertItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index ,void *src, unsigned int width ) {

    if (index == 0) { //start of the list 
        push (performance, list_ptr, src, width); 
    } else {
        
        int i = 0; 
        for (i = 0; i < index; i++) {
            list_ptr = next (performance, list_ptr); 
        
        }
        push (performance, list_ptr, src, width); 
        
    }
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//adds an element at the beginning of the list
void prependItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ) {
    insertItem (performance, list_ptr, 0 ,src, width ); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//delete an element from the list 
void deleteItem (struct Performance *performance, struct Node **list_ptr, unsigned int index ) {

    
    if (isEmpty(performance, list_ptr) == FALSE) { 
        int i = 0;
        for (i = 0; i < index; i++) {
            list_ptr = next (performance, list_ptr);
        }
       /* unsigned char *dest = malloc( sizeof( (*list_ptr)->data) ); 
        dest */
        pop (performance, list_ptr, (*list_ptr)->data, sizeof( (*list_ptr)->data) ); 
    } 
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//retrieve elements from list using readItem starting from the first element in the list and proceeding incrementally.
 int findItem (struct Performance *performance, struct Node **list_ptr, int(*compar)(const void *, const void *), void *target, unsigned width) {

    int i = 0; 
    unsigned char *dest = malloc( width);
    unsigned int match = -1;//if the function process the entire list without finding a match it should return -1;

    while (isEmpty(performance,list_ptr) == FALSE) {
        readHead (performance, list_ptr, dest, width); 
        if (compar (dest,target) == 0) { 
            match = i; 
            free  (dest); 
            return match; //if the compare function return 0(match) thus function should return the index of the matching element. 
        } //if the compare function a non -zero (not match) it should proceed with the next element.
         list_ptr = next (performance, list_ptr); 
         i++; 
    }
    free  (dest); 
    return match; //not a match 
}//end of findItem 
