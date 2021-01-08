//Structure for the list 
struct Node {
    void *data; 
    struct Node *next; 
}; 

typedef struct Node Node;  //creates a new name to use for the struct Node

struct Performance {
    unsigned int reads; 
    unsigned int writes; 
    unsigned int mallocs; 
    unsigned int frees; 
}; 

//allocate memory for a performance structure 
struct Performance *newPerformance (); 

//this functions adds an element to the beginning (head) of the list 
void push ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width); 

//check if the list is empty 
int isEmpty (struct Performance *performance, struct Node **list_ptr); 

void readHead ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width); 

//remove an item from the head of list
void pop ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ); 

//return pointer to the pointer to the second item in the list
struct Node **next (struct Performance *performance, struct Node **list_ptr); 

//pop item of the list until list isEmpty 
void freeList (struct Performance *performance, struct Node **list_ptr); 

//will use next and readItem to find Node i (where i = 0 for the first node in the list), to retrieve 
//data from the given position in the list
void readItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index,  void *dest, unsigned int width ); 

//adds an element to the end of the list
void appendItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ); 

//insert element in the list 
void insertItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index ,void *src, unsigned int width ); 

//adds an element at the beginning of the list
void prependItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ); 

void deleteItem (struct Performance *performance, struct Node **list_ptr, unsigned int index ); 

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//retrieve elements from list using readItem starting from the first element in the list and proceeding incrementally.
 int findItem (struct Performance *performance, struct Node **list_ptr, int(*compar)(const void *, const void *), void *target, unsigned width); 