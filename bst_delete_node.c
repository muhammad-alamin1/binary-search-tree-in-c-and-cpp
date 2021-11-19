#include <stdio.h>

typedef struct node BST_Node;
struct node
{
    int data;
    BST_Node *parent_node;
    BST_Node *left_node;
    BST_Node *right_node;
};

BST_Node *create_bst_node(int item);
void add_left_child(BST_Node *root, BST_Node *child);
void add_right_child(BST_Node *root, BST_Node *child);
BST_Node *bst_insert(BST_Node *root, BST_Node *node);
BST_Node *create_bst_tree(void);
BST_Node *bst_minimum(BST_Node *root);
void in_order(BST_Node *root);
BST_Node *search(BST_Node *root, int item);
BST_Node *bst_transplant(BST_Node *root, BST_Node *current_node, BST_Node *new_node);
BST_Node *bst_delete(BST_Node *root, BST_Node *node);

int main(void)
{
    BST_Node *root, *node;

    root = create_bst_tree();
    printf("Root Data: %d\n", root->data);

    // ascending traversal
    printf("BST: \n");
    in_order(root);
    printf("\n");

    node = search(root, 55);
    if(node != NULL)
    {
        printf("Will delete %d\n", node->data);
        root = bst_delete(root, node);

        printf("BST: \n");
        in_order(root);
        printf("\n");
    }
    else
        printf("Node not found!\n");


    return 0;
}

// create node
BST_Node *create_bst_node(int item)
{
    BST_Node *new_node;

    new_node = (BST_Node *)malloc(sizeof(BST_Node));
    if(new_node == NULL)
    {
        printf("Error! Could not create a bst node.\n");
        exit(1);
    }

    new_node->data = item;
    new_node->parent_node = NULL;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    return new_node;
}

// add child left
void add_left_child(BST_Node *root, BST_Node *child)
{
    root->left_node = child;

    if(child != NULL)
        child->parent_node = root;
}

// add right child
void add_right_child(BST_Node *root, BST_Node *child)
{
    root->right_node = child;

    if(child != NULL)
        child->parent_node = root;
}

// insert
BST_Node *bst_insert(BST_Node *root, BST_Node *node)
{
    BST_Node *parent_node, *current_node;

    if(root == NULL)
    {
        root = node;
        return root;
    }

    parent_node = NULL;
    current_node = root;

    while(current_node != NULL)
    {
        parent_node = current_node;

        if(node->data < current_node->data)
            current_node = current_node->left_node;
        else
            current_node = current_node->right_node;
    }

    if(node->data < parent_node->data)
        add_left_child(parent_node, node);
    else
        add_right_child(parent_node, node);

    return root;
}

// create BST tree
BST_Node *create_bst_tree(void)
{
    BST_Node *root, *node;

    int i;
    int arr[] = {3, 7, 1, 9, 2, 33, 67, 12, 78, 55};
    int n = (sizeof(arr) / sizeof(arr[0]));

    // create root node
    root = create_bst_node(10);

    for(i = 0; i < n; i++)
    {
        node = create_bst_node(arr[i]);
        root = bst_insert(root, node);
    }

    return root;
}

// ascending order (bst minimum)
BST_Node *bst_minimum(BST_Node *root)
{
    BST_Node *node = root;

    while(node != NULL)
    {
        node = node->left_node;
    }

    return node;
}

// in-order
void in_order(BST_Node *root)
{
    if(root->left_node != NULL)
        in_order(root->left_node);

    printf("%d ", root->data);

    if(root->right_node != NULL)
        in_order(root->right_node);
}

// search
BST_Node *search(BST_Node *root, int item)
{
    BST_Node *node = root;

    while(node != NULL)
    {
        if(node->data == item)
            return node;
        if(node->data > item)
            node = node->left_node;
        else
            node = node->right_node;
    }
    return node;
}

// BST transplant
BST_Node *bst_transplant(BST_Node *root, BST_Node *current_node, BST_Node *new_node)
{
    if(current_node == root)
        root = new_node;
    else if(current_node == current_node->parent_node->left_node)
        add_left_child(current_node->parent_node, new_node);
    else
        add_right_child(current_node->parent_node, new_node);

    return root;
}

// BST delete
BST_Node *bst_delete(BST_Node *root, BST_Node *node)
{
    BST_Node *smallest_node;

    if(node->left_node == NULL)
    {
        root = bst_transplant(root, node, node->right_node);
    }
    else if(node->right_node == NULL)
    {
        root = bst_transplant(root, node, node->left_node);
    }
    else
    {
        smallest_node = bst_minimum(node->right_node);

        if(smallest_node->parent_node != node)
        {
            root = bst_transplant(root, smallest_node, smallest_node->right_node);
            add_right_child(smallest_node, node->right_node);
        }
        else
            root = bst_transplant(root, node, smallest_node);
        add_left_child(smallest_node, node->left_node);
    }

    free(node);
    return root;
}
