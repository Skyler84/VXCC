/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "BlockDeclarations/Forward.hpp"
#include "Declarators/Forward.hpp"

namespace AST {
class Declaration;
// nodeclspec-function-declaration
class FunctionDefinition;
class FunctionBody;
// template-declaration
// deduction-guide
// explicit-instantiation
// explicit-specialization
// export-declaration
// linkage-specification
// namespace-definition
// empty-declaration
// attribute-declaration
// module-import-declaration
class ParameterDeclaration;

class DeclSpecifier;
class DefiningTypeSpecifier;
class TypeQualifier;
class FunctionSpecifier;
class StorageClassSpecifier;
class TypeSpecifier;
class SimpleTypeSpecifier;

class Initializer;
class InitializerList;

class TypeId;

} // namespace AST
