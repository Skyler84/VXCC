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

void PtrOperator::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "PtrOperator: ";
  switch(m_op){
    case OpType::Star:
      std::cout << "*\n";
      break;
    case OpType::LRef:
      std::cout << "&\n";
      break;
    case OpType::RRef:
      std::cout << "&&\n";
      break;
  }
  //FIXME: Qualifiers
}

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

void PtrDeclarator::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "PtrDeclarator: \n";
  for (auto &ptr : m_ptrs) {
    ptr.dump(stream, indent + step, step);
  }
  m_decl->dump(stream, indent + step, step);
}
