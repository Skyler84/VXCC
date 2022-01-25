/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Expressions/PrimaryExpression.hpp"
#include "Common/Assert.hpp"

using namespace AST;

void PrimaryExpression::dump(std::ostream &stream, size_t indent,
                             size_t step) const {
  stream << std::string(indent, ' ');
  switch (m_type) {
  case ExpressionType::Identifier:
    stream << "Identifier: " << m_ident << "\n";
    return;
  case ExpressionType::IntegerLiteral:
    stream << "Integer: " << m_integer << "\n";
    return;
  case ExpressionType::Literal:
    TODO();
  case ExpressionType::ParenExpression:
    TODO();
  case ExpressionType::This:
    stream << "this\n";
    return;
  default:
    UNREACHABLE();
  }
  UNREACHABLE();
}
