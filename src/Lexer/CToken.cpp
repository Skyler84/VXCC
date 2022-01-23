/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "Lexer/CToken.hpp"
#include "Common/Assert.hpp"

const std::map<std::string_view, CToken::Keyword> &CToken::keywords() {
  if (!s_keywords) {
    s_keywords = new std::map<std::string_view, CToken::Keyword>{

#define KEYWORD(x)                                                             \
  std::pair<std::string_view, CToken::Keyword>{#x, CToken::Keyword::KW_##x},
        C_KEYWORDS(KEYWORD)
#undef KEYWORDS
    };
  }
  return *s_keywords;
}

const std::map<std::string_view, CToken::Punctuator> &CToken::punctuators() {
  if (!s_punctuators) {
    s_punctuators = new std::map<std::string_view, CToken::Punctuator>{
#define PUNCTUATOR(name, op)                                                   \
  std::pair<std::string_view, CToken::Punctuator>{                             \
      op, CToken::Punctuator::SEQ(FIRST, name)},
        C_PUNCTUATORS(PUNCTUATOR)
#undef PUNCTUATOR
    };
  }
  return *s_punctuators;
};

std::map<std::string_view, CToken::Keyword> *CToken::s_keywords;

std::map<std::string_view, CToken::Punctuator> *CToken::s_punctuators;

CToken::CToken(Type t, std::string &&val) : Token(std::move(val)), m_type{t} {
  VERIFY(m_type != Type::None);
  switch (m_type) {
  case Type::Keyword:
    m_kw = keywords().at(value());
    break;
  case Type::Punctuator:
    m_punc = punctuators().at(value());
    break;
  default:
    break;
  }
}

CToken::Keyword CToken::keyword() const {
  if (m_type == Type::Keyword)
    return m_kw;
  return Keyword::None;
}
CToken::Punctuator CToken::punctuator() const {
  if (m_type == Type::Punctuator)
    return m_punc;
  return Punctuator::None;
}