#if !defined(HINST_SET_HPP)
#define HINST_SET_HPP

#include "header.hpp"

typedef enum
{
  MOV = 0,
  ADD = 1,
  PUSH = 2,
  POP = 3,
  HALT = 4,
  NUM_OF_INSTS
} InstructionSet;

#endif // HINST_SET_HPP
