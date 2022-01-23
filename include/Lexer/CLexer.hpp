/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "Lexer/Lexer.hpp"

class CLexer : public Lexer {
public:
  using Lexer::Lexer;
  bool lex() override;

private:
  static bool isIdentFirstChar(char c);
  static bool isIdentChar(char c);
  static bool isWhitespace(char c);
  static bool matchesPunctuator(const std::string &str);
};