add_executable(vxcc-bin)
set_target_properties(vxcc-bin PROPERTIES OUTPUT_NAME vxcc)

target_sources(vxcc-bin
PRIVATE
  main.cpp
  ArgParser.cpp
)

target_link_libraries(vxcc-bin 
PRIVATE
  vxcc
)

install(TARGETS vxcc-bin DESTINATION /usr/local/bin/)