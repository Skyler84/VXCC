/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"

#include <memory>
#include <vector>

namespace AST {
class CompoundStatement final : public Statement {
public:
  CompoundStatement(std::vector<std::unique_ptr<Statement>> &&statements);

private:
  std::vector<std::unique_ptr<Statement>> m_statements;
};
} // namespace AST
