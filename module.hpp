#if !defined(HMODULE_HPP)
#define HMODULE_HPP

#include "header.hpp"
#include "inst_set.hpp"
#include "register.hpp"
#include "stack.hpp"

#define DEBUG(X) X

namespace pl
{

class Module
{
private:
  std::vector<char> program;      /* program data in chars */
  short pc;                       /* program counter */
  stack<char> st;                 /* program stack */
  std::vector<Register *> regmap; /* registers */

public:
  Module () { pc = 0; };
  Module (std::vector<char> &prog) : program (prog) { pc = 0; };
  Module (std::vector<char> &&prog) : program (std::move (prog)) { pc = 0; }

  Module (Module &rhs)
  {
    program = rhs.program;
    pc = rhs.pc;
  }

  Module &operator= (Module &);
  Module &operator= (Module &&);

  inline std::vector<char> &
  get_prog ()
  {
    return program;
  };

  inline char
  push_prog (char i)
  {
    program.push_back (i);
    return i;
  }

  char
  get_prog_top ()
  {
    if (!program.size ())
      return NUM_OF_INSTS;
    return program.back ();
  }

  char
  get_prog_pc ()
  {
    if (pc >= program.size ())
      return -1;
    return program[pc];
  }

  inline short
  get_pc ()
  {
    return pc;
  }

  inline void
  set_pc (short i)
  {
    pc = i;
  }

  inline char
  fetch ()
  {
    char c = get_prog_pc ();

    if (c == -1)
      return c;

    set_pc (get_pc () + 1);
    return c;
  }

  friend void swap (Module &, Module &) noexcept;

  void exec ();

  stack<char> &
  get_stack ()
  {
    return st;
  }

  /* register routines */
  void
  add_register (char *_Name, RegisterType _Type)
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

  ~Module () = default;
};

} // namespace pl

#endif // HMODULE_HPP
