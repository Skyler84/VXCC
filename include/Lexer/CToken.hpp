/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "Token.hpp"

#include "Common/Macros.hpp"

#include <map>

#define C_KEYWORDS(o)                                                          \
    o(auto)           \
    o(break)          \
    o(case)           \
    o(char)           \
    o(const)          \
    o(continue)       \
    o(default)        \
    o(do)             \
    o(double)         \
    o(else)           \
    o(enum)           \
    o(extern)         \
    o(float)          \
    o(for)            \
    o(goto)           \
    o(if)             \
    o(inline)         \
    o(int)            \
    o(long)           \
    o(register)       \
    o(restrict)       \
    o(return)         \
    o(short)          \
    o(signed)         \
    o(sizeof)         \
    o(static)         \
    o(struct)         \
    o(switch)         \
    o(typedef)        \
    o(union)          \
    o(unsigned)       \
    o(void)           \
    o(volatile)       \
    o(while)          \
    o(_Bool)          \
    o(_Complex)       \
    o(_Imaginary)

#define C_OPERATORS(o)\
    o((Plus           ), "+")\
    o((Minus          ), "-")\
    o((Increment      ), "++")\
    o((Decrement      ), "--")\
    o((Assign         ), "=")\
    o((Mul, Star      ), "*")\
    o((Div            ), "/")\
    o((Mod            ), "%")\
    o((BOr            ), "|")\
    o((Ampersand, BAnd), "&")\
    o((LOr            ), "||")\
    o((LAnd           ), "&&")\
    o((Xor            ), "^")\
    o((Not            ), "!")\
    o((Compl, Tilde   ), "~")\
    o((PlusAssign     ), "+=")\
    o((MinusAssign    ), "-=")\
    o((Equal          ), "==")\
    o((NotEqual       ), "!=")\
    o((LT             ), "<")\
    o((GT             ), ">")\
    o((LTEq           ), "<=")\
    o((GTEq           ), ">=")\
    o((MulAssign      ), "*=")\
    o((DivAssign      ), "/=")\
    o((ModAssign      ), "%=")\
    o((OrAssign       ), "|=")\
    o((AndAssign      ), "&=")\
    o((XorAssign      ), "^=")\
    o((LShift         ), "<<")\
    o((RShift         ), ">>")\
    o((LShiftAssign   ), "<<=")\
    o((RShiftAssign   ), ">>=")\
    o((Ternary        ), "?")\
    o((Colon          ), ":")\
    o((Comma          ), ",")\
    o((Dot            ), ".")\
    o((Pointer        ), "->")

#define C_PUNCTUATION(o)\
    o((LParen    ), "(")\
    o((RParen    ), ")")\
    o((LBracket  ), "[")\
    o((RBracket  ), "]")\
    o((LBrace    ), "{")\
    o((RBrace    ), "}")\
    o((Semicolon ), ";")\

#define C_PUNCTUATORS(o)\
    C_PUNCTUATION(o)    \
    C_OPERATORS(o)      \

class CToken final : public Token {
public:
  enum class Type {
    None,
    Keyword,
    Identifier,
    Constant,
    StringLiteral,
    Punctuator,
  };
  CToken(Type t, std::string &&val);
  virtual std::unique_ptr<Token> copy() const override {
    return _copy<CToken>();
  }

  enum class Keyword {
    None,
#define KEYWORD(x) ALIASES_RCONCAT((x), KW_)
    C_KEYWORDS(KEYWORD)
#undef KEYWORD
  };
  enum class Punctuator {
    None,
#define PUNC(aliases, op) ALIASES_NOMOD(aliases)
    C_PUNCTUATORS(PUNC)
#undef PUNC
  };

  Type type() const { return m_type; }
  Keyword keyword() const;
  Punctuator punctuator() const;

  static const std::map<std::string_view, CToken::Keyword> &keywords();
  static const std::map<std::string_view, CToken::Punctuator> &punctuators();

private:
  Type m_type;
  union{
    Keyword m_kw;
    Punctuator m_punc;
  };
  static std::map<std::string_view, CToken::Keyword> *s_keywords;
  static std::map<std::string_view, CToken::Punctuator> *s_punctuators;
};