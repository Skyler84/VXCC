/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/FunctionBody.hpp"
#include "AST/Statements/CompoundStatement.hpp"

using namespace AST;

FunctionBody::FunctionBody(std::unique_ptr<CompoundStatement> &&body)
    : m_type{BodyType::CompoundStatement}, m_body{std::move(body)} {}

void FunctionBody::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "FunctionBody: ";
  switch (m_type)
  {
  case BodyType::CompoundStatement:
    stream << "CompoundStatement\n";
    m_body->dump(stream, indent+step, step);
    break;
  case BodyType::CompoundStatementWithCtorInitializer:
    stream << "CompoundStatement with Contructor Initializer\n";
    break;
  case BodyType::Default:
    stream << "default\n";
    break;
  case BodyType::Delete:
    stream << "delete\n";
    break;
  }

}