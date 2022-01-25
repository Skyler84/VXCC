/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "Parser/CParser.hpp"
#include "AST/Declarations/BlockDeclarations/SimpleDeclaration.hpp"
#include "AST/Declarations/DeclSpecifier.hpp"
#include "AST/Declarations/Declaration.hpp"
#include "AST/Declarations/Declarators/Declarator.hpp"
#include "AST/Declarations/Declarators/DeclaratorId.hpp"
#include "AST/Declarations/Declarators/FunctionDeclarator.hpp"
#include "AST/Declarations/Declarators/InitDeclarator.hpp"
#include "AST/Declarations/Declarators/NoptrDeclarator.hpp"
#include "AST/Declarations/Declarators/PtrDeclarator.hpp"
#include "AST/Declarations/FunctionDefinition.hpp"
#include "AST/Declarations/Initializer.hpp"
#include "AST/Declarations/TypeId.hpp"
#include "AST/Declarations/TypeQualifier.hpp"
#include "AST/Expressions/BinaryExpression.hpp"
#include "AST/Expressions/Expression.hpp"
#include "AST/Expressions/PrimaryExpression.hpp"
#include "AST/Expressions/UnaryExpression.hpp"
#include "AST/Statements/DeclarationStatement.hpp"
#include "AST/Statements/ExpressionStatement.hpp"
#include "AST/Statements/IterationStatement.hpp"
#include "AST/Statements/JumpStatement.hpp"
#include "AST/Statements/SelectionStatement.hpp"
#include "AST/TopLevelDeclaration.hpp"
#include "AST/TranslationUnit.hpp"
#include "Common/Assert.hpp"

using namespace AST;

CParser::~CParser() {}

bool CParser::parse() {
  m_ast = parseTranslationUnit();
  if (!m_ast)
    return false;
  return true;
}

AST::TranslationUnit &CParser::ast() { return *m_ast; }

std::unique_ptr<TranslationUnit> CParser::parseTranslationUnit() {
  auto tu = std::make_unique<TranslationUnit>();
  while (!toks().atEnd()) {
    if (auto p = parseExternalDeclaration())
      tu->add(std::move(p));
    else
      break;
  }
  if (!toks().atEnd())
    return {};
  return tu;
}

std::unique_ptr<TopLevelDeclaration> CParser::parseExternalDeclaration() {
  if (auto p = parseFunctionDefinition())
    return p;
  if (auto p = parseDeclaration())
    return p;
  return {};
}

std::unique_ptr<FunctionDefinition> CParser::parseFunctionDefinition() {
  /** function-definition:
   *    declaration-specifiers declarator declaration-list(opt)
   * compound-statement
   */
  auto pos = toks().getPos();
  auto specs = parseDeclSpecifiers();
  auto decl = parseDeclarator();
  auto decl_list = parseDeclarationList();
  auto body = parseCompoundStatement();
  if (!(specs.size() && decl && body)) {
    toks().setPos(pos);
    return {};
  }
  return std::make_unique<FunctionDefinition>(
      std::move(specs), std::move(decl), std::move(decl_list),
      std::make_unique<FunctionBody>(std::move(body)));
}

std::unique_ptr<Declaration> CParser::parseDeclaration() {
  auto decl_specs = parseDeclSpecifiers();
  if (!decl_specs.size())
    return {};
  auto init = parseInitDeclaratorList();
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::Semicolon) {
    TODO(Error : Missing semicolon);
  }
  toks().consumeToken();
  return std::make_unique<SimpleDeclaration>(std::move(decl_specs),
                                             std::move(init));
}
std::vector<std::unique_ptr<Declaration>> CParser::parseDeclarationList() {
  std::vector<std::unique_ptr<Declaration>> declarations;
  while (auto decl = parseDeclaration())
    declarations.emplace_back(std::move(decl));
  return declarations;
}

std::vector<std::unique_ptr<DeclSpecifier>> CParser::parseDeclSpecifiers() {
  std::vector<std::unique_ptr<DeclSpecifier>> declspecs;
  while (true) {
    std::unique_ptr<DeclSpecifier> p;
    do {
      if (p = parseStorageClassSpecifier())
        break;
      if (p = parseTypeSpecifier())
        break;
      if (p = parseTypeQualifier())
        break;
      if (p = parseFunctionSpecifier())
        break;
    } while (false);
    if (!p)
      break;
    declspecs.emplace_back(std::move(p));
  }
  return declspecs;
}
std::unique_ptr<PtrDeclarator> CParser::parseDeclarator() {
  /**
   *  declarator:
   *    pointer(opt) direct-declarator
   *  pointer:
   *    * type-qualifier-list(opt) pointer
   */
  std::vector<PtrOperator> ptrs;
  while (true) {
    auto &tok = toks().currentToken<CToken>();
    if (tok.punctuator() != CToken::Punctuator::Star)
      break;
    toks().consumeToken();
    auto ts = parseTypeQualifiers();
    // TODO: check type qualifiers?
    ptrs.emplace_back(PtrOperator::OpType::Star, std::move(ts));
  }
  auto decl = parseDirectDeclarator();
  return std::make_unique<PtrDeclarator>(std::move(ptrs), std::move(decl));
}
std::unique_ptr<PtrAbstractDeclarator> CParser::parseAbstractDeclarator() {
  /**
   *  abstract-declarator:
   *    pointer(opt) direct-abstract-declarator
   *  pointer:
   *    * type-qualifier-list(opt) pointer
   */
  std::vector<PtrOperator> ptrs;
  while (true) {
    auto &tok = toks().currentToken<CToken>();
    if (tok.type() != CToken::Type::Punctuator)
      break;
    if (tok.punctuator() != CToken::Punctuator::Star)
      break;
    toks().consumeToken();
    auto ts = parseTypeQualifiers();
    // TODO: check type qualifiers?
    ptrs.emplace_back(PtrOperator::OpType::Star, std::move(ts));
  }
  auto decl = parseAbstractDirectDeclarator();
  return std::make_unique<PtrAbstractDeclarator>(std::move(ptrs),
                                                 std::move(decl));
}

std::unique_ptr<CompoundStatement> CParser::parseCompoundStatement() {
  if (toks().currentToken<CToken>().punctuator() != CToken::Punctuator::LBrace)
    return {};
  toks().consumeToken();

  std::vector<std::unique_ptr<Statement>> statements;
  while (toks().currentToken<CToken>().punctuator() !=
         CToken::Punctuator::RBrace) {
    if (auto p = parseBlockItem())
      statements.emplace_back(std::move(p));
    else
      break;
    // TODO: Recover from error more gracefully
  }
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::RBrace) {
    TODO(handle missing RBrace error);
  }
  toks().consumeToken();
  return std::make_unique<CompoundStatement>(std::move(statements));
}

std::unique_ptr<SimpleTypeSpecifier> CParser::parseTypeSpecifier() {
  const static std::map<CToken::Keyword, SimpleTypeSpecifier::TypeWord> types{
      {CToken::Keyword::KW_void, SimpleTypeSpecifier::TypeWord::Void},
      {CToken::Keyword::KW_char, SimpleTypeSpecifier::TypeWord::Char},
      {CToken::Keyword::KW_short, SimpleTypeSpecifier::TypeWord::Short},
      {CToken::Keyword::KW_int, SimpleTypeSpecifier::TypeWord::Int},
      {CToken::Keyword::KW_long, SimpleTypeSpecifier::TypeWord::Long},
      {CToken::Keyword::KW_float, SimpleTypeSpecifier::TypeWord::Float},
      {CToken::Keyword::KW_double, SimpleTypeSpecifier::TypeWord::Double},
      {CToken::Keyword::KW_unsigned, SimpleTypeSpecifier::TypeWord::Unsigned},
      {CToken::Keyword::KW_signed, SimpleTypeSpecifier::TypeWord::Signed},
      {CToken::Keyword::KW__Complex, SimpleTypeSpecifier::TypeWord::Complex},
      {CToken::Keyword::KW__Bool, SimpleTypeSpecifier::TypeWord::Bool},
  };
  auto &tok = toks().currentToken<CToken>();
  if (!types.contains(tok.keyword()))
    return {};
  toks().consumeToken();
  return std::make_unique<SimpleTypeSpecifier>(types.at(tok.keyword()));
}
std::unique_ptr<FunctionSpecifier> CParser::parseFunctionSpecifier() {
  const static std::map<CToken::Keyword, FunctionSpecifier::Specifier> specs{
      {CToken::Keyword::KW_inline, FunctionSpecifier::Specifier::Inline},
  };
  auto &tok = toks().currentToken<CToken>();
  if (!specs.contains(tok.keyword()))
    return {};
  toks().consumeToken();
  return std::make_unique<FunctionSpecifier>(specs.at(tok.keyword()));
  return {};
}
std::unique_ptr<StorageClassSpecifier> CParser::parseStorageClassSpecifier() {
  const static std::map<CToken::Keyword, StorageClassSpecifier::Specifier>
      classes{
          {CToken::Keyword::KW_auto, StorageClassSpecifier::Specifier::Auto},
          {CToken::Keyword::KW_extern,
           StorageClassSpecifier::Specifier::Extern},
          {CToken::Keyword::KW_register,
           StorageClassSpecifier::Specifier::Register},
          {CToken::Keyword::KW_static,
           StorageClassSpecifier::Specifier::Static},
          {CToken::Keyword::KW_typedef,
           StorageClassSpecifier::Specifier::Typedef},
      };
  auto &tok = toks().currentToken<CToken>();
  if (!classes.contains(tok.keyword()))
    return {};
  toks().consumeToken();
  return std::make_unique<StorageClassSpecifier>(classes.at(tok.keyword()));
}
std::unique_ptr<TypeQualifier> CParser::parseTypeQualifier() {
  const static std::map<CToken::Keyword, TypeQualifier::Qualifier> quals{
      {CToken::Keyword::KW_const, TypeQualifier::Qualifier::Const},
      {CToken::Keyword::KW_restrict, TypeQualifier::Qualifier::Restrict},
      {CToken::Keyword::KW_volatile, TypeQualifier::Qualifier::Volatile},
  };
  auto &tok = toks().currentToken<CToken>();
  if (!quals.contains(tok.keyword()))
    return {};
  toks().consumeToken();
  return std::make_unique<TypeQualifier>(quals.at(tok.keyword()));
}

std::vector<std::unique_ptr<TypeQualifier>> CParser::parseTypeQualifiers() {
  std::vector<std::unique_ptr<TypeQualifier>> quals;
  while (auto p = parseTypeQualifier())
    quals.emplace_back(std::move(p));
  return quals;
}

std::unique_ptr<NoptrDeclarator> CParser::parseDirectDeclarator() {
  /**
   *  direct-declarator:
   *    identifier
   *    ( declarator )
   *    direct-declarator [ type-qualifier-list(opt)
   *        assignment-expression(opt) ]
   *    direct-declarator [ static type-qualifier-list(opt)
   *        assignment-expression ]
   *    direct-declarator [ type-qualifier-list static assignment-expression ]
   *    direct-declarator [ type-qualifier-list(opt) * ]
   *    direct-declarator ( parameter-type-list )
   *    direct-declarator ( identifier-list(opt) )
   */
  std::unique_ptr<NoptrDeclarator> declarator;
  if (toks().currentToken<CToken>().punctuator() ==
      CToken::Punctuator::LParen) {
    toks().consumeToken();
    declarator = parseDeclarator();
    if (toks().currentToken<CToken>().punctuator() !=
        CToken::Punctuator::RParen) {
      // Eror
      TODO(Error expected RParen);
    } else {
      toks().consumeToken();
    }
  } else if (toks().currentToken<CToken>().type() == CToken::Type::Identifier) {
    declarator = std::make_unique<DeclaratorId>(
        std::string{toks().currentToken().value()});
    toks().consumeToken();
  }
  while (toks().currentToken<CToken>().punctuator() ==
             CToken::Punctuator::LParen ||
         toks().currentToken<CToken>().punctuator() ==
             CToken::Punctuator::LBracket) {
    auto &tok = toks().currentToken<CToken>();
    if (tok.punctuator() == CToken::Punctuator::LParen) {
      toks().consumeToken();
      /**
       *  ( parameter-type-list )
       *  ( identifier-list(opt) )
       */
      if (auto idents = parseIdentifierList(); idents.size()) {
        declarator = std::make_unique<FunctionDeclarator>(std::move(declarator),
                                                          std::move(idents));
      } else {
        auto params = parseParameterTypeList();
        declarator = std::make_unique<FunctionDeclarator>(std::move(declarator),
                                                          std::move(params));
      }
      if (toks().currentToken<CToken>().punctuator() !=
          CToken::Punctuator::RParen) {
        TODO(Handle missing RParen);
      } else {
        toks().consumeToken();
      }
    } else if (tok.punctuator() == CToken::Punctuator::LBracket) {
      toks().consumeToken();
      /**
       *  [ type-qualifier-list(opt) assignment-expression(opt) ]
       *  [ static type-qualifier-list(opt) assignment-expression ]
       *  [ type-qualifier-list static assignment-expression ]
       *  [ type-qualifier-list(opt) * ] (only in function prototype)
       */
      if (toks().currentToken<CToken>().punctuator() ==
          CToken::Punctuator::RBracket) {
        toks().consumeToken();
        continue;
      }
      if (toks().currentToken<CToken>().keyword() ==
          CToken::Keyword::KW_static) {
        TODO(Handle static keyword in array declaration);
      }
      if (auto l = parseTypeQualifiers(); l.size()) {
        TODO(Handle type qualifiers in array declaration);
      }
      if (toks().currentToken<CToken>().punctuator() ==
          CToken::Punctuator::Star) {
        TODO(Handle Star in Array declaration);
      }
      TODO(Parse assignment expression in array declaration);
      if (toks().currentToken<CToken>().punctuator() !=
          CToken::Punctuator::RBracket) {
        TODO(Handle missing RBracket);
      } else {
        toks().consumeToken();
      }
    }
  }
  return declarator;
}

std::unique_ptr<NoptrAbstractDeclarator>
CParser::parseAbstractDirectDeclarator() {
  /**
   *  direct-abstract-declarator:
   *    ( abstract-declarator )
   *    direct-abstract-declarator [ type-qualifier-list(opt)
   *        assignment-expression(opt) ]
   *    direct-abstract-declarator [ static type-qualifier-list(opt)
   *        assignment-expression ]
   *    direct-abstract-declarator [ type-qualifier-list static
   * assignment-expression ] direct-abstract-declarator [
   * type-qualifier-list(opt) * ] direct-abstract-declarator (
   * parameter-type-list ) direct-abstract-declarator ( identifier-list(opt) )
   */
  std::unique_ptr<NoptrAbstractDeclarator> declarator;
  if (toks().currentToken<CToken>().punctuator() ==
      CToken::Punctuator::LParen) {
    toks().consumeToken();
    declarator = parseAbstractDeclarator();
    if (toks().currentToken<CToken>().punctuator() !=
        CToken::Punctuator::RParen) {
      // Error
      TODO(Error expected RParen);
    } else {
      toks().consumeToken();
    }
  }
  while (toks().currentToken<CToken>().punctuator() ==
             CToken::Punctuator::LParen ||
         toks().currentToken<CToken>().punctuator() ==
             CToken::Punctuator::LBracket) {
    auto &tok = toks().currentToken<CToken>();
    if (tok.punctuator() == CToken::Punctuator::LParen) {
      toks().consumeToken();
      /**
       *  ( parameter-type-list )
       *  ( identifier-list(opt) )
       */
      if (auto idents = parseIdentifierList(); idents.size()) {

      } else {
        auto params = parseParameterTypeList();
      }
      TODO(parse abstract function declarator);
      if (toks().currentToken<CToken>().punctuator() !=
          CToken::Punctuator::LParen) {
        TODO(Handle missing LParen);
      } else {
        toks().consumeToken();
      }
    } else if (tok.punctuator() == CToken::Punctuator::LBracket) {
      toks().consumeToken();
      /**
       *  [ type-qualifier-list(opt) assignment-expression(opt) ]
       *  [ static type-qualifier-list(opt) assignment-expression ]
       *  [ type-qualifier-list static assignment-expression ]
       *  [ type-qualifier-list(opt) * ] (only in function prototype)
       */
      if (toks().currentToken<CToken>().keyword() ==
          CToken::Keyword::KW_static) {
        TODO(Handle static keyword in array declaration);
      }
      if (auto l = parseTypeQualifiers(); l.size()) {
        TODO(Handle type qualifiers in array declaration);
      }
      if (toks().currentToken<CToken>().punctuator() ==
          CToken::Punctuator::Star) {
        TODO(Handle Star in Array declaration);
      }
      TODO(Parse assignment expression in array declaration);
      if (toks().currentToken<CToken>().punctuator() !=
          CToken::Punctuator::LBracket) {
        TODO(Handle missing LBracket);
      } else {
        toks().consumeToken();
      }
    }
  }
  return declarator;
}

std::vector<std::unique_ptr<InitDeclarator>>
CParser::parseInitDeclaratorList() {
  std::vector<std::unique_ptr<InitDeclarator>> l;
  do {
    auto decl = parseDeclarator();
    if (!decl && !l.size())
      break;
    else if (l.size()) {
      TODO(Error handling - expected declarator after ',');
    }
    if (toks().currentToken<CToken>().punctuator() ==
        CToken::Punctuator::Assign) {
      toks().consumeToken();
      auto init = parseInitializer();
      if (!init) {
        TODO(Error - expected initializer after '=');
      }
      l.emplace_back(
          std::make_unique<InitDeclarator>(std::move(decl), std::move(init)));
    }
  } while (toks().currentToken<CToken>().punctuator() ==
           CToken::Punctuator::Comma);
  return l;
  UNIMPLEMENTED();
}

std::unique_ptr<Initializer> CParser::parseInitializer() {
  auto expr = parseAssignmentExpression();
  if (!expr)
    return {};
  return std::make_unique<Initializer>(std::move(expr));
}

std::vector<std::unique_ptr<AST::ParameterDeclaration>>
CParser::parseParameterTypeList() {
  /**
   *  parameter-type-list:
   *    parameter-list
   *    parameter-list , ...
   *  parameter-list:
   *    parameter-declaration
   *    parameter-list , parameter-declaration
   *  parameter-declaration:
   *    declaration-specifiers declarator
   *    declaration-specifiers abstract-declarator(opt)
   */
  std::vector<std::unique_ptr<AST::ParameterDeclaration>> decls;
  while (true) {
    auto pos = toks().getPos();
    if (decls.size()) {
      if (toks().currentToken<CToken>().punctuator() ==
          CToken::Punctuator::Comma)
        toks().consumeToken();
      else
        break;
    }
    auto declspecs = parseDeclSpecifiers();
    if (auto pd = parseDeclarator()) {
      auto p = std::make_unique<AST::ParameterDeclaration>(std::move(declspecs),
                                                           std::move(pd));
      decls.emplace_back(std::move(p));
    } else if (auto pa = parseAbstractDeclarator()) {
      auto p = std::make_unique<AST::ParameterDeclaration>(std::move(declspecs),
                                                           std::move(pa));
      decls.emplace_back(std::move(p));
    } else {
      toks().setPos(pos);
      break;
    }
  }
  return decls;
}
std::vector<std::string> CParser::parseIdentifierList() {
  /**
   *  identifier-list:
   *    identifier
   *    identifier-list , identifier
   */
  std::vector<std::string> idents;
  while (true) {
    auto pos = toks().getPos();
    if (idents.size()) {
      if (toks().currentToken<CToken>().punctuator() ==
          CToken::Punctuator::Comma)
        toks().consumeToken();
      else
        break;
    }
    if (toks().currentToken<CToken>().type() == CToken::Type::Identifier) {
      idents.emplace_back(toks().currentToken().value());
      toks().consumeToken();
    } else {
      toks().setPos(pos);
      break;
    }
  }
  return idents;
}

std::unique_ptr<AST::Statement> CParser::parseBlockItem() {
  /**
   *  block-item:
   *    declaration
   *    statement
   */
  if (auto p = parseDeclaration())
    return std::make_unique<DeclarationStatement>(std::move(p));
  if (auto p = parseStatement())
    return p;
  return {};
}
std::unique_ptr<AST::Statement> CParser::parseStatement() {
  /**
   *  statement:
   *    labeled-statement
   *    compound-statement
   *    expression-statement
   *    selection-statement
   *    iteration-statement
   *    jump-statement
   */
  std::unique_ptr<AST::Statement> p;
  auto &tok = toks().currentToken<CToken>();
  if (tok.punctuator() == CToken::Punctuator::LBrace)
    p = parseCompoundStatement();
  else if (tok.keyword() == CToken::Keyword::KW_if)
    p = parseIfStatement();
  else if (tok.keyword() == CToken::Keyword::KW_switch)
    p = parseSwitchStatement();
  else if (tok.keyword() == CToken::Keyword::KW_for)
    p = parseForStatement();
  else if (tok.keyword() == CToken::Keyword::KW_while)
    p = parseWhileStatement();
  else if (tok.keyword() == CToken::Keyword::KW_do)
    p = parseDoWhileStatement();
  else if (tok.keyword() == CToken::Keyword::KW_goto)
    p = parseGotoStatement();
  else if (tok.keyword() == CToken::Keyword::KW_continue)
    p = parseContinueStatement();
  else if (tok.keyword() == CToken::Keyword::KW_break)
    p = parseBreakStatement();
  else if (tok.keyword() == CToken::Keyword::KW_return)
    p = parseReturnStatement();
  else
    p = parseExpressionStatement();
  return p;
}

std::unique_ptr<AST::SelectionStatement> CParser::parseIfStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_if);
  toks().consumeToken();
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::LParen) {
    TODO(Error missing lparen);
  }
  toks().consumeToken();
  auto expr = parseExpression();
  // TODO: Check if type convertible to bool

  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::RParen) {
    TODO(Error missing rparen);
  }
  toks().consumeToken();
  auto st = parseStatement();
  if (!st) {
    TODO(Error expected statement after if);
  }
  if (toks().currentToken<CToken>().keyword() != CToken::Keyword::KW_else) {
    return std::make_unique<SelectionStatement>(std::move(expr), std::move(st));
  }
  toks().consumeToken();
  auto else_st = parseStatement();
  if (!else_st) {
    TODO(error expected statement after else);
  }
  return std::make_unique<SelectionStatement>(std::move(expr), std::move(st),
                                              std::move(else_st));
}

std::unique_ptr<AST::SelectionStatement> CParser::parseSwitchStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_switch);
  UNIMPLEMENTED(switch statement);
  return {};
}

std::unique_ptr<AST::IterationStatement> CParser::parseForStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_for);
  UNIMPLEMENTED(for statement);
  return {};
}

std::unique_ptr<AST::IterationStatement> CParser::parseWhileStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_while);
  UNIMPLEMENTED(while statement);
  return {};
}

std::unique_ptr<AST::IterationStatement> CParser::parseDoWhileStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_do);
  UNIMPLEMENTED(do-while statement);
  return {};
}

std::unique_ptr<AST::JumpStatement> CParser::parseGotoStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_goto);
  UNIMPLEMENTED(goto statement);
  return {};
}

std::unique_ptr<AST::JumpStatement> CParser::parseContinueStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() ==
         CToken::Keyword::KW_continue);
  toks().consumeToken();
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::Semicolon) {
    TODO(handle missing semicolon after continue);
  }
  toks().consumeToken();
  return std::make_unique<JumpStatement>(JumpStatement::JumpType::Continue);
}

std::unique_ptr<AST::JumpStatement> CParser::parseBreakStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_break);
  UNIMPLEMENTED(break statement);
  return {};
}

std::unique_ptr<AST::JumpStatement> CParser::parseReturnStatement() {
  VERIFY(toks().currentToken<CToken>().keyword() == CToken::Keyword::KW_return);
  toks().consumeToken();
  if (toks().currentToken<CToken>().punctuator() ==
      CToken::Punctuator::Semicolon) {
    toks().consumeToken();
    return std::make_unique<JumpStatement>(nullptr);
  }
  auto expr = parseExpression();
  if (!expr) {
    TODO(Expected ';' or expression after return );
  }
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::Semicolon) {
    TODO(Expected ';' after return expression);
  }
  toks().consumeToken();
  return std::make_unique<JumpStatement>(std::move(expr));
  UNIMPLEMENTED();
  return {};
}

std::unique_ptr<AST::ExpressionStatement> CParser::parseExpressionStatement() {
  auto expr = parseExpression();
  if (toks().currentToken<CToken>().punctuator() !=
      CToken::Punctuator::Semicolon) {
    TODO(handle missing semicolon after expression);
  }
  toks().consumeToken();
  return std::make_unique<ExpressionStatement>(std::move(expr));
}

std::unique_ptr<AST::Expression> CParser::parseExpression() {
  std::unique_ptr<AST::Expression> expr = parseAssignmentExpression();
  if (!expr)
    return expr;
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::Comma) {
    toks().consumeToken();
    auto expr2 = parseAssignmentExpression();
    if (!expr2) {
      TODO(handle expected expression after ',');
    }
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(expr2),
                                              BinaryExpression::Op::Comma);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseAssignmentExpression() {
  auto pos = toks().getPos();
  auto lhs = parseUnaryExpression();
  if (!lhs)
    return parseConditionalExpression();
  auto &tok = toks().currentToken<CToken>();
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::Assign, BinaryExpression::Op::Assign},
      {CToken::Punctuator::PlusAssign, BinaryExpression::Op::PlusAssign},
      {CToken::Punctuator::MinusAssign, BinaryExpression::Op::MinusAssign},
      {CToken::Punctuator::MulAssign, BinaryExpression::Op::MulAssign},
      {CToken::Punctuator::DivAssign, BinaryExpression::Op::DivAssign},
      {CToken::Punctuator::ModAssign, BinaryExpression::Op::ModAssign},
      {CToken::Punctuator::LShiftAssign, BinaryExpression::Op::LShiftAssign},
      {CToken::Punctuator::RShiftAssign, BinaryExpression::Op::RShiftAssign},
      {CToken::Punctuator::AndAssign, BinaryExpression::Op::AndAssign},
      {CToken::Punctuator::OrAssign, BinaryExpression::Op::OrAssign},
      {CToken::Punctuator::XorAssign, BinaryExpression::Op::XorAssign},
  };
  if (!ops.contains(tok.punctuator())) {
    // backtrack
    toks().setPos(pos);
    return parseConditionalExpression();
  }
  toks().consumeToken();
  auto rhs = parseAssignmentExpression();
  if (!rhs) {
    TODO(Error expected expression after assignment);
  }
  return std::make_unique<BinaryExpression>(std::move(lhs), std::move(rhs),
                                            ops.at(tok.punctuator()));
}

std::unique_ptr<AST::Expression> CParser::parseConditionalExpression() {
  auto lhs = parseLogicalOrExpression();
  auto &tok = toks().currentToken<CToken>();
  if (tok.punctuator() != CToken::Punctuator::Ternary)
    return lhs;
  toks().consumeToken();
  UNIMPLEMENTED();
}

std::unique_ptr<AST::Expression> CParser::parseLogicalOrExpression() {
  std::unique_ptr<AST::Expression> expr = parseLogicalAndExpression();
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::LOr) {
    toks().consumeToken();
    auto rhs = parseLogicalAndExpression();
    if (!rhs)
      TODO(expected expression after ||);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              BinaryExpression::Op::LOr);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseLogicalAndExpression() {
  std::unique_ptr<AST::Expression> expr = parseInclusiveOrExpression();
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::LAnd) {
    toks().consumeToken();
    auto rhs = parseInclusiveOrExpression();
    if (!rhs)
      TODO(expected expression after &&);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              BinaryExpression::Op::LAnd);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseInclusiveOrExpression() {
  std::unique_ptr<AST::Expression> expr = parseExclusiveOrExpression();
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::BOr) {
    toks().consumeToken();
    auto rhs = parseExclusiveOrExpression();
    if (!rhs)
      TODO(expected expression after |);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              BinaryExpression::Op::BOr);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseExclusiveOrExpression() {
  std::unique_ptr<AST::Expression> expr = parseAndExpression();
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::Xor) {
    toks().consumeToken();
    auto rhs = parseAndExpression();
    if (!rhs)
      TODO(expected expression after ^);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              BinaryExpression::Op::Xor);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseAndExpression() {
  std::unique_ptr<AST::Expression> expr = parseEqualityExpression();
  while (toks().currentToken<CToken>().punctuator() ==
         CToken::Punctuator::BAnd) {
    toks().consumeToken();
    auto rhs = parseEqualityExpression();
    if (!rhs)
      TODO(expected expression after &);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              BinaryExpression::Op::BAnd);
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseEqualityExpression() {
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::Equal, BinaryExpression::Op::Equal},
      {CToken::Punctuator::NotEqual, BinaryExpression::Op::NotEqual},
  };
  std::unique_ptr<AST::Expression> expr = parseRelationalExpression();
  while (ops.contains(toks().currentToken<CToken>().punctuator())) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    auto rhs = parseRelationalExpression();
    if (!rhs)
      TODO(expected expression after == / !=);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              ops.at(tok.punctuator()));
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseRelationalExpression() {
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::LT, BinaryExpression::Op::LessThan},
      {CToken::Punctuator::LTEq, BinaryExpression::Op::LessThanOrEqual},
      {CToken::Punctuator::GT, BinaryExpression::Op::GreaterThan},
      {CToken::Punctuator::GTEq, BinaryExpression::Op::GreaterThanOrEqual},
  };
  std::unique_ptr<AST::Expression> expr = parseShiftExpression();
  while (ops.contains(toks().currentToken<CToken>().punctuator())) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    auto rhs = parseShiftExpression();
    if (!rhs)
      TODO(expected expression after<|> | <= | >=);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              ops.at(tok.punctuator()));
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseShiftExpression() {
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::LShift, BinaryExpression::Op::LShift},
      {CToken::Punctuator::RShift, BinaryExpression::Op::RShift},
  };
  std::unique_ptr<AST::Expression> expr = parseAdditiveExpression();
  while (ops.contains(toks().currentToken<CToken>().punctuator())) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    auto rhs = parseAdditiveExpression();
    if (!rhs)
      TODO(expected expression after << | >>);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              ops.at(tok.punctuator()));
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseAdditiveExpression() {
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::Plus, BinaryExpression::Op::Plus},
      {CToken::Punctuator::Minus, BinaryExpression::Op::Minus},
  };
  std::unique_ptr<AST::Expression> expr = parseMultiplicativeExpression();
  while (ops.contains(toks().currentToken<CToken>().punctuator())) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    auto rhs = parseMultiplicativeExpression();
    if (!rhs)
      TODO(expected expression after + | -);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              ops.at(tok.punctuator()));
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseMultiplicativeExpression() {
  const static std::map<CToken::Punctuator, BinaryExpression::Op> ops{
      {CToken::Punctuator::Mul, BinaryExpression::Op::Mul},
      {CToken::Punctuator::Div, BinaryExpression::Op::Div},
      {CToken::Punctuator::Mod, BinaryExpression::Op::Mod},
  };
  std::unique_ptr<AST::Expression> expr = parseCastExpression();
  while (ops.contains(toks().currentToken<CToken>().punctuator())) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    auto rhs = parseCastExpression();
    if (!rhs)
      TODO(expected expression after * | / | %);
    expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(rhs),
                                              ops.at(tok.punctuator()));
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parseCastExpression() {
  std::unique_ptr<AST::Expression> expr = parseUnaryExpression();
  return expr;
  // FIXME: just check the grammar
  UNIMPLEMENTED();
}

std::unique_ptr<AST::Expression> CParser::parseUnaryExpression() {
  auto &tok = toks().currentToken<CToken>();
  if (tok.punctuator() == CToken::Punctuator::Increment) {
    toks().consumeToken();
    return std::make_unique<UnaryExpression>(parseUnaryExpression(),
                                             UnaryExpression::Op::Increment);
  }
  if (tok.punctuator() == CToken::Punctuator::Decrement) {
    toks().consumeToken();
    return std::make_unique<UnaryExpression>(parseUnaryExpression(),
                                             UnaryExpression::Op::Decrement);
  }
  if (tok.keyword() == CToken::Keyword::KW_sizeof) {
    TODO(Sizeof unimplemented);
  }
  std::map<CToken::Punctuator, UnaryExpression::Op> unaryOps{
      {CToken::Punctuator::Plus, UnaryExpression::Op::SignPlus},
      {CToken::Punctuator::Minus, UnaryExpression::Op::SignMinus},
      {CToken::Punctuator::Star, UnaryExpression::Op::Deref},
      {CToken::Punctuator::Ampersand, UnaryExpression::Op::AddrOf},
      {CToken::Punctuator::Compl, UnaryExpression::Op::Compl},
      {CToken::Punctuator::Not, UnaryExpression::Op::Not},
  };
  if (unaryOps.contains(tok.punctuator())) {
    toks().consumeToken();
    return std::make_unique<UnaryExpression>(parseCastExpression(),
                                             unaryOps.at(tok.punctuator()));
  }
  return parsePostfixExpression();
}

std::unique_ptr<AST::Expression> CParser::parsePostfixExpression() {
  std::unique_ptr<AST::Expression> expr;
  if (toks().currentToken<CToken>().punctuator() ==
      CToken::Punctuator::LParen) {
    auto pos = toks().getPos();
    toks().consumeToken();
    if (auto p = parseTypeName()) {
      TODO(postfix expression
           : (typename) { initializer - list } not supported);

    } else {
      toks().setPos(pos);
    }
  }
  if (!expr)
    expr = parsePrimaryExpression();
  if (!expr)
    return {};
  auto &tok = toks().currentToken<CToken>();
  while (true) {
    if (tok.punctuator() == CToken::Punctuator::LParen) {
      TODO(function call expression);
    }
    if (tok.punctuator() == CToken::Punctuator::LBracket) {
      TODO(Array subscript expression);
    }
    if (tok.punctuator() == CToken::Punctuator::Dot) {
      TODO(Object member expression);
    }
    if (tok.punctuator() == CToken::Punctuator::Pointer) {
      TODO(Pointer member expression);
    }
    if (tok.punctuator() == CToken::Punctuator::Increment) {
      TODO(Postfix increment expression);
    }
    if (tok.punctuator() == CToken::Punctuator::Decrement) {
      TODO(Postfix decrement expression);
    }
    break;
  }
  return expr;
}

std::unique_ptr<AST::Expression> CParser::parsePrimaryExpression() {
  if (toks().currentToken<CToken>().punctuator() ==
      CToken::Punctuator::LParen) {
    toks().consumeToken();
    auto expr = parseExpression();
    if (!expr)
      return {};
    if (toks().currentToken<CToken>().punctuator() !=
        CToken::Punctuator::RParen) {
      TODO(expected RParen after expression);
    }
    toks().consumeToken();
    // FIXME: return a PrimaryExpression?
    return std::make_unique<PrimaryExpression>(std::move(expr));
  }
  if (toks().currentToken<CToken>().type() == CToken::Type::Identifier) {
    std::string ident{toks().currentToken<CToken>().value()};
    toks().consumeToken();
    return std::make_unique<PrimaryExpression>(std::move(ident));
  }
  if (toks().currentToken<CToken>().type() == CToken::Type::Constant) {
    auto &tok = toks().currentToken<CToken>();
    toks().consumeToken();
    std::string val{tok.value()};
    // currently only do decimal
    unsigned long _val = std::stoll(val, nullptr, 0);
    return std::make_unique<PrimaryExpression>(_val);
  }
  UNIMPLEMENTED();
}

std::unique_ptr<AST::TypeId> CParser::parseTypeName() {
  auto specs = parseSpecifierQualifierList();
  if (!specs.size())
    return {};
  auto p = parseAbstractDeclarator();
  return std::make_unique<AST::TypeId>(std::move(specs), std::move(p));
}

std::vector<std::unique_ptr<AST::DeclSpecifier>>
CParser::parseSpecifierQualifierList() {
  std::vector<std::unique_ptr<AST::DeclSpecifier>> spec_quals;
  while (true) {
    if (auto p = parseTypeQualifier()) {
      spec_quals.emplace_back(std::move(p));
      continue;
    }
    if (auto p = parseTypeSpecifier()) {
      spec_quals.emplace_back(std::move(p));
      continue;
    }
    break;
  }
  return spec_quals;
}
