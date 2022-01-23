/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"

namespace AST {
class SelectionStatement final : public Statement {
public:
  SelectionStatement()
      : Statement{StatementType::SelectionStatement} {}

private:
};
} // namespace AST
