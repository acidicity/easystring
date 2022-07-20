cmake_minimum_required(VERSION 3.10)

project(tests)

set(Sources
    src/tests.cpp
)

set(EXECUTABLE_OUTPUT_PATH
    ${CMAKE_CURRENT_LIST_DIR}/bin
)

add_executable(tests ${Sources})

target_link_libraries(tests PUBLIC
    easystring
    gtest_main
)

add_test(
    NAME tests
    COMMAND tests
)
