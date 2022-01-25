/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Statements/Statement.hpp"

#include <memory>

namespace AST {
class JumpStatement final : public Statement {
public:
  enum class JumpType {
    Continue,
    Break,
    Return,
    Goto,
  };
  JumpStatement(JumpType t);
  JumpStatement(std::unique_ptr<Expression> &&expr);
  ~JumpStatement();
  void dump(std::ostream &, size_t indent, size_t step) const override;

private:
  JumpType m_type;
  union {
    std::string m_label;
    std::unique_ptr<Expression> m_expr;
  };
};
} // namespace AST
