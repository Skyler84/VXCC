add_library(vxcc)

target_sources(vxcc
PRIVATE
  AST/AST.cpp
  AST/TranslationUnit.cpp
  AST/Declarations/Declaration.cpp
  AST/Declarations/FunctionDefinition.cpp
  AST/Declarations/BlockDeclarations/BlockDeclaration.cpp
  AST/Expressions/Expression.cpp
  AST/Expressions/BinaryExpression.cpp
  AST/Expressions/UnaryExpression.cpp
  AST/Expressions/PostfixExpression.cpp
  Lexer/CLexer.cpp
  Lexer/CToken.cpp
  Lexer/TokenStream.cpp
  Parser/Parser.cpp
)

target_include_directories(vxcc
PUBLIC
  ../include/
)