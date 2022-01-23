/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Attribute.hpp"
#include "AST/Declarations/Declaration.hpp"
#include "AST/Declarations/Declarators/Declarator.hpp"
#include "AST/Declarations/FunctionBody.hpp"
#include "AST/Declarations/DeclSpecifier.hpp"
#include "AST/Statements/CompoundStatement.hpp"

namespace AST {

class FunctionDefinition : public Declaration {
public:
  FunctionDefinition(
      std::vector<std::unique_ptr<AttributeSpecifier>> &&attr_seq,
      std::vector<std::unique_ptr<DeclSpecifier>> &&declspec_seq,
      std::unique_ptr<Declarator> &&decl,
      std::vector<std::unique_ptr<Declaration>> &&declarations,
      std::unique_ptr<FunctionBody> &&body)
      : m_attr_seq{std::move(attr_seq)},
        m_declspec_seq{std::move(declspec_seq)}, m_decl{std::move(decl)},
        m_declarations{std::move(declarations)}, m_body{std::move(body)} {}

  FunctionDefinition(
      std::vector<std::unique_ptr<DeclSpecifier>> &&declspec_seq,
      std::unique_ptr<Declarator> &&decl,
      std::vector<std::unique_ptr<Declaration>> &&declarations,
      std::unique_ptr<FunctionBody> &&body)
      : m_declspec_seq{std::move(declspec_seq)}, m_decl{std::move(decl)},
        m_declarations{std::move(declarations)}, m_body{std::move(body)} {}

  void dump(std::ostream&, size_t ident) const override;

private:
  std::vector<std::unique_ptr<AttributeSpecifier>> m_attr_seq;
  std::vector<std::unique_ptr<DeclSpecifier>> m_declspec_seq;
  std::unique_ptr<Declarator> m_decl;
  std::vector<std::unique_ptr<Declaration>>
      m_declarations; /** < Only a C thing */
  std::unique_ptr<FunctionBody> m_body;
  // TODO: virt-specifier-seq
  // TODO: requires-clause
};
} // namespace AST
