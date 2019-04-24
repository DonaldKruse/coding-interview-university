#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int data;
     struct Node* left;
     struct Node* right;
};
typedef struct Node Node;


Node* create_node(int val)
{
     Node* node = malloc(sizeof(Node));
     node->data = val;
     node->left = NULL;
     node->right = NULL;
     return node;
}

Node* insert(Node* root, int data)
{
     if (!root)
	  return create_node(data);
     if (data <= root->data)
	  root->left = insert(root->left, data);
     else
	  root->right = insert(root->right, data);
     return root;
}

int bst_min(Node* root)
{
     if(!root)
     {
	  printf("null root: no minimum\n");
	  return -1;
     }
     
     Node* current = root;
     while (current->left)
	  current = current->left;

     return current->data;
}


int bst_max(Node* root)
{
     if(!root)
     {
	  printf("null root: no minimum\n");
	  return -1;
     }
     
     Node* current = root;
     while (current->right)
	  current = current->right;

     return current->data;
}


int main ()
{
     Node* root = NULL;
     root = insert(root, 10);
     root = insert(root, 5);
     root = insert(root, 8);
     root = insert(root, 2);
     root = insert(root, 20);

     printf("min = %d\n", bst_min(root));
     printf("max = %d\n", bst_max(root));
     return 0;
}
