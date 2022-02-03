#include "Parser/CParser.hpp"
#include "AST/TopLevelDeclaration.hpp"
#include "AST/TranslationUnit.hpp"
#include "Lexer/CLexer.hpp"
#include "Lexer/CToken.hpp"
#include <gtest/gtest.h>

#include <fstream>
#include <vector>

const std::vector<CToken> source1_toks{
    CToken{CToken::Type::Keyword, std::string{"int"}},
    CToken{CToken::Type::Identifier, std::string{"main"}},
    CToken{CToken::Type::Punctuator, std::string{"("}},
    CToken{CToken::Type::Keyword, std::string{"int"}},
    CToken{CToken::Type::Identifier, std::string{"argc"}},
    CToken{CToken::Type::Punctuator, std::string{","}},
    CToken{CToken::Type::Keyword, std::string{"char"}},
    CToken{CToken::Type::Punctuator, std::string{"*"}},
    CToken{CToken::Type::Punctuator, std::string{"*"}},
    CToken{CToken::Type::Identifier, std::string{"argv"}},
    CToken{CToken::Type::Punctuator, std::string{")"}},
    CToken{CToken::Type::Punctuator, std::string{"{"}},
    CToken{CToken::Type::Identifier, std::string{"argc"}},
    CToken{CToken::Type::Punctuator, std::string{"+="}},
    CToken{CToken::Type::Identifier, std::string{"argc"}},
    CToken{CToken::Type::Punctuator, std::string{";"}},
    CToken{CToken::Type::Keyword, std::string{"return"}},
    CToken{CToken::Type::Identifier, std::string{"argc"}},
    CToken{CToken::Type::Punctuator, std::string{";"}},
    CToken{CToken::Type::Punctuator, std::string{"}"}},
};

TEST(CParserTest, CompundAssign) {
  // testing::internal::CaptureStdout();
  CParser parser{TokenStream{source1_toks}};
  ASSERT_TRUE(parser.parse());
  parser.ast().dump(std::cerr, 0, 2);
}

#define SOURCE_TEST(name, filepath)                                            \
  TEST(CParserTest, name) {                                                    \
    std::ifstream input;                                                       \
    /*execution directory is binary directory - build/test/ vxcc_test*/        \
    input.open(filepath);                                                      \
    ASSERT_TRUE(input.is_open());                                              \
    CLexer lexer{input};                                                       \
    ASSERT_TRUE(lexer.lex());                                                  \
    CParser parser{TokenStream(std::move(lexer))};                             \
    EXPECT_TRUE(parser.parse());                                               \
  }

SOURCE_TEST(test1_simple     , "../test_code/C/test1.c")
SOURCE_TEST(test2_declaration, "../test_code/C/test2.c")
SOURCE_TEST(test3_if_else    , "../test_code/C/test3.c")