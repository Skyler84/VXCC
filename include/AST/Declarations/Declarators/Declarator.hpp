/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"
#include "AST/Declarations/Declarators/NoptrDeclarator.hpp"

namespace AST {
class Declarator : public NoptrDeclarator {
public:
  enum class DeclType {
    PtrDeclarator,
  };
  Declarator(DeclType type)
      : NoptrDeclarator{NoptrDeclType::Declarator}, m_decltype{type} {}
  DeclType declType() const { return m_decltype; }

private:
  DeclType m_decltype;
};

class AbstractDeclarator : public NoptrAbstractDeclarator {
public:
  enum class DeclType {
    PtrDeclarator,
  };
  AbstractDeclarator(DeclType type)
      : NoptrAbstractDeclarator{NoptrDeclType::Declarator}, m_decltype{type} {}
  DeclType declType() const { return m_decltype; }

private:
  DeclType m_decltype;
};
} // namespace AST
