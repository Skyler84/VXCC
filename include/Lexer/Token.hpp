/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

class Token {
public:
  Token(std::string &&value) : m_value{std::move(value)}, m_original{m_value} {}
  virtual ~Token(){};
  virtual std::unique_ptr<Token> copy() const = 0;
  std::string_view filename() const { return m_filename; }
  unsigned lineNo() const { return m_line; }
  unsigned colNo() const { return m_col; }
  std::string_view value() const { return m_value; }

protected:
  template <class T>
  requires(std::is_base_of_v<Token, T>) std::unique_ptr<T> _copy()
  const { return std::make_unique<T>(*static_cast<const T *>(this)); }

private:
  std::string_view m_filename;
  unsigned m_line;
  unsigned m_col;
  std::string m_value;
  std::string m_original;
};
