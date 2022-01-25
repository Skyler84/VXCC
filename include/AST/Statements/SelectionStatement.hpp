/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Expressions/Expression.hpp"
#include "AST/Statements/Statement.hpp"

#include <map>
#include <memory>

namespace AST {
class SelectionStatement final : public Statement {
public:
  enum class SelectionType {
    Switch,
    IfElse,
  };
  SelectionStatement(std::unique_ptr<Expression> &&expr,
                     std::unique_ptr<Statement> &&if_true,
                     std::unique_ptr<Statement> &&if_false = {})
      : Statement{StatementType::SelectionStatement},
        m_seltype{SelectionType::IfElse},
        m_expr(std::move(expr)), m_if_statements{std::move(if_true),
                                                 std::move(if_false)} {}
  ~SelectionStatement() {}

private:
  SelectionType m_seltype;
  std::unique_ptr<Expression> m_expr;
  union {
    struct {
      std::unique_ptr<Statement> m_if_true;
      std::unique_ptr<Statement> m_if_false;
    } m_if_statements;
    std::map<unsigned long, int> m_case_statements;
};
};

} // namespace AST
