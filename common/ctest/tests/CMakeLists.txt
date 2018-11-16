cmake_minimum_required(VERSION 3.11)

project(ctest_tests)
add_compile_options("-Wall" "-Wextra" "-pedantic" "-Wcast-align"
"-Winit-self" "-Wmissing-include-dirs" "-Wredundant-decls" "-Wshadow" "-Wstrict-overflow=5" "-Wundef" "-Wwrite-strings" "-Wpointer-arith" "-Wmissing-declarations"
"-Wuninitialized" "-Wold-style-definition" "-Wstrict-prototypes"
"-Wmissing-prototypes" "-Wswitch-default" "-Wbad-function-cast"
"-Wnested-externs" "-Wconversion" "-Wunreachable-code")

set (CTEST_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/ctest_tests.c
    )

add_executable(${PROJECT_NAME} ${CTEST_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ctest_lib)


