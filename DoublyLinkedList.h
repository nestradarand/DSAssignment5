/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "DoubleListNode.h"
#include <cstddef>
#include <iostream>

//list functionality using doubly linked implementation

template <typename T>
class DoublyLinkedList
{
private:
  //member variables referecning the front and back of the list and the size of the list
    DoubleListNode<T> *front;
    DoubleListNode<T> *back;
    unsigned int size;
public:
  //constructor and destructor
    DoublyLinkedList();
    ~DoublyLinkedList();
    //inserting values to front or back of the list
    void insertFront(T newEntry);
    void insertBack(T newEntry);
    //removing values from from or back of the list
    T removeBack();
    T removeFront();
    //returns the front/back of the list
    T getFront();
    T getBack();
    //finds index based on the entry
    int find(T entry);
    //removes an entry based on the instance passed to it
    bool remove(T entry);
    //indicates if the list is empty or not
    bool isEmpty();
    //prints contents of the list
    void printList();
    //returns the size of the list
    unsigned int getSize();
};


//default constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  size = 0;
  front = NULL;
  back = NULL;
}
//destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  while(!isEmpty())
    removeFront();
}
//inserts instance to front of the list
template <typename T>
void DoublyLinkedList<T>::insertFront(T newEntry)
{
  DoubleListNode<T> *node = new DoubleListNode<T>(newEntry);
  if(size == 0)//empty list
  {
    back = node;
  }
  else
  {
    node -> next = front;
    front -> prev = node;
  }
  front = node;

  size ++;

}
//removes instance from the front of the list and returns it
template <typename T>
T DoublyLinkedList<T>::removeFront()
{
  if(isEmpty())
    throw std::runtime_error("List is empty.");    
  T holder = front -> data;
  DoubleListNode<T> *toDelete = front;
  if(size == 1)//only one node in the list
  {
    back = NULL;
  }
  else //more than one node
  {
    front -> next -> prev = NULL;
  }
  front = front -> next;
  toDelete -> next = NULL;
  delete toDelete;
  size -- ;
  return holder;
}
//inserts instance to the back of the list
template <typename T>
void DoublyLinkedList<T>::insertBack(T newEntry)
{
  DoubleListNode<T> *node = new DoubleListNode<T>(newEntry);
  if(size == 0)//empty list
  {
    front = node;
  }
  else//not an empty list
  {
    node -> prev = back;
    back -> next = node;
  }
  back = node;

  size ++;
}
//removes instance and returns it from the back of the list
template <typename T>
T DoublyLinkedList<T>::removeBack()
{
  if(isEmpty())
    throw std::runtime_error("stack is empty");
  DoubleListNode<T> *backTemp = back;
  if(size == 1)//only one node in the list
  {
    front = NULL;
  }
  else //more than one node
  {
    back -> prev -> next = NULL;
  }
  back = back -> prev;
  T temp = backTemp -> data;
  backTemp -> prev = NULL;
  delete backTemp;
  size --;

  return temp;
}
//removes an instance by searching for it then removing it
template <typename T>
bool DoublyLinkedList<T>::remove(T data)
{
  if(isEmpty())
    return false;
  DoubleListNode<T> *current = front;
  while(current -> data != data)//as long as we dont find the data
  {
    current = current -> next;
    if(current == NULL)//means we didnt find the data
      return false;
  }
  //if we get to here it means we found it
  //check if the node is the front
  if(current == front)
    front  = current -> next;

  else
  {
    //not the front
    //attach previouis to the one in front of the current
    current -> prev -> next = current -> next;
  }
  if(current == back)
    back = current -> prev;
  else //not the back
  {
    current -> next -> prev = current -> prev;
  }
  //detach current
  current -> next = NULL;
  current -> prev = NULL;
  size --;
  delete current;
  return true;
}
//returns if the list is empty
template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
  return size == 0;
}
//prints all contents
template <typename T>
void DoublyLinkedList<T>::printList()
{
  DoubleListNode<T> *current = front;
  while(current != NULL)
  {
    std::cout <<current -> data << std::endl;
    current = current -> next;
  }
}
//returns the length of the list
template <typename T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}
//finds an entry and returns its index in the list
template <typename T>
int DoublyLinkedList<T>::find(T entry)
{
  int index = 0;
  DoubleListNode<T> *current = front;
  while(current != NULL)
  {
    if(current -> data == entry)
      break;
    index ++;
    current = current -> next;
  }
  if(current == NULL)
    index = -1;
  return index;  
}
//returns instance at the front of the list
template <typename T>
T DoublyLinkedList<T>::getFront()
{
  return front ->data;
}
//returns the instance at the back of the list
template <typename T>
T DoublyLinkedList<T>::getBack()
{
  return back -> data;
}

#endif
