#if !defined(HSTACK_HPP)
#define HSTACK_HPP

#include "header.hpp"

#define STACK_CAPACITY 256

template <typename T> class stack
{
private:
  T *values;
  size_t len;
  size_t capacity;

public:
  stack ()
  {
    len = 0;
    capacity = STACK_CAPACITY;
    values = new T[capacity];
  };

  stack (T *p, size_t l)
  {
    values = new T[l];
    len = l;
    capacity = ((l / STACK_CAPACITY) + 1) * STACK_CAPACITY;

    for (size_t i = 0; i < len; i++)
      {
        values[i] = p[i];
      }
  }

  stack (stack<T> &rhs)
  {
    len = rhs.len;
    values = new T[len];
    capacity = rhs.capacity;

    for (size_t i = 0; i < len; i++)
      {
        values[i] = rhs.values[i];
      }
  }

  stack<T> &
  operator= (stack<T> &rhs)
  {
    stack<T> temp (rhs);
    std::swap (*this, temp);

    return *this;
  }

  stack<T> &
  operator= (stack<T> &&rhs)
  {
    std::swap (values, rhs.values);
    len = rhs.len;
    capacity = rhs.capacity;

    return *this;
  }

  void
  reserve (size_t s)
  {
    if (s < len)
      return;

    if (s > capacity)
      resize (2 * s + 1);

    len = s;
  }

  void
  resize (size_t c)
  {
    if (c < capacity)
      return;

    capacity = c;

    T *pres = values;
    values = new T[capacity];

    for (size_t i = 0; i < len; i++)
      values[i] = pres[i];

    delete pres;
  }

  inline int
  size ()
  {
    return len;
  }

  bool
  isEmpty ()
  {
    return !len;
  }

  void
  push (T v)
  {
    if (len == capacity)
      resize (capacity * 2 + 1);

    values[len++] = v;
  }

  T
  pop ()
  {
    if (isEmpty ())
      throw "stack_is_empty";

    return values[--len];
  }

  T &
  top ()
  {
    if (isEmpty ())
      throw "stack_is_empty";

    return values[len - 1];
  }

  ~stack () { delete values; }
};

#endif // HSTACK_HPP
