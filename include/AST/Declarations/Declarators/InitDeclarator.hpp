/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

#include <memory>

// FIXME: outline
#include "AST/Declarations/Declarators/Declarator.hpp"
#include "AST/Declarations/Initializer.hpp"

namespace AST {
class InitDeclarator : public AstNode {
public:
  InitDeclarator(std::unique_ptr<Declarator> &&decl,
                 std::unique_ptr<Initializer> &&init)
      : m_decl{std::move(decl)}, m_init{std::move(init)} {}
  void dump(std::ostream &, size_t indent, size_t step) const override;

private:
  std::unique_ptr<Declarator> m_decl;
  std::unique_ptr<Initializer> m_init;
};
} // namespace AST
