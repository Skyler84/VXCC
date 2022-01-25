/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Declarators/DeclaratorId.hpp"

using namespace AST;
void DeclaratorId::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "DeclaratorId: " << m_ident << '\n';
}
