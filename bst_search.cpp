#include <iostream>

using namespace std;

typedef struct node Node;
struct node
{
    int data;
    Node *parent_node;
    Node *left_node;
    Node *right_node;
};

class BST
{
public:
    Node *create_bst_node(int item);
    void add_left_child(Node *root, Node *child);
    void add_right_child(Node *root, Node *child);
    Node *bst_insert(Node *root, Node *node);
    Node *create_bst_tree(void);
    Node *bst_search(Node *root, int item);
    void pre_order_traversal(Node *root);
};

int main(void)
{
    BST bst;
    Node *root, *node;

    root = bst.create_bst_tree();
    cout << "Root data: " << root->data << endl;

    bst.pre_order_traversal(root);

    node = bst.bst_search(root, 29);
    if(node != NULL)
        cout << "\n\n" << node->data << " Node found.\n" << endl;
    else
        cout << "\n\nNode not found.\n";

    return 0;
}

// create node
Node *BST::create_bst_node(int item)
{
    Node *new_node;

    new_node = new Node;
    if(new_node == NULL)
    {
        cout << "Error! Could not create a new node.\n";
        exit(1);
    }

    new_node->data = item;
    new_node->parent_node = NULL;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    return new_node;
    delete new_node;
}

// add left child
void BST::add_left_child(Node *root, Node *child)
{
    root->left_node = child;

    if(child != NULL)
        child->parent_node = root;
}

// add right child
void BST::add_right_child(Node *root, Node *child)
{
    root->right_node = child;

    if(child != NULL)
        child->parent_node = root;
}

// bst insert
Node *BST::bst_insert(Node *root, Node *node)
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

        if(current_node->data > node->data)
        {
            current_node = current_node->left_node;
        }
        else
        {
            current_node = current_node->right_node;
        }
    }

    if(parent_node->data > node->data)
        add_left_child(parent_node, node);
    else
        add_right_child(parent_node, node);

    return root;
}

// create bst tree
Node *BST::create_bst_tree(void)
{
    int i;
    int ara[] = {9, 2, 6, 3, 11, 1, 29, 51, 99, 4, 7};
    int n = sizeof(ara) / sizeof(ara[0]);
    Node *root, *node;

    // create root
    root = create_bst_node(25);

    for(i = 0; i < n; i++)
    {
        node = create_bst_node(ara[i]);
        root = bst_insert(root, node);
    }

    return root;
}

// Traversal
void BST::pre_order_traversal(Node *root)
{
    cout << root->data << " ";

    if(root->left_node != NULL)
        pre_order_traversal(root->left_node);

    if(root->right_node != NULL)
        pre_order_traversal(root->right_node);
}

// bst search
Node *BST::bst_search(Node *root, int item)
{
    Node *node = root;

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

