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

void CompoundStatement::dump(std::ostream &stream, size_t indent,
                             size_t step) const {
  stream << std::string(indent, ' ') << "CompoundStatement:\n";
  for (auto &st : m_statements)
    st->dump(stream, indent + step, step);
}
