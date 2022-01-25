/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Declarators/FunctionDeclarator.hpp"
#include "AST/Declarations/Declaration.hpp"

using namespace AST;

FunctionDeclarator::FunctionDeclarator(
    std::unique_ptr<NoptrDeclarator> &&decl,
    std::vector<std::unique_ptr<ParameterDeclaration>> &&params)
    : NoptrDeclarator{NoptrDeclType::FunctionDeclarator},
      m_param_type{ParamType::ParamList}, m_decl{std::move(decl)},
      m_param_decls{std::move(params)} {}
FunctionDeclarator::FunctionDeclarator(std::unique_ptr<NoptrDeclarator> &&decl,
                                       std::vector<std::string> &&idents)
    : NoptrDeclarator{NoptrDeclType::FunctionDeclarator},
      m_param_type{ParamType::IdentList}, m_decl{std::move(decl)},
      m_idents{std::move(idents)} {}
FunctionDeclarator::~FunctionDeclarator() {}

void FunctionDeclarator::dump(std::ostream &stream, size_t indent,
                              size_t step) const {
  stream << std::string(indent, ' ');
  stream << "FunctionDeclarator: \n";
  m_decl->dump(stream, indent + step, step);
  if (m_param_type == ParamType::ParamList) {
    for(auto &param : m_param_decls)
      param->dump(stream, indent+step, step);
  } else {
    for(auto &ident : m_idents)
      stream << std::string(indent+step, ' ') << "Param: " << ident << '\n';
  }
}