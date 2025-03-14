#if !defined(HINST_SET_HPP)
#define HINST_SET_HPP

#include "header.hpp"

typedef enum
{
  ADD,
  POP, /* pop to register */
  HALT,

  MOV_rv, /* mov to register, a constant value */
  MOV_rr, /* mov to register, a value in a register */
  MOV_dv, /* mov to data section, a constant value */
  MOV_dr, /* mov to data section, a value in a register */

  PUSH_v, /* push constant to stack */
  PUSH_r, /* push data in a register to stack */
  PUSH_d, /* push byte in data segment to stack */

  SYSCALL,
  NUM_OF_INSTS
} InstructionSet;

#define MOV ((InstructionSet)MOV_rv)
#define PUSH ((InstructionSet)PUSH_v)

#endif // HINST_SET_HPP
