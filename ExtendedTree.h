/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef EXTENDED_TREE
#define EXTENDED_TREE
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include <cstddef>
#include <iostream>
#include <fstream>

//This tree serves to extend the BST to a more specialized version to meet the demands of cataloging
//Students and Facutly objects

template <typename T>
class ExtendedTree: public BST<T>
{
    public:
        //default construtctor
        ExtendedTree();
        //prints nodes in their entirety using toString method
        void printToStrings();
        //basic insertion of new value
        void insert(T value);
        //returns instance of stored value if found
        T search(T entry);
        //returns any entry other than the one entered (used to find new advisors)
        T getEntryOtherThan(T value);
        //delets a node containing instance equivalent to that passed as argument
        bool deleteNode(T entry);
        //writes contents of all nodes in serializable form to a given filestream
        void write(std::ofstream &stream);
    

    private:
        //prints all nodes using toString method recursively
        void printFullNodes(TreeNode<T> *root);
        //finds entry other than argument 
        T privateGetEntryOtherThan(T entry);
        //finds succeesor for a node that will be deleted
        TreeNode<T> *getSuccessor(TreeNode<T> *d);
        //writes all nodes to specified filestream recursively
        void recursiveWriteAll(TreeNode<T> *node,std::ofstream &stream);
};
#endif
//default constructor
template <typename T>
ExtendedTree<T>::ExtendedTree(): BST<T>()
{

}
//prints all nodes' data using their toString method, to be used in public scope
template <typename T>
void ExtendedTree<T>::printToStrings()
{
    if (this ->root != NULL)
        printFullNodes(this -> root);
    else
        std::cout << "There is nothing stored to print out" << std::endl;
}
//prints all nodes recursively using toString, prints inorder
template <typename T>
void ExtendedTree<T>::printFullNodes(TreeNode<T> *root)
{
    if (root != NULL)
    {
        printFullNodes(root->left);
        std::cout << root->key->toString() << "\n---" << std::endl;
        printFullNodes(root->right);
    }
    else
        return;
}
//inserts value same as regular BST but instead uses overloaded operators
template <typename T>
void ExtendedTree<T>::insert(T value)
{
    TreeNode<T> *newNode = new TreeNode<T>(value);
    if (this ->root == NULL)
        this -> root = newNode;
    //otherwise tree is not empty/need to find insertion location
    TreeNode<T> *current = this->root;
    TreeNode<T> *parent = NULL;
    //will run until the current node value is NULL, that way we can place the new node at that location
    //works by updating the parent to the current node then the if values move us down the tree
    while (true)
    {
        parent = current;
        if (value->operator<(*current->key))
        {
            current = current->left;
            if (current == NULL)
            {
                parent->left = newNode;
                break;
            }
        }
        else if (value->operator>(*current->key))
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
//works the same as normal BST search function but instead uses overloaded operators
template <typename T>
T ExtendedTree<T>::search(T value)
{
    if (this->root == NULL)
        return NULL;
    //tree is not empty; let's look
    TreeNode<T> *current = this->root;
    while (current->key->operator!=(*value))
    {
        if (value->operator<(*current->key))
            current = current->left;
        else
            current = current->right;
        if (current == NULL) //didnt find the value
            return NULL;
    }
    return current->key; //happens if the value was found which would have broken the loop above
}
//public method to get entry other than the one passed as an argument
template <typename T>
T ExtendedTree<T>::getEntryOtherThan(T entry)
{
    return privateGetEntryOtherThan(entry);
}
//returns next available entry looking at the root and its children
template <typename T>
T ExtendedTree<T>::privateGetEntryOtherThan(T entry)
{
    {
        if (this->root == NULL)
            return NULL;
        //tree is not empty; let's look
        TreeNode<T> *current = this->root;
        if(current ->key->operator!=(*entry))
            return current->key;
        else 
        {
            if(current ->right != NULL)
                current  = current -> right;
            else if (current->left != NULL)
                current = current -> left;
            else 
                return NULL;
        }
        return current->key; //happens if the value was found which would have broken the loop above
    }
}
//deletes a node given a value, works the sam as normal delete but instead uses overloaded operators
template <typename T>
bool ExtendedTree<T>::deleteNode(T value)
{
    if (this ->root == NULL)
        return false;

    TreeNode<T> *current = this ->root;
    TreeNode<T> *parent = this ->root;
    bool isLeft = true;
    while (current->key->operator!=(*value))
    {
        isLeft = true;
        parent = current;
        if (value->operator<(*current->key))
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
        if (current == this ->root)
            this -> root = NULL;
        else if (isLeft)
            parent->left = NULL;
        else
            parent->right = NULL;
    }

    //if node to be deleted has one child
    //need to determine if child is left or right
    else if (current->right == NULL) //no right child
    {
        if (current == this -> root)
        {
            this->root = current->left;
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
        if (current == this ->root)
        {
            this ->root = current->right;
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

        if (current == this ->root)
            this ->root = successor;
        else if (isLeft)
        {
            parent->left = successor;
        }
        else
            parent->right = successor;
        successor->left = current->left;
    }
    current->right = nullptr;
    current->left = nullptr;
    delete current;
    return true;
}
//returns the sucessor of a node to be deleted, does so using overloaded operators
template <typename T>
TreeNode<T> *ExtendedTree<T>::getSuccessor(TreeNode<T> *d)
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
//public method to begin recursive writing process for all nodes
template <typename T>
void ExtendedTree<T>::write(std::ofstream &stream)
{
    recursiveWriteAll(this->root,stream);
}
//writes all nodes recursively using pre order traversal; writes serializable info from all instances
template <typename T>
void ExtendedTree<T>::recursiveWriteAll(TreeNode<T> *node,std::ofstream &stream)
{
    if(node != NULL)
    {
        stream << node->key->getSerializable() << "\r\n";
        recursiveWriteAll(node ->right,stream);
        recursiveWriteAll(node ->left,stream);
    }
    else    
        return;
}

