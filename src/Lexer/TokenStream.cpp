/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "Lexer/TokenStream.hpp"
#include "Common/Assert.hpp"

void TokenStream::consumeToken() {
  VERIFY(!atEnd());
  ++m_cur_pos;
}

void TokenStream::setPos(TokenStreamIterator it) {
  VERIFY(it <= m_tokens.end() && it >= m_tokens.begin());
  m_cur_pos = it;
}