/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Declarators/Declarator.hpp"

#include <memory>
#include <string>
#include <vector>

namespace AST {
class FunctionDeclarator : public NoptrDeclarator {
public:
  enum class ParamType {
    IdentList,
    ParamList,
  };
  FunctionDeclarator(
      std::unique_ptr<NoptrDeclarator> &&decl,
      std::vector<std::unique_ptr<ParameterDeclaration>> &&params);
  FunctionDeclarator(std::unique_ptr<NoptrDeclarator> &&decl,
                     std::vector<std::string> &&idents);
  ~FunctionDeclarator();
  ParamType paramType() const { return m_param_type; }

private:
  std::unique_ptr<NoptrDeclarator> m_decl;
  ParamType m_param_type;
  union {
    std::vector<std::unique_ptr<ParameterDeclaration>> m_param_decls;
    std::vector<std::string> m_idents;
  };
  bool variadic{false};
};

} // namespace AST
