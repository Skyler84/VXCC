/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Initializer.hpp"
#include "AST/Expressions/Expression.hpp"
#include "Common/Assert.hpp"

using namespace AST;

Initializer::Initializer(std::unique_ptr<Expression> &&expr)
    : m_type{InitializerType::Expression}, m_expr{std::move(expr)} {}
Initializer::Initializer(std::unique_ptr<InitializerList> &&init_list)
    : m_type{InitializerType::InitializerList}, m_init_list{
                                                    std::move(init_list)} {}
Initializer::~Initializer() { UNIMPLEMENTED(); }

void Initializer::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "Initializer: \n";
  switch (m_type) {
  case InitializerType::Expression:
    m_expr->dump(stream, indent + step, step);
    return;
  case InitializerType::InitializerList:
    m_init_list->dump(stream, indent + step, step);
    return;
  default:
    UNREACHABLE();
  }
}
