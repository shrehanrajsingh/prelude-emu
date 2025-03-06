#include <prelude.hpp>

int
main (int argc, char const *argv[])
{
  const int prog[] = { PUSH, 5, PUSH, 10, ADD, HALT };
  pl::Module mod{ std::vector<int> (std::begin (prog), std::end (prog)) };

  mod.exec ();

  stack<int> &t = mod.get_stack ();
  while (!t.isEmpty ())
    {
      std::cout << t.pop () << '\n';
    }

  return 0;
}