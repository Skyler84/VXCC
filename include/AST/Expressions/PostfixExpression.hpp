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
 * @class PostfixExpression
 * Represents a postfix expression such as [] () . -> ++ --
 */
class PostfixExpression : public Expression {
  struct Op {};

public:
  /**
   * Construct a Postfix expression from lhs using op
   */
  PostfixExpression(std::unique_ptr<Expression> &&lhs, Op op);
  bool isAssignment() const;
  bool isCompoundAssignment() const;
  void getOp() const;
  Expression &lhs();             /**<gets a reference to the LHS expression*/
  const Expression &lhs() const; /**<gets a reference to the LHS expression*/

private:
  std::unique_ptr<Expression> m_lhs;
  Op m_op;
};
} // namespace AST
