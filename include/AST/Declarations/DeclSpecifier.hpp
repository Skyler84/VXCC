/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

namespace AST {
class DeclSpecifier : public AstNode {
public:
  enum class DeclSpecifierType {
    StorageClassSpecifier,
    FunctionSpecifier,
    DefiningTypeSpecifier,
    TypeQualifier,
  };
  DeclSpecifier(DeclSpecifierType type) : m_type{type} {}
  DeclSpecifierType declspecType() const { return m_type; }

private:
  DeclSpecifierType m_type;
};
class FunctionSpecifier final : public DeclSpecifier {
public:
  enum class Specifier {
    Inline,
  };
  FunctionSpecifier(Specifier spec)
      : DeclSpecifier{DeclSpecifierType::FunctionSpecifier}, m_spec{spec} {}
  Specifier spec() const { return m_spec; }

private:
  Specifier m_spec;
};
class StorageClassSpecifier final : public DeclSpecifier {
public:
  enum class Specifier {
    Typedef,
    Extern,
    Static,
    Auto,
    Register,
    ThreadLocal,
    Mutable,
  };
  StorageClassSpecifier(Specifier spec)
      : DeclSpecifier{DeclSpecifierType::StorageClassSpecifier}, m_spec{spec} {}
  Specifier specifier() const { return m_spec; }

private:
  Specifier m_spec;
};
class DefiningTypeSpecifier : public DeclSpecifier {
public:
  enum class DefiningType {
    TypeSpecifier,
    ClassSpecifier,
    EnumSpecifier,
    TypedefSpecifier,
  };
  DefiningTypeSpecifier(DefiningType t)
      : DeclSpecifier{DeclSpecifierType::DefiningTypeSpecifier}, m_type{t} {}
  DefiningType defType() const { return m_type; }

private:
  DefiningType m_type;
};
class SimpleTypeSpecifier : public DefiningTypeSpecifier {
public:
  enum class TypeWord {
    Void,
    Char,
    Char8,
    Char16,
    Char32,
    WChar,
    Short,
    Int,
    Long,
    Float,
    Double,
    Unsigned,
    Signed,
    Bool,
    Complex
  };
  SimpleTypeSpecifier(TypeWord word)
      : DefiningTypeSpecifier{DefiningType::TypeSpecifier}, m_word{word} {}
  TypeWord word() const { return m_word; }

private:
  TypeWord m_word;
};
} // namespace AST
