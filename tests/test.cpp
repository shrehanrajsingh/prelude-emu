#include <prelude.hpp>

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_D 3
#define REG_E 4
#define REG_F 5

const int SHOW_DEBUG_STATS = 0;

#define TO_VEC(X) std::vector<char> (std::begin (X), std::end (X))

int
main (int argc, char const *argv[])
{
  const char s_data[] = "Hello, World!\n";
  /* basic pushing to stack */
  // const char s_text[] = { PUSH, 5, PUSH, 10, ADD, HALT };

  /* syscall routine call */
  // const char s_text[] = { MOV,   REG_A, 1,   MOV,   REG_B, 1,       MOV,
  //                         REG_C, 14,    MOV, REG_D, 0,     SYSCALL, HALT };

  /* basic jump instruction */
  /* in this code, no message will be printed, assume data = "Hello, World!\n"
   */
  const char s_text[] = {
    MOV,         REG_A, 10,    CMP,   REG_A, 10,      JE,   14 /* to HALT */,
    0 /* b-2 */, MOV,   REG_A, 1,     MOV,   REG_B,   1,    MOV,
    REG_C,       14,    MOV,   REG_D, 0,     SYSCALL, HALT,
  };

  /* SJE variant */
  // const char s_text[] = {
  //   MOV, REG_A, 10,    CMP, REG_A,   10,   SJE, 14 /* to HALT */,
  //   MOV, REG_A, 1,     MOV, REG_B,   1,    MOV, REG_C,
  //   14,  MOV,   REG_D, 0,   SYSCALL, HALT,
  // };

  pl::Module mod{ TO_VEC (s_text) };

  mod.add_section_data (TO_VEC (s_data));

  mod.add_register ((char *)"A", REG_TYPE_8);
  mod.add_register ((char *)"B", REG_TYPE_8);
  mod.add_register ((char *)"C", REG_TYPE_8);
  mod.add_register ((char *)"D", REG_TYPE_8);
  mod.add_register ((char *)"E", REG_TYPE_8);
  mod.add_register ((char *)"F", REG_TYPE_8);

  /* Status flags register */
  /**
   * (from MSB)
   * .0 = CF (carry flag)
   * .1 = PF (parity flag)
   * .2 = AF (Auxiliary flag)
   * .3 = ZF (Zero flag)
   * .4 = SF (Sign flag)
   * .5 = OF (OVerflow flag)
   * .6 = Custom
   * .7 = Custom
   */
  mod.add_register ((char *)"SF", REG_TYPE_8);

  try
    {
      mod.exec ();
    }
  catch (const char *e)
    {
      std::cerr << "Error: " << e << '\n';
    }

  if (SHOW_DEBUG_STATS)
    {
      std::cout << "\n[stack]\n";
      stack<char> &t = mod.get_stack ();
      while (!t.isEmpty ())
        {
          std::cout << (int)t.pop () << '\n';
        }

      std::cout << "\n[registers]\n";
      for (pl::Register *r : mod.get_regmap ())
        {
          if (r->get_type () == REG_TYPE_8)
            {
              std::cout << (int)((pl::Register8 *)r)->get_val () << '\n';
            }
          else
            {
              std::cout << (int)((pl::Register16 *)r)->get_val () << '\n';
            }
        }
    }

  return 0;
}