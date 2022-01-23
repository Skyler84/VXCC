/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "Token.hpp"
#include <memory>
#include <type_traits>
#include <vector>

/**
 * @class TokenStream
 * @brief contains the pre-processed tokens to be iterated over by the Parser
 */
class TokenStream {
  using Container = std::vector<std::unique_ptr<Token>>;

public:
  using TokenStreamIterator = Container::iterator;

  /**
   * @brief Consumes the current token.
   * Asserts that we have not passed end of tokens.
   */
  void consumeToken();

  /**
   * @brief Returns a reference to the current token
   */
  template <class T = Token>
  requires(std::is_base_of_v<Token, T>) T &currentToken() {
    return static_cast<T &>(*m_cur_pos[0]);
  }

  /**
   * @brief Returns a reference to the n+1th token
   */
  template <class T = Token>
  requires(std::is_base_of_v<Token, T>) T &peekToken(int idx = 0) {
    return static_cast<T &>(*m_cur_pos[idx + 1]);
  }

  /**
   * @brief Returns the current token iterator
   */
  TokenStreamIterator getPos() const { return m_cur_pos; }

  /**
   * @brief Sets the current token iterator
   * TODO: Asserts that it is within begin() and end()
   */
  void setPos(TokenStreamIterator it);

  /**
   * @brief Returns count of remaining tokens
   */
  size_t remaining() const { return m_tokens.end() - m_cur_pos; }

  /**
   * @brief Returns true if all tokens consumed
   */
  bool atEnd() const { return !remaining(); }

private:
  Container m_tokens; /**< container of Token(s)*/
  TokenStreamIterator m_cur_pos;
};