#include <prelude.hpp>

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_D 3
#define REG_E 4
#define REG_F 5

int
main (int argc, char const *argv[])
{
  const char prog[] = { PUSH, 5, PUSH, 10, ADD, HALT };
  pl::Module mod{ std::vector<char> (std::begin (prog), std::end (prog)) };

  mod.add_register ("A", REG_TYPE_8);
  mod.add_register ("B", REG_TYPE_8);
  mod.add_register ("C", REG_TYPE_8);
  mod.add_register ("D", REG_TYPE_8);
  mod.add_register ("E", REG_TYPE_8);
  mod.add_register ("F", REG_TYPE_8);

  mod.exec ();

  stack<char> &t = mod.get_stack ();
  while (!t.isEmpty ())
    {
      std::cout << (int)t.pop () << '\n';
    }

  return 0;
}