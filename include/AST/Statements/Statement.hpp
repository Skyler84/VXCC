/**
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"
#include "AST/Statements/Forward.hpp"

#include <memory>
#include <vector>

//FIXME: outline constructor
#include "AST/Attribute.hpp"

namespace AST {
class Statement : public AstNode {
public:
  enum class StatementType {
    LabeledStatement,
    ExpressionStatement,
    CompoundStatement,
    SelectionStatement,
    IterationStatement,
    JumpStatement,
    DeclarationStatement,
    // TryBlock,
  };
  Statement(StatementType t) : m_type{t} {}
  StatementType type() const { return m_type; }

private:
  StatementType m_type;
  std::vector<std::unique_ptr<AttributeSpecifier>> m_attrs;
  union {
    // std::unique_ptr<LabeledStatement> m_lbl_st;
    // std::unique_ptr<ExpressionStatement> m_expr_st;
    // std::unique_ptr<CompoundStatement> m_comp_st;
    // std::unique_ptr<SelectionStatement> m_sel_st;
    // std::unique_ptr<IterationStatement> m_iter_st;
    // std::unique_ptr<JumpStatement> m_jmp_st;
    // std::unique_ptr<DeclarationStatement> m_decl_st;
    // std::unique_ptr<TryBlock> m_try_blk;
  };
};
} // namespace AST
