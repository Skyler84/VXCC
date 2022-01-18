project(VXCC DESCRIPTION "Versatile cross Compiler" LANGUAGES CXX )
cmake_minimum_required(VERSION 3.22)

add_compile_options(-std=c++20)
add_compile_options(-Wsuggest-override -fpermissive)

option(BUILD_DOC "Build documentation" ON)
if(BUILD_DOC)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    # request to configure the file
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endif(BUILD_DOC)

add_subdirectory(src)
