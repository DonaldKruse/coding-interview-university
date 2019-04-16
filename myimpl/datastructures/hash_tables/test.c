#include <stdio.h>
#include <stdlib.h>

struct node {
    char* key;
    int val;
    struct node* next;
};

struct node* create_node(const char* key, const int val)
{
    struct node* nd = malloc(sizeof(struct node));
    nd->key = key;
    nd->val = val;
    nd->next = NULL;
    return nd;
}

struct table {
    int size;
    struct node** nodearray;
};

void delete_node(struct node* nd)
{
    free(nd);
}


void delete_list(struct node* head)
{
    struct node* tmp = NULL;
    while (head)
    {
       tmp = head;
       head = head->next;
       delete_node(tmp);
    }
    head = NULL;
}

void delete_table(struct table* tb)
{
    int i;
    for (i = 0; i < tb->size; i++)
    {
        delete_list(tb->nodearray[i]);
    }
    free(tb->nodearray);
    free(tb);
    tb = NULL;
}


int main()
{
    int SIZE = 10;
    struct table* tb = malloc(sizeof(struct table));
    printf("sizeof(table) = %d\n", sizeof(struct table));
    tb->size = SIZE;
    //tb->nodearray = malloc(SIZE*sizeof(struct node*));
    tb->nodearray = calloc(SIZE, sizeof(struct node*));
    printf("sizeof(node*) = %d\n", sizeof(struct node*));
    printf("sizeof(node) = %d\n", sizeof(struct node));
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("tb->nodearray[%d] = %d\n", i, tb->nodearray[i]);
    }
    const char* key = "test";
    for (i = 0; i < SIZE; i++)
    {
        tb->nodearray[i] = create_node(key, i);
    }
    for (i = 0; i < SIZE; i++)
    {
        printf("arr[%d] = %d\n", i, tb->nodearray[i]);
    }
    printf("\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%s    %d    %d\n", tb->nodearray[i]->key, tb->nodearray[i]->val, tb->nodearray[i]->next);
    }
    delete_table(tb);

    return 0;
}
