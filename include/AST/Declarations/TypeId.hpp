/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"
#include "AST/Declarations/DeclSpecifier.hpp"
#include "AST/Declarations/Declarators/Declarator.hpp"

namespace AST {
/**
 * TODO: Change SimpleTypeSpecifier to TypeSpecifier class aaaaa this is hackish
 */
class TypeId final : public AstNode {
public:
  TypeId(std::vector<std::unique_ptr<DeclSpecifier>> &&specs,
         std::unique_ptr<AbstractDeclarator> &&abs_decl)
      : m_specs{std::move(specs)}, m_abs_decl{std::move(abs_decl)} {}

private:
  std::vector<std::unique_ptr<DeclSpecifier>> m_specs;
  std::unique_ptr<AbstractDeclarator> m_abs_decl;
};
} // namespace AST
