#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int val;
     struct Node* left;
     struct Node* right;
};
typedef struct Node Node;


Node* create_node(int val)
{
     Node* node = malloc(sizeof(Node));
     node->val = val;
     node->left = NULL;
     node->right = NULL;
     return node;
}

void insert(Node** root_ref, int data)
{
     Node* root = *(root_ref);
     if (!root)
     {
	  root = create_node(data);
     }
     
int main ()
{
     Node* root = NULL;
     
