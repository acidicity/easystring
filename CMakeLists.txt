cmake_minimum_required(VERSION 3.10)

project(easystring C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
    src/string.c
)

set(Headers
    include/es/string.h
)
set(LIBRARY_OUTPUT_PATH 
    ${PROJECT_SOURCE_DIR}/lib
)

add_library(easystring STATIC ${Sources} ${Headers})

add_subdirectory(tests)

target_include_directories(easystring PUBLIC include)
