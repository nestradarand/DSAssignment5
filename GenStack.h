#ifndef GENSTACK_H
#define GENSTACK_H

#include <iostream>

//template class to store any data type in a stack ADT
template <typename T>
class GenStack
{
  //stores how many entries can be held and the top index for access to most recently added element
  int size;
  int top;
  //pointers to the arrays storing data in this implementation
  T *theStack;
  // T *tempArray;
public:
  //constructors
  GenStack();
  GenStack(int i);
  //desctructor
  ~GenStack();
  //returns if the stack is empty
  bool isEmpty() const;
  //adds element to the stack
  void push(const T &object);
  //removes and returns the top element of the stack
  T pop();
  //allows viewing of the top element on the stack
  const T peek() const;
  //returns if the stack is full
  const bool isFull() const;
private:
  void resizeArray(T* newArray,int size);
};

//default constructor gives stack size 100
template <typename T>
GenStack<T>::GenStack()
{
  theStack = new T[100];
  size = 100;
  top = -1;
}
//int constructor takes in int argument to initialize to that size
template <typename T>
GenStack<T>::GenStack(int i)
{
  if(i <0)
    throw std::runtime_error("Invalid value entered for stack size");
  theStack = new T[i];
  size = i;
  top = -1;
}
//deconstructor that deallocates memory for pointer to array
template <typename T>
GenStack<T>::~GenStack()
{
  delete theStack;
}
//returns if the stack is empty
template <typename T>
bool GenStack<T>::isEmpty() const
{
  return top == -1;
}
//adds new element to the stack
template <typename T>
void GenStack<T>::push(const T &object)
{
  if(isFull())
  {
    resizeArray(theStack,size);
  }
  theStack[++top] = object;
}
//removes and returns the top element on the stack
template <typename T>
T GenStack<T>::pop()
{
  if(isEmpty())
    throw std::runtime_error("Cannot pop. Stack is empty.");
  return theStack[top--];
}
//returns the first element on the stack
template <typename T>
const T GenStack<T>::peek() const
{
  if(isEmpty())
    throw std::runtime_error("Cannot pop. Stack is empty.");
  return theStack[top];
}
//returns if the stack is full
template <typename T>
const bool GenStack<T>::isFull() const
{
  return (top == size -1);
}
//resizes the array when called to double the initial capacity with the same elements copied over
template <typename T>
void GenStack<T>::resizeArray(T* newArray,int currentSize)
{
  T *tempArray = new T[currentSize*2];
  T *stackHolder = theStack;
  for(int i = 0; i<currentSize; ++i)
    tempArray[i] = newArray[i];
  theStack = tempArray;
  tempArray = NULL;
  delete stackHolder;
  delete tempArray;
  size = currentSize *2;
}

#endif
