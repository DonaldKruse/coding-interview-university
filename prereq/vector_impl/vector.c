#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int _size;           // the size of the vector
    int _end;            // the size of the allocation for the array
    int* arr;         // the array that stores the values
} vector;


vector* alloc_vector(int size)
{
    vector* vec = malloc(sizeof(vector));
    vec->arr = malloc(size*sizeof(int));
    vec->_end = size;
    vec->_size = 0;  // no push_backs have happend yet
    return vec;
}


void push_back(vector* self, int x)
{
    // null ptr for vector; vector of size zero case
    if (!self)
    {
        self = alloc_vector(1);
        self->arr[0] = x;
        self->_size = 1;
        self->_end = 2;
    } 
    else if (self->_size == self->_end) // end of the vector case
    {
        int* newarr = realloc(self->arr, 2*(self->_size)*sizeof(int));

        // need to check if there was an error with the allocation
        // realloc automatically frees on success
        if (!newarr)
        {
            printf("something went wrong with realloc\n");
            free(self->arr);
            free(self);
            self = NULL;
            exit(-1);
        }
        self->arr = newarr; 
        self->_end = 2*(self->_size);
        self->arr[self->_size] = x;
        self->_size++;
    }
    else // size is less than end
    {
       self->arr[self->_size] = x;
       self->_size++;
    }
}


void vector_free(vector* vec)
{
    printf("in vector_free\n");
    printf("value of vec: %d\n", vec);
    printf("value of vec->arr: %d\n", vec->arr);
    free(vec->arr);
    free(vec);
    vec = NULL;
}

int main()
{
    int N = 10;
    vector* v1 = alloc_vector(N);
    printf("v1 size: %d\n", v1->_size);
    printf("v1 end: %d\n", v1->_end);

    printf("v1 : %d\n", v1);
    printf("v1->arr : %d\n", v1->arr);
    printf("v1->arr[0] = %d\n", v1->arr[0]);
  

    // testing the push_backs
    printf("\n\n\n");
    printf("------------------------\n");
    printf("Testing push_backs\n");
    printf("------------------------\n");
    int i;
    for (i = 0; i < 9; i++)
    {
        printf("i = %d:\n", i);
        printf("-------\n");
        push_back(v1, i);
        printf("    v1->_size = %d\n", v1->_size);
        printf("    v1->_end = %d\n", v1->_end);
        printf("\n");
    }
    
    // print the vector:
    printf("\n");
    printf("v1 = [");
    for (i = 0; i < v1->_size; i++)
    {
        printf("%d ", v1->arr[i]);
    }
    printf("]\n");

    // 3 more push_backs
    for (i = 9; i < 12; i++)
    {
        printf("i = %d:\n", i);
        printf("-------\n");
        push_back(v1, i);
        printf("    v1->_size = %d\n", v1->_size);
        printf("    v1->_end = %d\n", v1->_end);
        printf("\n");
    }
    
    // print the vector:
    printf("\n");
    printf("v1 = [");
    for (i = 0; i < v1->_size; i++)
    {
        printf("%d ", v1->arr[i]);
    }
    printf("]\n");



    vector_free(v1);
    return 0;
}
