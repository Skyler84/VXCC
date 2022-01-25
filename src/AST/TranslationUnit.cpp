/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/TranslationUnit.hpp"

using namespace AST;

void TranslationUnit::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ')
         << "TranslationUnit:\n";
  for (auto &decl : m_declarations) {
    decl->dump(stream, indent+step, step);
  }
}
