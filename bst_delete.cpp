#include <iostream>

using namespace std;

typedef struct node Node;
struct node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
};

class Bst
{
public:
    Node *create_bst_node(int item);
    void add_child_left(Node *root, Node *child);
    void add_child_right(Node *root, Node *child);
    Node *bst_minimum(Node *root);
    Node *create_bst_tree(void);
    Node *bst_insert(Node *root, Node *node);
    void in_order(Node *root);
    Node *bst_search(Node *root, int item);
    Node *bst_transplant(Node *root, Node *current_node, Node *new_node);
    Node *bst_delete(Node *root, Node *node);
};

int main(void)
{
    Bst bst;
    Node *root, *node;

    root = bst.create_bst_tree();
    cout << "Root Data: " << root->data << endl;

    // full bst tree;
    cout << "BST: \n";
    bst.in_order(root);
    cout << "\n";

    node = bst.bst_search(root, 10);
    if(node != NULL)
    {
        cout << "Will delete " << node->data << "\n";
        root = bst.bst_delete(root, node);

        cout << "BST: \n";
        bst.in_order(root);
        cout << "\n";
    }
    else
        cout << "Node not found.\n";

    return 0;
}

// create node
Node *Bst::create_bst_node(int item)
{
    Node *new_node;

    new_node = new Node;
    if(new_node == NULL)
    {
        cout << "Error! Could not create a bst new Node.\n";
        exit(1);
    }

    new_node->data = item;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
    delete new_node;
}

// add child left
void Bst::add_child_left(Node *root, Node *child)
{
    root->left = child;

    if(child != NULL)
        child->parent = root;
}

// add child right
void Bst::add_child_right(Node *root, Node *child)
{
    root->right = child;

    if(child != NULL)
        child->parent = root;
}

// bst minimum
Node *Bst::bst_minimum(Node *root)
{
    Node *node = root;

    while(node != NULL)
    {
        node = node->left;
    }
    return node;
}

// create bst tree
Node *Bst::bst_insert(Node *root, Node *node)
{
    Node *current_node, *parent_node;

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
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }

    if(parent_node->data > node->data)
        add_child_left(parent_node, node);
    else
        add_child_right(parent_node, node);

    return root;
}

// create bst tree
Node *Bst::create_bst_tree(void)
{
    Node *root, *node;

    int i;
    int arr[] = {11, 4, 6, 55, 19, 8, 10, 3};
    int n = (sizeof(arr)/sizeof(arr[0]));

    // create root
    root = create_bst_node(25);

    for(i=0; i<n; i++)
    {
        node = create_bst_node(arr[i]);
        root = bst_insert(root, node);
    }

    return root;
}

// in order traversal
void Bst::in_order(Node *root)
{
    if(root->left != NULL)
        in_order(root->left);

    cout << root->data << " ";

    if(root->right != NULL)
        in_order(root->right);
}

// search item
Node *Bst::bst_search(Node *root, int item)
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

// transplant
Node *Bst::bst_transplant(Node *root, Node *current_node, Node *new_node)
{
    if(current_node == root)
    {
        root = new_node;
    }
    else if(current_node == current_node->parent->left)
    {
        add_child_left(current_node->parent, new_node);
    }
    else
    {
        add_child_right(current_node->parent, new_node);
    }

    return root;
}

// delete
Node *Bst::bst_delete(Node *root, Node *node)
{
    Node *smallest_node;

    if(node->left == NULL)
    {
        root = bst_transplant(root, node, node->right);
    }
    else if(node->right == NULL)
    {
        root = bst_transplant(root, node, node->left);
    }
    else
    {
        smallest_node = bst_minimum(node->right);

        if(smallest_node->parent != node)
        {
            root = bst_transplant(root, smallest_node, smallest_node->right);
            add_child_right(smallest_node, node->right);
        }
        else
            root = bst_transplant(root, node, smallest_node);
        add_child_left(smallest_node, node->left);
    }

    free(node);
    return root;
}
