/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "AST/Declarations/DeclSpecifier.hpp"

using namespace AST;

void SimpleTypeSpecifier::dump(std::ostream &stream, size_t indent, size_t step) const {
  stream << std::string(indent, ' ');
  stream << "SimpleTypeSpecifier: ";
  switch(m_word){
    case TypeWord::Void: stream << "Void\n"; break;
    case TypeWord::Char: stream << "Char\n"; break;
    case TypeWord::Char8: stream << "Char8\n"; break;
    case TypeWord::Char16: stream << "Char16\n"; break;
    case TypeWord::Char32: stream << "Char32\n"; break;
    case TypeWord::WChar: stream << "WChar\n"; break;
    case TypeWord::Short: stream << "Short\n"; break;
    case TypeWord::Int: stream << "Int\n"; break;
    case TypeWord::Long: stream << "Long\n"; break;
    case TypeWord::Float: stream << "Float\n"; break;
    case TypeWord::Double: stream << "Double\n"; break;
    case TypeWord::Unsigned: stream << "Unsigned\n"; break;
    case TypeWord::Signed: stream << "Signed\n"; break;
    case TypeWord::Bool: stream << "Bool\n"; break;
    case TypeWord::Complex: stream << "Complex\n"; break;
  }
}
