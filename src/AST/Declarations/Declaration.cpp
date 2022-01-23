/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Declaration.hpp"
#include "AST/Declarations/Declarators/Declarator.hpp"
#include "AST/Declarations/DeclSpecifier.hpp"

using namespace AST;

ParameterDeclaration::ParameterDeclaration(
    std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
    std::unique_ptr<Declarator> &&decl)
    : m_decltype{DeclType::Declarator},
      m_declspecs{std::move(declspecs)}, m_decl{std::move(decl)} {}
ParameterDeclaration::ParameterDeclaration(
    std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
    std::unique_ptr<AbstractDeclarator> &&abs_decl)
    : m_decltype{DeclType::AbstractDeclarator},
      m_declspecs{std::move(declspecs)}, m_abs_decl{std::move(abs_decl)} {}
ParameterDeclaration::~ParameterDeclaration() {}
