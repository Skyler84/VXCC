/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/Declarators/PtrDeclarator.hpp"
#include "AST/Declarations/TypeQualifier.hpp"

#include <ostream>
#include <string>

using namespace AST;


PtrOperator::PtrOperator(PtrOperator::OpType op) : PtrOperator{op, {}, {}} {}
PtrOperator::PtrOperator(PtrOperator::OpType op,
                         std::vector<std::unique_ptr<TypeQualifier>> &&ts)
    : PtrOperator{op, {}, std::move(ts)} {}
PtrOperator::PtrOperator(PtrOperator::OpType op,
                         std::vector<std::unique_ptr<AttributeSpecifier>> &&as)
    : PtrOperator{op, std::move(as), {}} {}
PtrOperator::PtrOperator(PtrOperator::OpType op,
                         std::vector<std::unique_ptr<AttributeSpecifier>> &&as,
                         std::vector<std::unique_ptr<TypeQualifier>> &&ts)
    : m_op{op}, m_attrs{std::move(as)}, m_type_quals{std::move(ts)} {}

