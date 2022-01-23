/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"
#include "AST/Expressions/Expression.hpp"

namespace AST {
class PrimaryExpression : public Expression {
public:
  enum class ExpressionType {
    Identifier,      /**< TODO: Change to IdExpression for C++ */
    ParenExpression, /**< ( expression ) */
    Literal,         /**< String/Char/Number literal constant */
    IntegerLiteral,  /**< integer number literal */
    This,            /**< this keyword (C++) */
  };
  PrimaryExpression(std::unique_ptr<Expression> &&expr)
      : m_type{ExpressionType::ParenExpression}, m_expr{std::move(expr)} {}
  PrimaryExpression(std::string &&ident)
      : m_type{ExpressionType::Identifier}, m_ident{std::move(ident)} {}
  PrimaryExpression(unsigned long integer)
      : m_type{ExpressionType::IntegerLiteral}, m_integer{integer} {}
  ~PrimaryExpression() {}
  ExpressionType type() const { return m_type; }

private:
  ExpressionType m_type;
  union {
    std::unique_ptr<Expression> m_expr;
    std::string m_ident;
    unsigned long m_integer;
  };
};
} // namespace AST
