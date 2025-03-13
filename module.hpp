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
  stack<char> st;            /* program stack */
  std::vector<char> bss;     /* bss section */
  std::vector<char> data;    /* data section */
  std::vector<char> program; /* program data in chars  (section text)*/

  short pc;                       /* program counter */
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

  inline void
  add_section_data (std::vector<char> &d)
  {
    data = d;
  }

  inline void
  add_section_data (std::vector<char> &&d)
  {
    data = std::move (d);
  }

  inline void
  add_section_bss (std::vector<char> &b)
  {
    bss = b;
  }

  inline void
  add_section_bss (std::vector<char> &&b)
  {
    bss = std::move (b);
  }

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
  void add_register (char *, RegisterType);
  Register *get_register (char *);
  void add_to_register (int, int);

  inline std::vector<Register *> &
  get_regmap ()
  {
    return regmap;
  }

  ~Module () = default;
};

} // namespace pl

#endif // HMODULE_HPP
