#ifndef __EXCEPTION_HANDLER_H__
#define __EXCEPTION_HANDLER_H__

#include <string>

#define SUCCESS 0
#define FAIL    1

using namespace std;

template <class T>
class TException_t
{
  public:
    TException_t(){};
    TException_t(const string& _file, const size_t& _line, const T& _object, const string& _description);
    ~TException_t(){};
    TException_t(const TException_t<T>& _existingException);
    const TException_t<T>& operator=(const TException_t<T>& _existingException);

    const string  GetFile() const        {return m_file;}
    const size_t  GetLine() const        {return m_line;}
    const string  GetDescription() const {return m_description;}
    const T&      GetObject() const      {return m_object;}

  private:
    string  m_file;
    size_t m_line;
    string m_description;
    T     m_object;
};

/* ------------------------------------- */

template <class T>
TException_t<T>::TException_t(const string& _file, const size_t& _line, const T& _object, const string& _description)
{
  m_file = _file;
  m_line = _line;
  m_description = _description;
  m_object = _object;
}

/* ------------------------------------- */

template <class T>
TException_t<T>::TException_t(const TException_t& _existingException)
{
  m_file = _existingException.m_file;
  m_line = _existingException.m_line;
  m_description = _existingException.m_description;
  m_object = _existingException.m_object;
}

/* ------------------------------------- */

template <class T>
const TException_t<T>& TException_t<T>::operator=(const TException_t<T>& _existingException)
{
  m_file = _existingException.m_file;
  m_line = _existingException.m_line;
  m_description = _existingException.m_description;
  m_object = _existingException.m_object;
  return *this;
}
/* ------------------------------------- */

#endif /* __EXCEPTION_HANDLER_H__ */
