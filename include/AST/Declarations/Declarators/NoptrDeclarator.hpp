/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

namespace AST {
class NoptrDeclarator : public AstNode {
public:
  enum class NoptrDeclType {
    DeclaratorId,
    FunctionDeclarator,
    ArrayDeclarator,
    Declarator,
  };
  NoptrDeclarator(NoptrDeclType t) : m_type{t} {}
  NoptrDeclType noptrDeclType() const { return m_type; }

private:
  NoptrDeclType m_type;
};
class NoptrAbstractDeclarator : public AstNode {
public:
  enum class NoptrDeclType {
    DeclaratorId,
    FunctionDeclarator,
    ArrayDeclarator,
    Declarator,
  };
  NoptrAbstractDeclarator(NoptrDeclType t) : m_type{t} {}
  NoptrDeclType noptrDeclType() const { return m_type; }

private:
  NoptrDeclType m_type;
};
} // namespace AST
