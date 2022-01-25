/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Attribute.hpp"
#include "AST/Declarations/Declarators/Declarator.hpp"
#include <memory>
#include <vector>

namespace AST {

class PtrOperator final : public AstNode {
public:
  enum class OpType {
    Star,
    LRef,
    RRef,
  };
  PtrOperator(OpType op);
  PtrOperator(OpType op, std::vector<std::unique_ptr<TypeQualifier>> &&ts);
  PtrOperator(OpType op, std::vector<std::unique_ptr<AttributeSpecifier>> &&as);
  PtrOperator(OpType op, std::vector<std::unique_ptr<AttributeSpecifier>> &&as,
              std::vector<std::unique_ptr<TypeQualifier>> &&ts);
  OpType op() const { return m_op; }

private:
  OpType m_op;
  std::vector<std::unique_ptr<AttributeSpecifier>> m_attrs;
  std::vector<std::unique_ptr<TypeQualifier>> m_type_quals;
};

class PtrDeclarator : public Declarator {
public:
  PtrDeclarator(std::unique_ptr<NoptrDeclarator> &&decl)
      : PtrDeclarator{{}, std::move(decl)} {}
  PtrDeclarator(std::vector<PtrOperator> &&ptrs,
                std::unique_ptr<NoptrDeclarator> &&decl)
      : Declarator{DeclType::PtrDeclarator}, m_ptrs{std::move(ptrs)},
        m_decl{std::move(decl)} {}
  const PtrOperator &ptr(int idx) const { return m_ptrs[idx]; }

private:
  std::vector<PtrOperator> m_ptrs;
  std::unique_ptr<NoptrDeclarator> m_decl;
};

class PtrAbstractDeclarator : public AbstractDeclarator {
public:
  PtrAbstractDeclarator(std::unique_ptr<NoptrAbstractDeclarator> &&decl)
      : PtrAbstractDeclarator{{}, std::move(decl)} {}
  PtrAbstractDeclarator(std::vector<PtrOperator> &&ptrs,
                        std::unique_ptr<NoptrAbstractDeclarator> &&decl)
      : AbstractDeclarator{DeclType::PtrDeclarator}, m_ptrs{std::move(ptrs)},
        m_decl{std::move(decl)} {}
  const PtrOperator &ptr(int idx) const { return m_ptrs[idx]; }

private:
  std::vector<PtrOperator> m_ptrs;
  std::unique_ptr<NoptrAbstractDeclarator> m_decl;
};
} // namespace AST
