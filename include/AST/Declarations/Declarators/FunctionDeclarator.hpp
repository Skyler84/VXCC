/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Declarators/Declarator.hpp"

#include <string>
#include <vector>

namespace AST {
class FunctionDeclarator : public NoptrDeclarator {
public:
  FunctionDeclarator(
      std::unique_ptr<NoptrDeclarator> &&decl,
      std::vector<std::unique_ptr<ParameterDeclaration>> &&params)
      : NoptrDeclarator{NoptrDeclType::FunctionDeclarator},
        m_decl{std::move(decl)}, m_param_decls{std::move(params)} {}
  FunctionDeclarator(std::unique_ptr<NoptrDeclarator> &&decl,
                     std::vector<std::string> &&idents)
      : NoptrDeclarator{NoptrDeclType::FunctionDeclarator},
        m_decl{std::move(decl)}, m_idents{std::move(idents)} {}
  ~FunctionDeclarator(){}
private:
  std::unique_ptr<NoptrDeclarator> m_decl;
  union {
    std::vector<std::unique_ptr<ParameterDeclaration>> m_param_decls;
    std::vector<std::string> m_idents;
  };
  bool variadic{false};
};

} // namespace AST
