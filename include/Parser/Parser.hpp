/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "Lexer/TokenStream.hpp"

class Parser {
public:
  Parser(TokenStream&&toks) : m_toks{std::move(toks)}{}
  /**
   * @brief Try to parse incoming tokens
   * @returns success indicator
   */
  virtual bool parse() = 0;

protected:
  TokenStream &toks() { return m_toks; }

private:
  TokenStream m_toks;
};