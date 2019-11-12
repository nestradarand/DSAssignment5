#ifndef DOUBLELISTNODE_H
#define DOUBLELISTNODE_H
#include <cstddef>


template <typename T>
class DoubleListNode
{
public:
  T data;
  DoubleListNode<T> *next;
  DoubleListNode<T> *prev;

  DoubleListNode();
  DoubleListNode(T data);
  ~DoubleListNode();
};

template <typename T>
DoubleListNode<T>::DoubleListNode(){}
template <typename T>
DoubleListNode<T>::DoubleListNode(T newData)
{
  data = newData;
  next = NULL;
  prev = NULL;
}
template <typename T>
DoubleListNode<T>::~DoubleListNode()
{
  if(next == NULL)
    delete next;
  if(prev == NULL)
    delete prev;
}
#endif
