/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef DOUBLELISTNODE_H
#define DOUBLELISTNODE_H
#include <cstddef>

///doubly linked list node implementation
template <typename T>
class DoubleListNode
{
public:
  //member variables of the data and references to next and previous nodes in the list
  T data;
  DoubleListNode<T> *next;
  DoubleListNode<T> *prev;

  //constructors and desctrutor
  DoubleListNode();
  DoubleListNode(T data);
  ~DoubleListNode();
};
//default constructor
template <typename T>
DoubleListNode<T>::DoubleListNode(){}
//data constructor
template <typename T>
DoubleListNode<T>::DoubleListNode(T newData)
{
  data = newData;
  next = NULL;
  prev = NULL;
}
//destructor
template <typename T>
DoubleListNode<T>::~DoubleListNode()
{
  //sets references to other nodes as null
  next = NULL;
  prev = NULL;
}
#endif
