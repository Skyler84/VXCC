/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/AST.hpp"

using namespace AST;

void AstNode::dump(std::ostream &stream, size_t ident) const {
  stream << std::string(ident, ' ');
  stream << typeid(*this).name() << '\n';
  stream << std::string(ident, ' ') << "AstNode::dump() unimplemented\n";
}
