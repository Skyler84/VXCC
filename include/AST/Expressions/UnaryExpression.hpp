/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Expressions/Expression.hpp"
#include <memory>

namespace AST {
/**
 * @class UnaryExpression
 * Represents a unary expression such as ++ -- & * + - ~ !
 */
class UnaryExpression : public Expression {
public:
  enum class Op {
    Increment,
    Decrement,
    AddrOf,
    Deref,
    SignPlus,
    SignMinus,
    Compl,
    Not,
  };
  /**
   * Construct a Unary expression from rhs using op
   */
  UnaryExpression(std::unique_ptr<Expression> &&rhs, Op op)
      : m_rhs{std::move(rhs)}, m_op{op} {}
  bool isAssignment() const;
  bool isCompoundAssignment() const;
  void getOp() const;
  Expression &rhs();             /**<gets a reference to the LHS expression*/
  const Expression &rhs() const; /**<gets a reference to the LHS expression*/

private:
  std::unique_ptr<Expression> m_rhs;
  Op m_op;
};
} // namespace AST
