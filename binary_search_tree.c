#include <stdio.h>

typedef struct node BINARY_SEARCH_TREE;
struct node
{
    int data;
    BINARY_SEARCH_TREE *parent;
    BINARY_SEARCH_TREE *left_node;
    BINARY_SEARCH_TREE *right_node;
};

BINARY_SEARCH_TREE *create_binary_search_tree_node(int item);
void add_left_child(BINARY_SEARCH_TREE *root, BINARY_SEARCH_TREE *child);
void add_right_child(BINARY_SEARCH_TREE *root, BINARY_SEARCH_TREE *child);

int main()
{

    return 0;
}

// Create BST Node
BINARY_SEARCH_TREE *create_binary_search_tree_node(int item)
{
    BINARY_SEARCH_TREE *new_node;

    new_node = (BINARY_SEARCH_TREE *)malloc(sizeof(BINARY_SEARCH_TREE));
    if(new_node == NULL)
    {
        printf("Error! Could not create a new BST Node.\n");
        exit(1);
    }

    new_node->data = item;
    new_node->parent = NULL;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    return new_node;
}

// add node left
void add_left_child(BINARY_SEARCH_TREE *root, BINARY_SEARCH_TREE *child)
{
    root->left_node = child;

    if(child != NULL)
        child->parent = root;
}

// add node right
void add_right_child(BINARY_SEARCH_TREE *root, BINARY_SEARCH_TREE *child)
{
    root->right_node = child;

    if(child != NULL)
        child->parent = root;
}
