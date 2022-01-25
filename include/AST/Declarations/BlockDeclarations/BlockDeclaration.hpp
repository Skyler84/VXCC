/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/Declaration.hpp"

namespace AST {
class BlockDeclaration : public Declaration {
public:
  enum class BlockDeclType{
    SimpleDeclaration,
  };
private:
};
} // namespace AST