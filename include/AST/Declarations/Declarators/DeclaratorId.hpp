/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Declarators/NoptrDeclarator.hpp"

namespace AST {
class DeclaratorId : public NoptrDeclarator {
public:
  DeclaratorId() : NoptrDeclarator{NoptrDeclType::DeclaratorId} {}
  DeclaratorId(std::string &&ident)
      : NoptrDeclarator{NoptrDeclType::DeclaratorId}, m_ident{std::move(ident)} {}

  const std::string &ident() const { return m_ident; }

private:
  std::string m_ident;
};
} // namespace AST
