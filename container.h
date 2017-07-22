#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stdlib.h>
#include "exception_handler.h"

template<class T>
class Container_t : public TException_t<T>
{
  public:
    Container_t(){m_numOfElements = 0;};
    virtual ~Container_t() {};

    Container_t(const Container_t<T>& _incContainer) {m_numOfElements = _incContainer.m_numOfElements;};
    const Container_t<T>& operator=(const Container_t<T>& _incContainer) {m_numOfElements = _incContainer.m_numOfElements; return *this;};

    size_t count() const {return m_numOfElements;}
    bool   isEmpty() const {return m_numOfElements == 0;}

    virtual bool   append(const T* _newElement, int _givenIndex) = 0;
    virtual bool   prepend(const T* _newElement, int _givenIndex) = 0;

    virtual bool   contains(T& _oldElement) = 0;
    virtual T* find(const T& _value) = 0;
    virtual size_t index(T& _oldElement) = 0;
    virtual bool   insert(const T* _newElement) = 0;

    virtual bool   remove(T* _oldElement, T _value) = 0;
    virtual void   removeAll() = 0;
    virtual void   removeAndDelete(const T* _oldElement) = 0;
    virtual void   removeAndDeleteAll() = 0;

  protected:
    void increaseNumElements() {m_numOfElements++;}
    void decreaseNumElements() {m_numOfElements--;}
    void setIncomingNumElements(size_t _newNum) {m_numOfElements = _newNum;}

  private:
    static size_t m_numOfElements;
};

template<class T>
size_t Container_t<T>::m_numOfElements = 0;

#endif /* __CONTAINER_H__ */
