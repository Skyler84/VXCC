/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"

namespace AST {
class ExpressionStatement final : public Statement {
public:
  ExpressionStatement(std::unique_ptr<Expression>&&expr)
      : Statement{StatementType::ExpressionStatement}, m_expr{std::move(expr)} {}

private:
  std::unique_ptr<Expression> m_expr;
};
} // namespace AST
