/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/FunctionBody.hpp"
#include "AST/Statements/CompoundStatement.hpp"

using namespace AST;

FunctionBody::FunctionBody(std::unique_ptr<CompoundStatement> &&body)
    : m_type{BodyType::CompoundStatement}, m_body{std::move(body)} {}

