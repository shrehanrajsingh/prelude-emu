#if !defined(HREGISTER_HPP)
#define HREGISTER_HPP

#include "header.hpp"

enum RegisterType
{
  REG_TYPE_8,
  REG_TYPE_16
};

namespace pl
{
class Register
{
protected:
  RegisterType type;
  char *name;
  int id;

public:
  Register () : type (REG_TYPE_8 /* default */) { id = -1; }
  Register (RegisterType _Type) : type (_Type) { id = -1; }
  Register (int _Type) : type ((RegisterType)_Type) { id = -1; }

  void
  set_name (char *_Name)
  {
    name = _Name;
  }

  void
  set_id (int _Id)
  {
    id = _Id;
  }

  inline char *
  get_name ()
  {
    return name;
  }

  inline RegisterType
  get_type ()
  {
    return type;
  }

  inline int
  get_id ()
  {
    return id;
  }

  virtual void set_val (int) = 0;

  ~Register () {}
};

class Register8 : public Register
{
private:
  char val;

public:
  Register8 () : Register (REG_TYPE_8) {}
  Register8 (char _Val) : Register (REG_TYPE_8), val (_Val) {}

  inline char
  get_val () const
  {
    return val;
  }

  inline char &
  get_val ()
  {
    return val;
  }

  void
  set_val (int _Val) override
  {
    val = static_cast<char> (_Val);
  }

  Register8
  add (Register8 &rhs)
  {
    return Register8 (val + rhs.val);
  }

  ~Register8 () {}
};

class Register16 : public Register
{
private:
  short val;

public:
  Register16 () : Register (REG_TYPE_16) {}
  Register16 (short _Val) : Register (REG_TYPE_16), val (_Val) {}

  inline short
  get_val () const
  {
    return val;
  }

  inline short &
  get_val ()
  {
    return val;
  }

  void
  set_val (int _Val) override
  {
    val = static_cast<short> (_Val);
  }

  Register16
  add (Register16 &rhs)
  {
    return Register16 (val + rhs.val);
  }

  ~Register16 () {}
};

} // namespace pl

#endif // HREGISTER_HPP
