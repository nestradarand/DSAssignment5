#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "DoubleListNode.h"
#include <cstddef>
#include <iostream>


template <typename T>
class DoublyLinkedList
{
private:
    DoubleListNode<T> *front;
    DoubleListNode<T> *back;
    unsigned int size;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T newEntry);
    void insertBack(T newEntry);
    T removeBack();
    T removeFront();
    T getFront();
    T getBack();
    //finds index based on the entry
    int find(T entry);
    bool remove(T entry);

    bool isEmpty();
    void printList();
    unsigned int getSize();
};

//implementation
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  size = 0;
  front = NULL;
  back = NULL;
}
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  while(!isEmpty())
    removeFront();
}
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
//need to as if this is even necessary
template <typename T>
bool DoublyLinkedList<T>::remove(T data)
{
  if(isEmpty())
    throw std::runtime_error("list is empty");
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
template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
  return size == 0;
}
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
template <typename T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}
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
template <typename T>
T DoublyLinkedList<T>::getFront()
{
  return front ->data;
}
template <typename T>
T DoublyLinkedList<T>::getBack()
{
  return back -> data;
}
//needs work do we even need it???
// template <typename T>
// T DoublyLinkedList<T>::deletePos(int position)
// {
//     if(size == 0)
//       throw std::runtime_error("List is empty");
//     int index = 0;
//     DoubleListNode<T> *current = front;
//     DoubleListNode<T> *previous = front;
//     //if the first node is to be deleted
//     if(position == index)
//     {
//       previous = NULL;
//       front = current ->next;
//       current -> next -> prev = NULL;
//       current -> next -> NULL;
//     }
//     else
//     {
//       while(index != position)
//       {
//         previous = current;
//         current = current -> next;
//         index ++;
//       }
//       previous ->next = current -> next;
//       //to avoid the next in line node
//       current -> next = NULL;
//     }
    
//     T returner = current -> data;  
//     size -- ;
//     previous = NULL;
//     delete previous;
//     delete current;
//     return returner;
// }
#endif
