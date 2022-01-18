add_library(vxcc)

target_sources(vxcc
PRIVATE
  Lexer/CLexer.cpp
  Lexer/TokenStream.cpp
)

target_include_directories(vxcc
PUBLIC
  ../include/
)