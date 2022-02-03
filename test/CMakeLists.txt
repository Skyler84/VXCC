
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(vxcc_test)

target_sources(vxcc_test PRIVATE
  CLexerTest.cpp
  CParserTest.cpp
)

target_link_libraries(vxcc_test
PRIVATE
  gtest_main
  vxcc
)

include(GoogleTest)
gtest_discover_tests(vxcc_test)