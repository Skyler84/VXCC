/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/AST.hpp"

using namespace AST;

void AstNode::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << typeid(*this).name() << '\n';
  stream << std::string(indent, ' ') << "AstNode::dump() unimplemented\n";
}
