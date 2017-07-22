#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>
#include <stdlib.h>
#include "container.h"
#include "exception_handler.h"

using namespace std;

#define LETS_BEGIN 100
#define LETS_GROW 50

#define TRUE  1
#define FALSE 0

template<class T>
class Array_t : public Container_t<T>
{
  public:
    Array_t();
    virtual ~Array_t();
    Array_t(const Array_t<T>& _existingArray);
    const Array_t<T>& operator=(const Array_t<T>& _existingArray);

    virtual bool   append(const T* _newElement, int _givenIndex);
    virtual bool   prepend(const T* _newElement, int _givenIndex);

    virtual bool   contains(T& _newElement);
    virtual T* find(const T& _value);
    virtual size_t index(T& _newElement);
    virtual bool   insert(const T* _newElement);

    virtual bool   remove(T* _newElement, T _value);
    virtual void   removeAll();
    virtual void   removeAndDelete(const T* _newElement);
    virtual void   removeAndDeleteAll();

  private:
    static size_t m_initialSize;
    size_t m_currentSize;
    T**    m_elements; //must be ptr to ptr since it pts to the T* in the container
};

/* -------------------------------------------------------------- */

template<class T>
size_t Array_t<T>::m_initialSize = LETS_BEGIN;

/* -------------------------------------------------------------- */

template<class T>
Array_t<T>::Array_t()
{
  m_currentSize = m_initialSize;
  m_elements = new T*[m_currentSize];
  if(!m_elements)
  {
    throw TException_t<int>(__FILE__, __LINE__, m_currentSize, "The elements weren't properly allocated.");
  }
}

/* -------------------------------------------------------------- */

template<class T>
Array_t<T>::~Array_t()
{
  delete[] m_elements;
  m_currentSize = 0;
  Container_t<T>::setIncomingNumElements(0);
}
/* -------------------------------------------------------------- */

template<class T>
Array_t<T>::Array_t(const Array_t<T>& _existingArray): Container_t<T>(_existingArray)
{
  m_currentSize = _existingArray.m_currentSize;
  //Container_t<T>::setIncomingNumElements(_existingArray.m_numOfElements);

  m_elements = new T*[m_currentSize];
  memcpy(m_elements, _existingArray.m_elements, (sizeof(T*) * _existingArray.m_numOfElements));
}
/* -------------------------------------------------------------- */

template <class T>
const Array_t<T>& Array_t<T>::operator=(const Array_t<T>& _arr)
{
  if(this != &_arr)
  {
    Container_t<T>::operator=(_arr);
      if(m_currentSize < _arr.m_currentSize)
      {
        delete[] m_elements;
        m_elements = new T*[_arr.m_currentSize];
        m_currentSize = _arr.m_currentSize;
      }
    memcpy(m_elements, _arr.m_elements, sizeof(T*) * _arr.Count());
  }
  return *this;
}

/* -------------------------------------------------------------- */

template<class T>
bool Array_t<T>::append(const T* _newElement, int _givenIndex)
{
  if ((_givenIndex > Container_t<T>::count()) || (_givenIndex < 0))
  {
    return FALSE;
  }

  size_t largerSize = (m_currentSize > Container_t<T>::count() ? m_currentSize : Container_t<T>::count());
  T** resizedArr = new T*[largerSize];

  memcpy(resizedArr, m_elements, (sizeof(T*) * _givenIndex));
  resizedArr[_givenIndex + 1] = (T*)_newElement;
  memcpy((resizedArr +_givenIndex + 2), (m_elements +_givenIndex + 1), (sizeof(T*) * (largerSize - _givenIndex - 1)));

  m_elements = resizedArr;

  Container_t<T>::increaseNumElements();
  m_currentSize = largerSize;
  return TRUE;
}

/* -------------------------------------------------------------- */

template<class T>
bool Array_t<T>::prepend(const T* _newElement, int _givenIndex)
{
  return _givenIndex > 0 ? append(_newElement, _givenIndex - 1) : FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
size_t Array_t<T>::index(T& _element)
{
  int n = Container_t<T>::count();

  for (int i = 0; i < n; ++i)
  {
    if(m_elements[i] == &_element)
    {
      return i;
    }
  }
  return FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
bool Array_t<T>::contains(T& _element)
{
  return (index(_element)) ? TRUE : FALSE;
}

/* -------------------------------------------------------------- */

template<class T>
T* Array_t<T>::find(const T& _value)
{
  int i;
  int numElements = Container_t<T>::count();

  for (i = 0; i < numElements; ++i)
  {
    if(m_elements[i] == &_value)
    {
      return m_elements[i];
    }
  }
  throw TException_t<int>(__FILE__, __LINE__, _value, "Not found");
}

/* -------------------------------------------------------------- */

template<class T>
bool Array_t<T>::insert(const T* _newElement)
{
  int setIndex = (Container_t<T>::count() > 0) ? Container_t<T>::count() - 1 : 0;
  int retVal = append(_newElement, setIndex); //append to the end
  return retVal;
}

/* -------------------------------------------------------------- */

template<class T>
bool Array_t<T>::remove(T* _oldElement, T _value)
{
  int foundIndex = index(*_oldElement);

  if(foundIndex >= 0)
  {
    memcpy(m_elements + foundIndex, m_elements + foundIndex + 1, sizeof(Container_t<T>::count() - foundIndex));
    Container_t<T>::decreaseNumElements();
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/* -------------------------------------------------------------- */

template<class T>
void Array_t<T>::removeAll()
{
  int i;
  T* value;
  for (i = 0; i < Container_t<T>::count(); ++i)
  {
    remove(m_elements[i], *value);
  }
}

/* -------------------------------------------------------------- */

template<class T>
void Array_t<T>::removeAndDelete(const T* _oldElement)
{
  int i;
  //T* value;
  for (i = 0; i < Container_t<T>::count(); ++i)
  {
    if(m_elements[i] == _oldElement)
    {
      //remove(m_elements[i], *value);
      delete m_elements[i];
      Container_t<T>::decreaseNumElements();
      return;
    }
  }
  return;
}

/* -------------------------------------------------------------- */

template<class T>
void Array_t<T>::removeAndDeleteAll()
{
  T* value;
  int i;
  for (i = 0; i < Container_t<T>::count(); ++i)
  {
    if (&m_elements[i])
    {
      remove(m_elements[i], *value);
    }

    delete m_elements[i];
  }
  Container_t<T>::setIncomingNumElements(0);
}

#endif /* __ARRAY_H__ */
