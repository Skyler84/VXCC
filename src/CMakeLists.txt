add_library(vxcc)

target_sources(vxcc
PRIVATE
  Lexer/CLexer.cpp
)

target_include_directories(vxcc
PUBLIC
  ../include/
)