/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Statements/CompoundStatement.hpp"

using namespace AST;

CompoundStatement::CompoundStatement(
    std::vector<std::unique_ptr<Statement>> &&statements)
    : Statement{StatementType::CompoundStatement}, m_statements{
                                                       std::move(statements)} {}

