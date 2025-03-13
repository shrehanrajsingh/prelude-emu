#include "module.hpp"

namespace pl
{
void
swap (Module &first, Module &second) noexcept
{
  std::swap (first.program, second.program);
}

Module &
Module::operator= (Module &rhs)
{
  Module temp (rhs);
  swap (*this, temp);
  return *this;
}

Module &
Module::operator= (Module &&rhs)
{
  swap (program, rhs.program);
  return *this;
}

void
Module::add_register (char *_Name, RegisterType _Type)
{
  Register *nr = nullptr;

  switch (_Type)
    {
    case REG_TYPE_8:
      {
        Register8 *n8 = new Register8 (0);
        nr = n8;
      }
      break;

    case REG_TYPE_16:
      {
        Register16 *n16 = new Register16 (0);
        nr = n16;
      }
      break;

    default:
      throw "invalid_register_type";
      break;
    }

  nr->set_name (_Name);
  nr->set_id (regmap.size ());

  regmap.push_back (nr);
}

Register *
Module::get_register (char *_Name)
{
  for (Register *r : regmap)
    if (!strcmp (r->get_name (), _Name))
      return r;

  return nullptr;
}

void
Module::exec ()
{
  int i;
  while ((i = fetch ()) != HALT)
    {
      switch (i)
        {
        case MOV:
          {
            int regid = fetch ();
            int val = fetch ();

            add_to_register (regid, val);
          }
          break;
        case ADD:
          {
            int a = st.pop (), b = st.pop ();
            st.push (a + b);
          }
          break;
        case PUSH:
          {
            st.push (fetch ());
          }
          break;
        case POP:
          {
            DEBUG (std::cout << st.pop ());
          }
          break;

        default:
          std::cout << i << '\n';
          throw "invalid_instruction";
          break;
        }
    }
}

void
Module::add_to_register (int regid, int val)
{
  /*
    Register ID is same as the index it appears
    in regmap
  */
  if (regid < 0 || regid >= regmap.size ())
    throw "regid_out_of_bounds";

  regmap[regid]->set_val (val);
}
} // namespace pl
