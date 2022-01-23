/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/FunctionDefinition.hpp"

using namespace AST;

void FunctionDefinition::dump(std::ostream&stream, size_t ident) const {
  stream << std::string(ident, ' ')
         << "FunctionDefinition:\n";
  for(auto &declspec : m_declspec_seq)
    declspec->dump(stream, ident+2);
  m_decl->dump(stream, ident+2);
  m_body->dump(stream, ident+2);
}

