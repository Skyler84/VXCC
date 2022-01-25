/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Declarations/BlockDeclarations/BlockDeclaration.hpp"
#include "AST/Declarations/Declarators/InitDeclarator.hpp"

namespace AST {
class SimpleDeclaration : public BlockDeclaration {
public:
  SimpleDeclaration(
      std::vector<std::unique_ptr<DeclSpecifier>> &&declspecs,
      std::vector<std::unique_ptr<InitDeclarator>> &&initdecls);
  void dump(std::ostream &, size_t indent, size_t step) const override;

private:
  std::vector<std::unique_ptr<AttributeSpecifier>>
      m_attrs; /**< Only applicable to C++
                  (officially) */
  std::vector<std::unique_ptr<DeclSpecifier>> m_declspecs;
  std::vector<std::unique_ptr<InitDeclarator>> m_initdecls;
};
} // namespace AST