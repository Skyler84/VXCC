/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Statements/DeclarationStatement.hpp"
#include "Common/Assert.hpp"

using namespace AST;

void DeclarationStatement::dump(std::ostream &stream, size_t indent,
                                size_t step) const {
  stream << std::string(indent, ' ') << "DeclarationStatement:\n";
  m_decl->dump(stream, indent + step, step);
}
