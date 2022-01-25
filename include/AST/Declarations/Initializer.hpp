/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

#include <memory>

namespace AST {

class Initializer final : public AstNode {
public:
  enum class InitializerType {
    Expression,
    InitializerList,
  };
  Initializer(std::unique_ptr<Expression> &&expr);
  Initializer(std::unique_ptr<InitializerList> &&init_list);
  ~Initializer();

private:
  InitializerType m_type;
  union {
    std::unique_ptr<Expression> m_expr;
    std::unique_ptr<InitializerList> m_init_list;
  };
};

class InitializerList : public AstNode {
public:
private:
};
} // namespace AST
