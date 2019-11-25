/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef TREENODE_H
#define TREENODE_H
#include <cstddef>

//Node class to store data for tree implementation

template <typename T>
class TreeNode 
{
public:
    //default constructor
    TreeNode();
    //constructor when given value
    TreeNode(T newKey);
    //destructor
    ~TreeNode();
    //member variables to store the data and references to left/right child
    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
#endif

//default constructor
template <typename T>
TreeNode<T>::TreeNode()
{
    key = nullptr;
    left = nullptr;
    right = nullptr;
}
//constructor to initialize with a value
template <typename T>
TreeNode<T>::TreeNode(T newKey)
{
    key = newKey;
    left = nullptr;
    right = nullptr;
}
//destructor
template <typename T>
TreeNode<T>::~TreeNode()
{
    //when destructed, will delete anything it is referenced to creating a domino effect 
    if(key != nullptr)
        delete key;
    if(left != nullptr)
        delete left;
    if(right != nullptr)
        delete right;
}