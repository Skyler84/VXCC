/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include "AST/Forward.hpp"
#include "Lexer/CToken.hpp"
#include "Parser/Parser.hpp"
#include "AST/TranslationUnit.hpp"

#include <memory>
#include <variant>
#include <vector>

class CParser : public Parser {
public:
  using Parser::Parser;
  ~CParser();
  bool parse() override;
  AST::TranslationUnit &ast();

protected:
  bool global() const { return !m_scope_depth; }
  void enterScope() { m_scope_depth++; }
  void leaveScope() { m_scope_depth; }

private:
  std::unique_ptr<AST::TranslationUnit> m_ast;
  unsigned m_scope_depth{0};

  std::unique_ptr<AST::TranslationUnit> parseTranslationUnit();
  std::unique_ptr<AST::TopLevelDeclaration> parseExternalDeclaration();
  std::unique_ptr<AST::FunctionDefinition> parseFunctionDefinition();
  std::unique_ptr<AST::Declaration> parseDeclaration();
  std::vector<std::unique_ptr<AST::Declaration>> parseDeclarationList();
  std::vector<std::unique_ptr<AST::DeclSpecifier>> parseDeclSpecifiers();
  std::unique_ptr<AST::PtrDeclarator> parseDeclarator();
  std::unique_ptr<AST::PtrAbstractDeclarator> parseAbstractDeclarator();
  std::unique_ptr<AST::CompoundStatement> parseCompoundStatement();
  std::unique_ptr<AST::StorageClassSpecifier> parseStorageClassSpecifier();
  std::unique_ptr<AST::FunctionSpecifier> parseFunctionSpecifier();
  std::unique_ptr<AST::SimpleTypeSpecifier> parseTypeSpecifier();
  std::unique_ptr<AST::TypeQualifier> parseTypeQualifier();
  std::vector<std::unique_ptr<AST::TypeQualifier>> parseTypeQualifiers();
  std::unique_ptr<AST::NoptrDeclarator> parseDirectDeclarator();
  std::unique_ptr<AST::NoptrAbstractDeclarator> parseAbstractDirectDeclarator();
  std::vector<std::unique_ptr<AST::InitDeclarator>> parseInitDeclaratorList();
  std::unique_ptr<AST::Initializer> parseInitializer();
  std::vector<std::unique_ptr<AST::ParameterDeclaration>>
  parseParameterTypeList();
  std::vector<std::string> parseIdentifierList();
  std::unique_ptr<AST::Statement> parseBlockItem();
  std::unique_ptr<AST::Statement> parseStatement();
  std::unique_ptr<AST::SelectionStatement> parseIfStatement();
  std::unique_ptr<AST::SelectionStatement> parseSwitchStatement();
  std::unique_ptr<AST::IterationStatement> parseForStatement();
  std::unique_ptr<AST::IterationStatement> parseWhileStatement();
  std::unique_ptr<AST::IterationStatement> parseDoWhileStatement();
  std::unique_ptr<AST::JumpStatement> parseGotoStatement();
  std::unique_ptr<AST::JumpStatement> parseContinueStatement();
  std::unique_ptr<AST::JumpStatement> parseBreakStatement();
  std::unique_ptr<AST::JumpStatement> parseReturnStatement();
  std::unique_ptr<AST::ExpressionStatement> parseExpressionStatement();
  std::unique_ptr<AST::Expression> parseExpression();
  std::unique_ptr<AST::Expression> parseAssignmentExpression();
  std::unique_ptr<AST::Expression> parseConditionalExpression();
  std::unique_ptr<AST::Expression> parseLogicalOrExpression();
  std::unique_ptr<AST::Expression> parseLogicalAndExpression();
  std::unique_ptr<AST::Expression> parseInclusiveOrExpression();
  std::unique_ptr<AST::Expression> parseExclusiveOrExpression();
  std::unique_ptr<AST::Expression> parseAndExpression();
  std::unique_ptr<AST::Expression> parseEqualityExpression();
  std::unique_ptr<AST::Expression> parseRelationalExpression();
  std::unique_ptr<AST::Expression> parseShiftExpression();
  std::unique_ptr<AST::Expression> parseAdditiveExpression();
  std::unique_ptr<AST::Expression> parseMultiplicativeExpression();
  std::unique_ptr<AST::Expression> parseCastExpression();
  std::unique_ptr<AST::Expression> parseUnaryExpression();
  std::unique_ptr<AST::Expression> parsePostfixExpression();
  std::unique_ptr<AST::Expression> parsePrimaryExpression();
  std::unique_ptr<AST::TypeId> parseTypeName();
  std::vector<std::unique_ptr<AST::DeclSpecifier>>
  parseSpecifierQualifierList();
};