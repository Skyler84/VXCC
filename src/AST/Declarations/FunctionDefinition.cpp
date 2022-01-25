/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/FunctionDefinition.hpp"

using namespace AST;

FunctionDefinition::FunctionDefinition(
    std::vector<std::unique_ptr<AttributeSpecifier>> &&attr_seq,
    std::vector<std::unique_ptr<DeclSpecifier>> &&declspec_seq,
    std::unique_ptr<Declarator> &&decl,
    std::vector<std::unique_ptr<Declaration>> &&declarations,
    std::unique_ptr<FunctionBody> &&body)
    : m_attr_seq{std::move(attr_seq)},
      m_declspec_seq{std::move(declspec_seq)}, m_decl{std::move(decl)},
      m_declarations{std::move(declarations)}, m_body{std::move(body)} {}
FunctionDefinition::FunctionDefinition(
    std::vector<std::unique_ptr<DeclSpecifier>> &&declspec_seq,
    std::unique_ptr<Declarator> &&decl,
    std::vector<std::unique_ptr<Declaration>> &&declarations,
    std::unique_ptr<FunctionBody> &&body)
    : m_declspec_seq{std::move(declspec_seq)}, m_decl{std::move(decl)},
      m_declarations{std::move(declarations)}, m_body{std::move(body)} {}

void FunctionDefinition::dump(std::ostream &stream, size_t indent,
                              size_t step) const {
  stream << std::string(indent, ' ') << "FunctionDefinition:\n";
  for(auto &declspec : m_declspec_seq)
    declspec->dump(stream, indent + step, step);
  m_decl->dump(stream, indent + step, step);
  m_body->dump(stream, indent + step, step);
}
 