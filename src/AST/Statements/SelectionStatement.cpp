/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Statements/SelectionStatement.hpp"

using namespace AST;
void SelectionStatement::dump(std::ostream &stream, size_t indent,
                              size_t step) const {
  stream << std::string(indent, ' ') << "SelectionStatement:\n";
  if (m_seltype == SelectionType::IfElse) {
    stream << std::string(indent + step, ' ') << "If\n";
    m_expr->dump(stream, indent + step * 2, step);
    stream << std::string(indent + step, ' ') << "Then\n";
    m_if_statements.m_if_true->dump(stream, indent + step * 2, step);
    if (m_if_statements.m_if_false)
      stream << std::string(indent + step, ' ') << "Else\n";
    m_if_statements.m_if_false->dump(stream, indent + step * 2, step);
  } else
    stream << "Switch\n";
}
