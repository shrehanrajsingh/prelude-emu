#include <prelude.hpp>

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_D 3
#define REG_E 4
#define REG_F 5

#define TO_VEC(X) std::vector<char> (std::begin (X), std::end (X))

int
main (int argc, char const *argv[])
{
  const char s_data[] = { '0', '1', '2', '3', '4', 0 };
  // const char s_text[] = { PUSH, 5, PUSH, 10, ADD, HALT };
  const char s_text[] = { MOV, REG_A, 10, MOV, REG_B, 20, HALT };
  pl::Module mod{ TO_VEC (s_text) };

  mod.add_section_data (TO_VEC (s_data));

  mod.add_register ((char *)"A", REG_TYPE_8);
  mod.add_register ((char *)"B", REG_TYPE_8);
  mod.add_register ((char *)"C", REG_TYPE_8);
  mod.add_register ((char *)"D", REG_TYPE_8);
  mod.add_register ((char *)"E", REG_TYPE_8);
  mod.add_register ((char *)"F", REG_TYPE_8);

  mod.exec ();

  stack<char> &t = mod.get_stack ();
  while (!t.isEmpty ())
    {
      std::cout << (int)t.pop () << '\n';
    }

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

  return 0;
}