/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Forward.hpp"
#include "AST/TopLevelDeclaration.hpp"
#include <memory>
#include <vector>

namespace AST {
class Declaration : public TopLevelDeclaration {
public:
  enum class Type {
    BlockDeclaration,

  };

private:
  union {};
};

class AbstractDeclaration : public AstNode {
public:
private:
  union {};
};

class ParameterDeclaration : public AstNode {
public:
  enum class DeclType {
    Declarator,
    DeclaratorInitialized,
    AbstractDeclarator,
    AbstractDeclaratorInitialized,
  };
  ParameterDeclaration(std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
                       std::unique_ptr<Declarator> &&decl);
  ParameterDeclaration(std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
                       std::unique_ptr<AbstractDeclarator> &&abs_decl);
  ~ParameterDeclaration();
  DeclType declType() const { return m_decltype; }
  void dump(std::ostream&, size_t indent, size_t step) const override;
private:
  DeclType m_decltype;
  std::vector<std::unique_ptr<DeclSpecifier>> m_declspecs;
  union {
    std::unique_ptr<Declarator> m_decl;
    std::unique_ptr<AbstractDeclarator> m_abs_decl;
  };
  // initializer
};
} // namespace AST
