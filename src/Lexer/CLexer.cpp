/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "Lexer/CLexer.hpp"
#include "Common/Assert.hpp"
#include "Lexer/CToken.hpp"

#include <algorithm>
#include <map>

static std::map<std::string_view, CToken::Keyword> keywords{
#define KEYWORD(x)                                                             \
  std::pair<std::string_view, CToken::Keyword>{#x, CToken::Keyword::KW_##x},
    C_KEYWORDS(KEYWORD)
#undef KEYWORDS
};

static std::map<std::string_view, CToken::Punctuator> punctuators{
#define PUNCTUATOR(name, op)                                                   \
  std::pair<std::string_view, CToken::Punctuator>{                             \
      op, CToken::Punctuator::SEQ(FIRST, name)},
    C_PUNCTUATORS(PUNCTUATOR)
#undef PUNCTUATOR
};

bool isIdentFirstChar(char c) {
  if (c >= 'a' && c <= 'z')
    return true;
  if (c >= 'A' && c <= 'Z')
    return true;
  if (c == '_' || c == '$')
    return true;
  return false;
}
bool isIdentChar(char c) {
  if (isIdentFirstChar(c))
    return true;
  if (c >= '0' && c <= '9')
    return true;
  return false;
}
bool isWhitespace(char c) {
  constexpr static std::string_view ws{" \r\n\t\v"};
  if (std::find(ws.begin(), ws.end(), c) != ws.end())
    return true;
  return false;
}
bool matchesPunctuator(const std::string &str) {
  auto it =
      std::find_if(punctuators.begin(), punctuators.end(),
                   [&](auto &pair) { return pair.first.starts_with(str); });
  if (it != punctuators.end())
    return true;
  return false;
}

bool CLexer::lex() {
  char c;
  std::string token;
  CToken::Type type = CToken::Type::None;
  while ((c = stream().get()) != std::istream::traits_type::eof()) {
    do {
      switch (type) {
      case CToken::Type::None: {
        if (isIdentFirstChar(c)) {
          token += c;
          type = CToken::Type::Identifier;
          continue;
        } else if (matchesPunctuator(std::string{c})) {
          type = CToken::Type::Punctuator;
          token += c;
        } else if (isWhitespace(c)) {
          goto next;
        }
        break;
      }
      case CToken::Type::Identifier: {
        if (isIdentChar(c)) {
          token += c;
          continue;
        }
        auto l = [&](const auto &kv) {
          auto &[key, val] = kv;
          return token == key;
        };
        if (std::find_if(keywords.begin(), keywords.end(), l) != keywords.end())
          type = CToken::Type::Keyword;
        tokens().emplace_back(std::make_unique<CToken>(type, std::move(token)));
        type = CToken::Type::None;
        break;
      }
      case CToken::Type::Punctuator: {
        token += c;
        if (matchesPunctuator(token))
          continue;
        token.pop_back();
        tokens().emplace_back(std::make_unique<CToken>(type, std::move(token)));
        type = CToken::Type::None;
        break;
      }
      default:
        UNREACHABLE(unhandled case);
      }
    } while (type == CToken::Type::None);
  next:;
  }
  return true;
}
