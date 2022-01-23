/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "Lexer/Token.hpp"

#include <istream>
#include <memory>
#include <vector>

class Lexer {
  friend class TokenStream;
public:
  using Container = std::vector<std::unique_ptr<Token>>;
  Lexer(std::istream &stream) : m_input_stream{stream} {}
  virtual bool lex() = 0;
  const Container &ctokens() const { return m_tokens; }

protected:
  Container &tokens() { return m_tokens; }
  std::istream &stream() { return m_input_stream; }

private:
  std::istream &m_input_stream;
  Container m_tokens;
};