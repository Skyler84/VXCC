#include "Lexer/CLexer.hpp"
#include "Lexer/CToken.hpp"
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <sstream>

const char *source1_str =
    R"SOURCE(
int main(){
  return;
}
)SOURCE";

TEST(CLexerTest, EmptyMain) {
  // testing::internal::CaptureStdout();
  std::stringstream source_stream{source1_str, std::ios_base::in};
  CLexer lexer{source_stream};
  EXPECT_TRUE(lexer.lex());
  for (const auto &tok : lexer.ctokens())
    std::cout << tok->value() << '\n';
}

const char *source2_str =
    R"SOURCE(
int main(int argc, char *argv[]){
  return argc;
}
)SOURCE";

TEST(CLexerTest, EmptyMainReturnArgc) {
  // testing::internal::CaptureStdout();
  std::stringstream source_stream{source2_str, std::ios_base::in};
  CLexer lexer{source_stream};
  EXPECT_TRUE(lexer.lex());
  for (const auto &tok : lexer.ctokens())
    std::cout << tok->value() << '\n';
}

const char *source3_str =
    R"SOURCE(
int main(int argc, char *argv[]){
  argc += argc;
  return argc;
}
)SOURCE";

std::vector<CToken> source3_toks{
    CToken{CToken::Type::Keyword, std::string{"int"}},
    CToken{CToken::Type::Identifier, std::string{"main"}},
    CToken{CToken::Type::Punctuator, std::string{"("}},
    CToken{CToken::Type::Keyword, std::string{"int"}},
    CToken{CToken::Type::Identifier, std::string{"argc"}},
    CToken{CToken::Type::Punctuator, std::string{","}},
    CToken{CToken::Type::Keyword, std::string{"char"}},
    CToken{CToken::Type::Punctuator, std::string{"*"}},
    CToken{CToken::Type::Identifier, std::string{"argv"}},
    CToken{CToken::Type::Punctuator, std::string{"["}},
    CToken{CToken::Type::Punctuator, std::string{"]"}},
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

TEST(CLexerTest, CompundAssign) {
  // testing::internal::CaptureStdout();
  std::stringstream source_stream{source3_str, std::ios_base::in};
  CLexer lexer{source_stream};
  EXPECT_TRUE(lexer.lex());
  auto &toks = lexer.ctokens();
  for (int i = 0; i < toks.size() && i < source3_toks.size(); i++) {
    auto &ctok = static_cast<CToken &>(*toks[i]);
    auto &ref_tok = source3_toks[i];
    EXPECT_EQ(ctok.type(), ref_tok.type());
    EXPECT_EQ(ctok.value(), ref_tok.value());
    std::cout << ctok.value() << '\n';
  }
}

#define SOURCE_TEST(name, filepath)                                            \
  TEST(CLexerTest, name) {                                                     \
    std::ifstream input;                                                       \
    /*execution directory is binary directory - build/test/ vxcc_test*/        \
    input.open(filepath);                                                      \
    ASSERT_TRUE(input.is_open());                                              \
    CLexer lexer{input};                                                       \
    EXPECT_TRUE(lexer.lex());                                                  \
  }

SOURCE_TEST(test1_source, "../test_code/C/test1.c")
SOURCE_TEST(test2_source, "../test_code/C/test2.c")
