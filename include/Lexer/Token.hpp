/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include <string>
#include <string_view>
#include <utility>

class Token {
public:
  Token(std::string &&value) : m_value{std::move(value)}, m_original{m_value} {}
  virtual ~Token(){};
  std::string_view filename() const { return m_filename; }
  unsigned lineNo() const { return m_line; }
  unsigned colNo() const { return m_col; }
  std::string_view value() const { return m_value; }

private:
  std::string_view m_filename;
  unsigned m_line;
  unsigned m_col;
  std::string m_value;
  std::string m_original;
};
