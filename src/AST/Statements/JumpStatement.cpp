/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Statements/JumpStatement.hpp"
#include "AST/Expressions/Expression.hpp"
#include "Common/Assert.hpp"

using namespace AST;


JumpStatement::JumpStatement(JumpType t)
    : Statement{StatementType::JumpStatement}, m_type{t} {}
JumpStatement::JumpStatement(std::unique_ptr<Expression> &&expr)
    : Statement{StatementType::JumpStatement}, m_type{JumpType::Return},
      m_expr{std::move(expr)} {}
JumpStatement::~JumpStatement() {}

void JumpStatement::dump(std::ostream &stream, size_t indent,
                              size_t step) const {
  stream << std::string(indent, ' ') << "JumpStatement:\n";
  switch(m_type){
    case JumpType::Return:
      stream << std::string(indent+step, ' ') << "Return:\n";
      m_expr->dump(stream, indent+step*2, step);
      return;
    case JumpType::Goto:
      stream << std::string(indent+step, ' ') << "Goto: " << m_label << "'\n";
      return;
    case JumpType::Continue:
      stream << std::string(indent+step, ' ') << "Continue:\n";
      return;
    case JumpType::Break:
      stream << std::string(indent+step, ' ') << "Break:\n";
      return;
    default:
      UNREACHABLE();
  }
}
