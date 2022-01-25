/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"
#include "AST/TopLevelDeclaration.hpp"
#include <memory>
#include <vector>

class AST::TranslationUnit : public AstNode {
public:
  void dump(std::ostream &stream, size_t indent, size_t step) const override;
  void add(std::unique_ptr<TopLevelDeclaration> &&decl) {
    m_declarations.emplace_back(std::move(decl));
  }

private:
  std::vector<std::unique_ptr<TopLevelDeclaration>> m_declarations;
};