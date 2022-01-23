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
 * @class BinaryExpression
 * Represents a binary expression such as = + - * / % etc
 */
class BinaryExpression : public Expression {
public:
  enum class Op {
    Comma,
    Assign,
    Plus,
    Minus,
    Mul,
    Div,
    Mod,
    LShift,
    RShift,
    LOr,
    LAnd,
    Xor,
    BOr,
    BAnd,
    PlusAssign,
    MinusAssign,
    MulAssign,
    DivAssign,
    ModAssign,
    LShiftAssign,
    RShiftAssign,
    AndAssign,
    OrAssign,
    XorAssign,
    Equal,
    NotEqual,
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
  };
  /**
   * Construct a Binary expression from lhs and rhs using op
   */
  BinaryExpression(std::unique_ptr<Expression> &&lhs,
                   std::unique_ptr<Expression> &&rhs, Op op)
      : m_lhs{std::move(lhs)}, m_rhs{std::move(rhs)}, m_op{op} {}

  bool isAssignment() const;
  bool isCompoundAssignment() const;
  Op getOp() const;
  Expression &lhs();             /**<gets a reference to the LHS expression*/
  const Expression &lhs() const; /**<gets a reference to the LHS expression*/
  Expression &rhs();             /**<gets a reference to the RHS expression*/
  const Expression &rhs() const; /**<gets a reference to the RHS expression*/

private:
  std::unique_ptr<Expression> m_lhs;
  std::unique_ptr<Expression> m_rhs;
  Op m_op;
};
} // namespace AST
