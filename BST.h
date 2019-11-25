/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef BST_H
#define BST_H
#include "TreeNode.h"
#include <cstddef>
#include <iostream>

//Basic template binary search tree used to store and find data

template <typename T>
class BST
{
public:
    //default constructor
    BST();
    //destructor
    ~BST();
    //searches for given instance of store value
    T search(T value);
    //inserts an instance of a given type
    void insert(T value);
    //delete a node of an instance if it exists
    bool deleteNode(T value);

    //helpers
    bool isEmpty();
    TreeNode<T> *getMin();
    TreeNode<T> *getMax();
    //recursive print for a subtree
    void recPrint(TreeNode<T> *node);
    //prints the values of the tree in order
    void printInOrder();
    //gets node to succeed a node that will be deleted
    TreeNode<T> *getSuccessor(TreeNode<T> *d);
protected:
    //stores the root of the tree
    TreeNode<T> *root;
};
#endif

//default constructor
template <typename T>
BST<T>::BST()
{
    root = NULL;
}
//destructor to delete root node which will cause chain effect and delete all nodes
template <typename T>
BST<T>::~BST()
{
    if(root != NULL)
        delete root;
}
//recursively prints all contents of the tree given an initial node in order
template <typename T>
void BST<T>::recPrint(TreeNode<T> *node)
{
    //if node is not null then print through it and its childrens' nodes
    if(node != NULL)
    {
        //print left child
        if(node -> left != NULL)
            recPrint(node->left);
        //print current node
        std::cout << node->key << std::endl;
        //print right child
        if(node -> right != NULL)
            recPrint(node->right);
    }
    else 
    {
        return;
    }
        
}
//public method to be used to print nodes in order
template <typename T>
void BST<T>::printInOrder()
{
    recPrint(root);
}
//gets the maximum value in the current tree
template <typename T>
TreeNode<T> *BST<T>::getMax()
{
    TreeNode<T> *current = root;
    //keep getting the right child until not possible
    if (current == NULL)
        return NULL;
    while (current->right != NULL)
    {
        current = current->next;
    }
    return current;
    //or need to use return &(current -> key) to return address of the data
}
//gets minimum value stored in the tree
template <typename T>
TreeNode<T> *BST<T>::getMin()
{
    TreeNode<T> *current = root;
    //continue getting left child until no longer possible
    if (current == NULL)
        return NULL;
    while (current->left != NULL)
    {
        current = current->next;
    }
    return current;
    //or need to use return &(current -> key) to return address of the data
}
//inserts an instance as a new ned in the tree
template <typename T>
void BST<T>::insert(T value)
{
    //makes new node and checks to see if there are any nodes to begin with
    TreeNode<T> *newNode = new TreeNode<T>(value);
    if (root == NULL)
        root = newNode;
    //otherwise tree is not empty/need to find insertion location
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    //will run until the current node value is NULL, that way we can place the new node at that location
    //works by updating the parent to the current node then the if values move us down the tree
    //breaks when null leaf found for insertion
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
//takes an instance and searches the tree for equivalent node
template <typename T>
T BST<T>::search(T value)
{
    //if there are no nodes in the tree return null
    if (root == NULL)
        return NULL;
    //tree is not empty; let's look
    TreeNode<T> *current = root;
    //keeps updating current node to the left or right node based on its comparison to the current node
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

//delete node by searching for a node with equivalent value to that passed as argument, and then removes the node
template <typename T>
bool BST<T>::deleteNode(T value)
{
    //if no nodes are stored return false
    if (root == NULL)
        return false;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    //checks to see if the node to be deleted is a left child
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
    //if it has no null children(leafnode)
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
    current ->right = nullptr;
    current ->left = nullptr;
    delete current;
    //if node is effectively deleted
    return true;
}
//returns a successor for a node that will be deleted
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

