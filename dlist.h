#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdlib.h>
#include "container.h"

#define LETS_BEGIN 100
#define LETS_GROW 50

#define TRUE  1
#define FALSE 0

template<class T>
class Dlist_t : public Container_t<T>
{
  public:
    Dlist_t();
    virtual ~Dlist_t();
    Dlist_t(const Dlist_t<T>& _existingDlist);
    const Dlist_t<T> operator=(const Dlist_t<T>& _existingDlist);

    virtual bool     append(const T* _newElement, int _givenIndex);
    virtual bool     prepend(const T* _newElement, int _givenIndex);

    virtual bool     contains(T& _newElement);
    virtual T* find(const T& _value);
    virtual size_t   index(T& _newElement);
    virtual bool     insert(const T* _newElement);

    virtual bool     remove(T* _oldElement, T _value);
    virtual void     removeAll();
    virtual void     removeAndDelete(const T* _oldElement);
    virtual void     removeAndDeleteAll();

  private:
    template <class N>
    class Node_t
    {
      public:
        Node_t(){};
        Node_t(const Node_t<T>& _next, const Node_t<T>& _prev, const T& _data):m_next(&_next), m_prev(&_prev), m_data(&_data) {}
        ~Node_t(){};

        Node_t* m_next;
        Node_t* m_prev;
        const T* m_data;
    };

      private:
        Node_t<T> m_head;
        Node_t<T> m_tail;
};

/* -------------------------------------------------------------- */

template<class T>
Dlist_t<T>::Dlist_t()
{
  m_head.m_next = &m_tail;
  m_tail.m_prev = &m_head;
}

/* -------------------------------------------------------------- */

template<class T>
Dlist_t<T>::~Dlist_t(){}

/* -------------------------------------------------------------- */

template<class T>
Dlist_t<T>::Dlist_t(const Dlist_t<T>& _existingDlist)
{
  int i;
  int numElements = _existingDlist.Count();

  const Node_t<T>* currentNode = &(_existingDlist.m_head);
  currentNode = currentNode->m_next;              //set to the first element after head

  for(i = 0; i < numElements; ++i)                //for all the elements in the list
  {
    T* newValue = new T();
    *newValue = *(currentNode->m_data);           //get the data of the element
    insert(newValue);                             //put it into the list
    currentNode = currentNode->m_next;            //continue
  }
}
/* -------------------------------------------------------------- */

template<class T>
const Dlist_t<T> Dlist_t<T>::operator=(const Dlist_t& _existingDlist)
{
  size_t i;
  int numElements = _existingDlist.Count();

  if(this != &_existingDlist)
  {
    removeAll();
    Container_t<T>::operator=(_existingDlist);

    const Node_t<T>* currentNode = &(_existingDlist.m_head);
    currentNode = currentNode->m_next;

    for(i = 0; i < numElements; ++i)
    {
      T* newData = new T();
      *newData = *(currentNode->m_data);
      Insert(newData);
      currentNode = currentNode->m_next;
    }
  }
  return *this;
}

/* -------------------------------------------------------------- */

template<class T>
bool Dlist_t<T>::append(const T* _newElement, int _givenIndex)
{
  size_t i;
  if(_givenIndex  + 1 <= Container_t<T>::count())
  {
    Node_t<T>* currNode = &m_head;
    for(i = 0; i < _givenIndex + 1; ++i)
    {
      currNode = currNode->m_next;
    }

    Node_t<T>* newNode = new Node_t<T>();
    if(!newNode)
    {
      throw TException_t<int>(__FILE__, __LINE__, _givenIndex, "Memory allocation error.");
    }

    newNode->m_next = currNode->m_next;
    newNode->m_prev = currNode;
    newNode->m_data = _newElement;

    currNode->m_next->m_prev = newNode;
    currNode->m_next = newNode;
    Container_t<T>::increaseNumElements();

    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/* -------------------------------------------------------------- */

template<class T>
bool Dlist_t<T>::prepend(const T* _newElement, int _givenIndex)
{
  return _givenIndex > 0 ? append(_newElement,_givenIndex - 1) : FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
bool Dlist_t<T>::contains(T& _element)
{
  return (index(_element)) ? TRUE : FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
size_t Dlist_t<T>::index(T& _element)
{
  int index;

  const Node_t<T>* currentNode = (Dlist_t<int>::Node_t<int>*)&m_head;
  currentNode = currentNode->m_next;
  for(index = 0; currentNode != &m_tail; currentNode = currentNode->m_next)
  {
    if(*currentNode->m_data == _element)
    {
      return index;
    }
    ++index;
  }
  return FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
T* Dlist_t<T>::find(const T& _value)
{
  int index;
  const Node_t<T>* currentNode = (Dlist_t<int>::Node_t<int>*)&m_head;
  currentNode = currentNode->m_next;
  for(index = 0; currentNode != &m_tail; currentNode = currentNode->m_next)
  {
    if(*currentNode->m_data == _value)
    {
      return (T*)currentNode->m_data;
    }
    ++index;
  }
  throw TException_t<int>(__FILE__, __LINE__, _value, "Couldn't be found.");
}

/* -------------------------------------------------------------- */

template<class T>
bool Dlist_t<T>::insert(const T* _newElement)
{
  return append(_newElement, Container_t<T>::count() - 1); //append to the end
}

/* -------------------------------------------------------------- */

template<class T>
bool Dlist_t<T>::remove(T* _oldElement, T _value)
{
  const Node_t<T>* currentNode = &m_head;
  currentNode = currentNode->m_next;
  for(; currentNode != &m_tail; currentNode = currentNode->m_next)
  {
    if(currentNode->m_data == _oldElement)
    {
      currentNode->m_prev->m_next = currentNode->m_next;
      currentNode->m_next->m_prev = currentNode->m_prev;
      _value = *currentNode->m_data;

      delete currentNode;
      Container_t<T>::decreaseNumElements();

      return TRUE;
    }
  }
return FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
void Dlist_t<T>::removeAll()
{
  const Node_t<T>* currentNode = &m_head;
  currentNode = currentNode->m_next->m_next; // because we're deletin the previous
  for(; currentNode != &m_tail; currentNode = currentNode->m_next)
  {
    delete currentNode->m_prev;
    Container_t<T>::decreaseNumElements();
  }
  delete currentNode->m_prev;
  Container_t<T>::decreaseNumElements();

  m_head.m_next = &m_tail;
  m_tail.m_prev = &m_head;
}

/* -------------------------------------------------------------- */

template<class T>
void Dlist_t<T>::removeAndDelete(const T* _oldElement)
{
  const Node_t<T>* currentNode = &m_head;
  currentNode = currentNode->m_next;
  for(; currentNode != &m_tail; currentNode = currentNode->m_next)
  {
    if(currentNode->m_data == _oldElement)
    {
      currentNode->m_prev->m_next = currentNode->m_next;
      currentNode->m_next->m_prev = currentNode->m_prev;

      delete currentNode;
      Container_t<T>::decreaseNumElements();
    }
  }
}

/* -------------------------------------------------------------- */

template<class T>
void Dlist_t<T>::removeAndDeleteAll()
{
  const Node_t<T>* currentNode = &m_head;
  currentNode = currentNode->m_next;
  currentNode = currentNode->m_next;

  for(; currentNode != &m_tail; currentNode = currentNode->m_next) //nothing in first param is ok?
  {
    delete currentNode->m_prev;
    Container_t<T>::decreaseNumElements();

  }

  delete currentNode->m_prev;
  Container_t<T>::decreaseNumElements();

  m_head.m_next = &m_tail;
  m_tail.m_prev = &m_head;
}

#endif /* __DLIST_H__ */
