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

  CMP_rv, /* compare a value in a register with a constant */

  JE,  /* 2 byte jump if ZF = 1 */
  SJE, /* 1 byte jump if ZF = 1 */

  SYSCALL,
  NUM_OF_INSTS
} InstructionSet;

#define MOV ((InstructionSet)MOV_rv)
#define PUSH ((InstructionSet)PUSH_v)
#define CMP ((InstructionSet)CMP_rv)

#define ARCH_BIG_ENDIAN 0
#define ARCH_LITTLE_ENDIAN 1

#define PL_ARCH ARCH_LITTLE_ENDIAN

enum StatusFlagBits
{
  SF_UD1 = 0b00000001,
  SF_UD2 = 0b00000010,
  SF_OF = 0b00000100,
  SF_SF = 0b00001000,
  SF_ZF = 0b00010000,
  SF_AF = 0b00100000,
  SF_PF = 0b01000000,
  SF_CF = 0b10000000
};

#endif // HINST_SET_HPP
