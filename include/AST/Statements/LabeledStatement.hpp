/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"

namespace AST {
class LabeledStatement final : public Statement {
public:
  LabeledStatement(std::string &&ident, std::unique_ptr<Statement> &&st)
      : Statement{StatementType::LabeledStatement}, m_ident{ident},
        m_statement{std::move(st)} {}

private:
  std::string m_ident;
  std::unique_ptr<Statement> m_statement;
};
} // namespace AST
