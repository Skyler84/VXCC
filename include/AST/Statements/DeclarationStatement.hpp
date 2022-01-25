/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"
#include "AST/Declarations/Declaration.hpp"

namespace AST {
class DeclarationStatement final : public Statement {
public:
  DeclarationStatement(std::unique_ptr<Declaration> &&decl)
      : Statement{StatementType::DeclarationStatement}, m_decl{std::move(decl)} {}

private:
  std::unique_ptr<Declaration> m_decl;
};
} // namespace AST
