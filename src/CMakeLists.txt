add_library(vxcc)

target_sources(vxcc
PRIVATE
  Lexer/CLexer.cpp
  Lexer/CToken.cpp
  Lexer/TokenStream.cpp
  Parser/Parser.cpp
)

target_include_directories(vxcc
PUBLIC
  ../include/
)