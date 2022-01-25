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

