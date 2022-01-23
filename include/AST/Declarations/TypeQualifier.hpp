/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/DeclSpecifier.hpp"

namespace AST {
/**
 * @class TypeQualifier
 * Holds type qualifiers such as:
 *    const
 *    volatile
 *    restrict(c99)
 */
class TypeQualifier final : public DeclSpecifier {
public:
  enum class Qualifier {
    Const,
    Volatile,
    Restrict,
  };
  TypeQualifier(Qualifier qualifier) : DeclSpecifier{DeclSpecifierType::TypeQualifier}, m_qualifier{qualifier} {}
  Qualifier qualifier() const { return m_qualifier; }

private:
  Qualifier m_qualifier;
};
} // namespace AST
