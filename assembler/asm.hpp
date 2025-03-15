#if !defined(HASM_HPP)
#define HASM_HPP

#include "header.hpp"
#include "token.hpp"

namespace pl
{
class AsmContext
{
private:
  std::string raw_input;
  std::vector<Token *> tok_table;

public:
  AsmContext () {}
  ~AsmContext () {}
};
} // namespace pl

#endif // HASM_HPP
