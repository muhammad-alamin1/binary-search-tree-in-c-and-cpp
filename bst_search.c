#include <stdio.h>

typedef struct node Node;
struct node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
};

Node *bst_search(Node *root, int item);
Node *create_bst_node(int item);
void add_left_child(Node *root, Node *child);
void add_right_child(Node *root, Node *child);
Node *bst_insert(Node *root, Node *node);
Node *create_binary_search_tree(void);
void post_order(Node *root);

int main(void)
{
    Node *root, *node;

    root = create_binary_search_tree();
    printf("Root data: %d\n", root->data);

    post_order(root);

    node = bst_search(root, 5);
    if(node != NULL)
        printf("\n\n%d Node found.\n", node->data);
    else
        printf("\n\nNode not found.\n");

    node = bst_search(root, 55);
    if(node != NULL)
        printf("\n\n%d Node found.\n", node->data);
    else
        printf("\n\nNode not found.\n");

    return 0;
}

// create BST node
Node *create_bst_node(int item)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if(new_node == NULL)
    {
        printf("Error! Could not create a new node.\n");
        exit(1);
    }

    new_node->data = item;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// add child left
void add_left_child(Node *root, Node *child)
{
    root->left = child;

    if(child != NULL)
        child->parent = root;
}

// add child right
void add_right_child(Node *root, Node *child)
{
    root->right = child;

    if(child != NULL)
        child->parent = root;
}

// Insert BST
Node *bst_insert(Node *root, Node *node)
{
    Node *parent_node, *current_node;

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
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }

    if(node->data < parent_node->data)
        add_left_child(parent_node, node);
    else
        add_right_child(parent_node, node);

    return root;
}

// Create binary search tree;
Node *create_binary_search_tree(void)
{
    Node *root, *node;

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

// post order traversal
void post_order(Node *root)
{
    if(root->left != NULL)
        post_order(root->left);

    if(root->right != NULL)
        post_order(root->right);

    printf("%d ", root->data);
}

// bst search
Node *bst_search(Node *root, int item)
{
    Node *node;

    node = root;
    while(node != NULL)
    {
        if(node->data == item)
            return node;
        if(node->data > item)
            node = node->left;
        else
            node = node->right;
    }

    return node;
}
