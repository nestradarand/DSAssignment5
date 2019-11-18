#ifndef BST_H
#define BST_H
#include "TreeNode.h"
#include <cstddef>
#include <iostream>

template <typename T>
class BST
{
public:
    BST();
    ~BST();
    T search(T value);
    void insert(T value);
    bool deleteNode(T value);

    //helpers
    bool isEmpty();
    TreeNode<T> *getMin();
    TreeNode<T> *getMax();
    //recursive print for a subtree
    void recPrint(TreeNode<T> *node);
    //prints the values of the tree in order
    void printInOrder();
    TreeNode<T> *getSuccessor(TreeNode<T> *d);
    //prints all the to string methods for a given tree

    TreeNode<T> *root;
    void printFullNodes(TreeNode<T> *root);
};
#endif

template <typename T>
BST<T>::BST()
{
    root = NULL;
}
template <typename T>
BST<T>::~BST()
{
    if(root != NULL)
        delete root;
}
//up to us in this case
////something wrong
template <typename T>
void BST<T>::recPrint(TreeNode<T> *node)
{
    if(node != NULL)
    {
        if(node -> left != NULL)
            recPrint(node->left);
        std::cout << node->key << std::endl;
        if(node -> right != NULL)
            recPrint(node->right);
    }
    else 
    {
        return;
    }
        
}
//works
template <typename T>
void BST<T>::printInOrder()
{
    recPrint(root);
}
//works
template <typename T>
TreeNode<T> *BST<T>::getMax()
{
    TreeNode<T> *current = root;
    if (current == NULL)
        return NULL;
    while (current->right != NULL)
    {
        current = current->next;
    }
    return current;
    //or need to use return &(current -> key) to return address of the data
}
template <typename T>
TreeNode<T> *BST<T>::getMin()
{
    TreeNode<T> *current = root;
    if (current == NULL)
        return NULL;
    while (current->left != NULL)
    {
        current = current->next;
    }
    return current;
    //or need to use return &(current -> key) to return address of the data
}
//works
template <typename T>
void BST<T>::insert(T value)
{
    TreeNode<T> *newNode = new TreeNode<T>(value);
    if (root == NULL)
        root = newNode;
    //otherwise tree is not empty/need to find insertion location
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    //will run until the current node value is NULL, that way we can place the new node at that location
    //works by updating the parent to the current node then the if values move us down the tree
    while (true)
    {
        parent = current;
        if (value < current->key)
        {
            current = current->left;
            if (current == NULL)
            {
                parent->left = newNode;
                break;
            }
        }
        else if(value >current -> key)
        {
            current = current->right;
            if (current == NULL)
            {
                parent->right = newNode;
                break;
            }
        }
        else
            break;
    }
}
template <typename T>
T BST<T>::search(T value)
{
    if (root == NULL)
        return NULL;
    //tree is not empty; let's look
    TreeNode<T> *current = root;
    while (current ->key != value)
    {
        if (value < current->key)
            current = current->left;
        else
            current = current->right;
        if (current == NULL) //didnt find the value
            return NULL;
    }
    return current ->key; //happens if the value was found which would have broken the loop above
}

//works
template <typename T>
bool BST<T>::deleteNode(T value)
{
    if (root == NULL)
        return false;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;
    while (current->key != value)
    {
        isLeft = true;
        parent = current;
        if (value < current->key)
            current = current->left;
        else
        {
            isLeft = false;
            current = current->right;
        }
        //occurs in the even that the value is not found in the tree
        if (current == NULL)
        {
            std::cout << "value not found to delete" << std::endl;
            return false;
        }
    }
    //if we make it here then we found the node with the value to be deleted
    //if it has no non null children(leafnode)
    if (current->left == NULL && current->right == NULL)
    {
        if (current == root)
            root = NULL;
        else if (isLeft)
            parent->left = NULL;
        else
            parent->right = NULL;
    }

    //if node to be deleted has one child
    //need to determine if child is left or right
    else if (current->right == NULL) //no right child
    {
        if (current == root)
        {
            root = current->left;
        }
        else if (isLeft)
        {
            parent->left = current->left;
        }
        else
            parent->right = current->left;
    }
    else if (current->left == NULL) //no left child
    {
        if (current == root)
        {
            root = current->right;
        }
        else if (isLeft)
        {
            parent->left = current->right;
        }
        else
            parent->right = current->right;
    }
    else //node to be deleted has two children
    {
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root)
            root = successor;
        else if (isLeft)
        {
            parent->left = successor;
        }
        else
            parent->right = successor;
        successor->left = current->left;
    }
    return true;
}
template <typename T>
TreeNode<T> *BST<T>::getSuccessor(TreeNode<T> *d)
{
    TreeNode<T> *sp = d; //successor parent
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while (current != NULL) //one right all the way left
    {
        sp = successor;
        successor = current;
        current = current->left;
    }
    if (successor != d->right)       // if it just isnt the right child of d
    {                                //means it is a successor of the right child
        sp->left = successor->right; //if the leftmost has a right child
        successor->right = d->right;
    }
    return successor;
}

