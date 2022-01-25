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

