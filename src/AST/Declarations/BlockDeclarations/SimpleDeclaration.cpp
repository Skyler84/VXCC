/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/BlockDeclarations/SimpleDeclaration.hpp"
#include "AST/Declarations/DeclSpecifier.hpp"
#include "AST/Attribute.hpp"

using namespace AST;


SimpleDeclaration::SimpleDeclaration(
      std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
      std::vector<std::unique_ptr<InitDeclarator>> &&initdecls)
      : BlockDeclaration{}, m_declspecs{std::move(declspecs)}, m_initdecls{std::move(initdecls)} {}

void SimpleDeclaration::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "SimpleDeclaration:\n";
  for(auto &declspec : m_declspecs)
    declspec->dump(stream, indent+step, step);
  for(auto &initdecl : m_initdecls)
    initdecl->dump(stream, indent+step, step);
}
