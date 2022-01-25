/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Declarators/InitDeclarator.hpp"

using namespace AST;
void InitDeclarator::dump(std::ostream &stream, size_t indent,
                          size_t step) const {
  stream << std::string(indent, ' ');
  stream << "InitDeclarator: \n";
  m_decl->dump(stream, indent + step, step);
  if (m_init)
    m_init->dump(stream, indent + step, step);
}
