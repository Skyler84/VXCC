/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "Lexer/CLexer.hpp"
#include "Common/Assert.hpp"
#include "Lexer/CToken.hpp"

#include <algorithm>
#include <set>

bool CLexer::isIdentFirstChar(char c) {
  if (c >= 'a' && c <= 'z')
    return true;
  if (c >= 'A' && c <= 'Z')
    return true;
  if (c == '_' || c == '$')
    return true;
  return false;
}
bool CLexer::isIdentChar(char c) {
  if (isIdentFirstChar(c))
    return true;
  if (c >= '0' && c <= '9')
    return true;
  return false;
}
bool CLexer::isWhitespace(char c) {
  const static std::set<char> ws{' ', '\r', '\n', '\t', '\v'};
  if (ws.contains(c))
    return true;
  return false;
}
bool CLexer::matchesPunctuator(const std::string &str) {
  if (CToken::punctuators().contains(str))
    return true;
  return false;
}

bool CLexer::isDigit(char c) {
  if(c >= '0' && c <= '9')
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
        } else if(isDigit(c)){
          type = CToken::Type::Constant;
          token += c;
        } else {
          // invalid token
          return false;
        }
        break;
      }
      case CToken::Type::Constant: {
        if(isDigit(c)){
          token += c;
          continue;
        }
        tokens().emplace_back(std::make_unique<CToken>(type, std::move(token)));
        type = CToken::Type::None;
        break;
      }
      case CToken::Type::Identifier: {
        if (isIdentChar(c)) {
          token += c;
          continue;
        }
        if (CToken::keywords().contains(token))
          type = CToken::Type::Keyword;
        tokens().emplace_back(std::make_unique<CToken>(type, std::move(token)));
        type = CToken::Type::None;
        break;
      }
      case CToken::Type::Punctuator: {
        token += c;
        if (matchesPunctuator(token))
          continue;
        if (token == "..") // Explicit case where token is between two
                           // punctuators - . ...
          continue;
        token.pop_back();
        if (token == "..") // Explicit case where token is between two
                           // punctuators - . ...
          return false;
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
