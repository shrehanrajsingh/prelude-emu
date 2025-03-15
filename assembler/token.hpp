#if !defined(HTOKEN_HPP)
#define HTOKEN_HPP

#include "header.hpp"

enum TokenType
{
  TOK_INSTRUCTION = 0,
  TOK_OPERATOR = 1,  /* comma, colon */
  TOK_RAWSTRING = 2, /* .something or any label name */
  TOK_CONSTINT = 3,  /* #[0-9]+ for text section and [0-9]+ for data section */
  TOK_COUNT          /* count number of tokens */
};

namespace pl
{
class Token
{
protected:
  TokenType type;

public:
  Token () { type = TOK_COUNT; }
  Token (TokenType _Type) { type = _Type; }

  ~Token () {}
};

class Tok_Instruction : public Token
{
private:
  char *val;

public:
  Tok_Instruction () : Token (TOK_INSTRUCTION) { val = nullptr; }
  Tok_Instruction (char *_Val) : Token (TOK_INSTRUCTION) { val = _Val; }

  inline char *&
  get_val ()
  {
    return val;
  }

  ~Tok_Instruction () {}
};

class Tok_Operator : public Token
{
private:
  char *val;

public:
  Tok_Operator () : Token (TOK_INSTRUCTION) { val = nullptr; }
  Tok_Operator (char *_Val) : Token (TOK_INSTRUCTION) { val = _Val; }

  inline char *&
  get_val ()
  {
    return val;
  }

  ~Tok_Operator () {}
};

class Tok_RawString : public Token
{
private:
  char *val;

public:
  Tok_RawString () : Token (TOK_RAWSTRING) { val = nullptr; }
  Tok_RawString (char *_Val) : Token (TOK_RAWSTRING) { val = _Val; }

  inline char *&
  get_val ()
  {
    return val;
  }

  ~Tok_RawString () {}
};

class Tok_ConstInt : public Token
{
private:
  char *val;

public:
  Tok_ConstInt () : Token (TOK_CONSTINT) { val = nullptr; }
  Tok_ConstInt (char *_Val) : Token (TOK_CONSTINT) { val = _Val; }

  inline char *&
  get_val ()
  {
    return val;
  }

  ~Tok_ConstInt () {}
};
} // namespace pl

#endif // HTOKEN_HPP
