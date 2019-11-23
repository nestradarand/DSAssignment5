/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 4 Registrar Simulation
*/
#ifndef DLQUEUE_H
#define DLQUEUE_H
#include "DoublyLinkedList.h"
#include <iostream>

//Class storing the Queue implementation using a doubly linked list

template <typename T>
class DLQueue
{
public:
    //constructor,,int constructor,desctructor
    DLQueue();
    DLQueue(int maxSize);
    ~DLQueue();
    //stores reference to the doubl linked list to store all the data
    DoublyLinkedList<T> *theList;
    //adds new entry to the back of the queue
    void enqueue(const T i);
    //removes the first entry and returns it
    T dequeue();
    //returns reference to the data point stored at the first node
    T peek();
    // returns if the queue is empty
    bool isEmpty();
    //returns the size of the queue
    int getSize();
    //stores the number of elements being stored in the queue
    int numElements;

};
//default constructor
template <typename T>
DLQueue<T>::DLQueue()
{
    theList = new DoublyLinkedList<T>();
    numElements = 0;
}
//constructor for the maximum size of the queue (leftover from array implementation)
template <typename T>
DLQueue<T>::DLQueue(int maxSize)
{
//   myQueue = new T[maxSize];
//   size = maxSize;
    theList = new DoublyLinkedList<T>();
    numElements = 0;
}
//destructor to delete the doubly linked list
template <typename T>
DLQueue<T>::~DLQueue()
{
    delete theList;
}
//adds new entry to the end of the queue
template <typename T>
void DLQueue<T>::enqueue(const T i)
{
    theList -> insertBack(i);
    ++numElements;
}
//removes and entry from the front of the queue
template <typename T>
T DLQueue<T>::dequeue()
{
    if(isEmpty())
        throw std::runtime_error("Queue is empty, unable to dequeue");
    T returner;
    returner = theList -> removeFront();
    --numElements;
    return returner;
}
template <typename T>
T DLQueue<T>::peek()
{
    if(isEmpty())
        throw std::runtime_error("Queue is empty, nothing to peek at");
    return theList -> getFront();
}
//returns if the queue is empty
template <typename T>
bool DLQueue<T>::isEmpty()
{
  return(numElements == 0);
}
//returns the size of the queue
template <typename T>
int DLQueue<T>::getSize()
{
  return numElements;
}
#endif

