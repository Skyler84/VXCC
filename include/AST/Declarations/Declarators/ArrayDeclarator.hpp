/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Declarators/Declarator.hpp"

namespace AST {
class ArrayDeclarator : public NoptrDeclarator {
public:
  ArrayDeclarator() : NoptrDeclarator{Type::ArrayDeclarator} {}

private:
};
} // namespace AST
