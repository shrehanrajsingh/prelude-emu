#if !defined(HINST_SET_HPP)
#define HINST_SET_HPP

#include "header.hpp"

#define DEFAULT_MOV_BEHAVIOUR 4 /* MOV_rv */

typedef enum
{
  ADD = 0,
  PUSH = 1,
  POP = 2,
  HALT = 3,
  MOV_rv = 4, /* mov to register, a constant value */
  MOV_rr = 5, /* mov to register, a value in a register */
  MOV_dv = 6, /* mov to data section, a constant value */
  MOV_dr = 7, /* mov to data section, a value in a register */

  NUM_OF_INSTS
} InstructionSet;

#define MOV ((InstructionSet)DEFAULT_MOV_BEHAVIOUR)

#endif // HINST_SET_HPP
