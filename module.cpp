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
Module::exec ()
{
  int i;
  while ((i = fetch ()) != HALT)
    {
      switch (i)
        {
        case MOV:
          {
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
} // namespace pl
