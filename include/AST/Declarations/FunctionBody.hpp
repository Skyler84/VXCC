/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/AST.hpp"

namespace AST {

class FunctionBody : public AstNode {
public:
  enum class BodyType {
    CompoundStatement,
    CompoundStatementWithCtorInitializer,
    Default,
    Delete,
  };
  FunctionBody(std::unique_ptr<CompoundStatement> &&body)
      : m_type{BodyType::CompoundStatement}, m_body{std::move(body)} {}

private:
  BodyType m_type;
  // std::unique_ptr<CtorInitializer> m_init;
  std::unique_ptr<CompoundStatement> m_body;
};
} // namespace AST
