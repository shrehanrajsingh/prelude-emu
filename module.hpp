#if !defined(HMODULE_HPP)
#define HMODULE_HPP

#include "header.hpp"
#include "inst_set.hpp"
#include "stack.hpp"

#define DEBUG(X) X

namespace pl
{

class Module
{
private:
  std::vector<int> program;
  int pc;        /* program counter */
  stack<int> st; /* program stack */

public:
  Module () { pc = 0; };
  Module (std::vector<int> &prog) : program (prog) { pc = 0; };
  Module (std::vector<int> &&prog) : program (std::move (prog)) { pc = 0; }

  Module (Module &rhs)
  {
    program = rhs.program;
    pc = rhs.pc;
  }

  Module &operator= (Module &);
  Module &operator= (Module &&);

  inline std::vector<int> &
  get_prog ()
  {
    return program;
  };

  inline int
  push_prog (int i)
  {
    program.push_back (i);
    return i;
  }

  int
  get_prog_top ()
  {
    if (!program.size ())
      return NUM_OF_INSTS;
    return program.back ();
  }

  int
  get_prog_pc ()
  {
    if (pc >= program.size ())
      return -1;
    return program[pc];
  }

  inline int
  get_pc ()
  {
    return pc;
  }

  inline void
  set_pc (int i)
  {
    pc = i;
  }

  inline int
  fetch ()
  {
    int c = get_prog_pc ();

    if (c == -1)
      return c;

    set_pc (get_pc () + 1);
    return c;
  }

  friend void swap (Module &, Module &) noexcept;

  void exec ();

  stack<int> &
  get_stack ()
  {
    return st;
  }

  ~Module () = default;
};

} // namespace pl

#endif // HMODULE_HPP
