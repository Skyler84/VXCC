/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Forward.hpp"
#include <iostream>

namespace AST {
class AstNode {
public:
  virtual void dump(std::ostream &, size_t ident, size_t step) const;

private:
};
} // namespace AST