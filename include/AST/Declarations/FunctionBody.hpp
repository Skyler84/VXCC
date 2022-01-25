/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

#include <memory>

namespace AST {

class FunctionBody : public AstNode {
public:
  enum class BodyType {
    CompoundStatement,
    CompoundStatementWithCtorInitializer,
    Default,
    Delete,
  };
  FunctionBody(std::unique_ptr<CompoundStatement> &&body);
  void dump(std::ostream &stream, size_t indent, size_t step) const override;

private:
  BodyType m_type;
  // std::unique_ptr<CtorInitializer> m_init;
  std::unique_ptr<CompoundStatement> m_body;
};
} // namespace AST
