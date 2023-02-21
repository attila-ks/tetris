cmake_minimum_required(VERSION 3.14)

project(backend_test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "$ENV{QTHOME}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b73f27fd164456fea9aba56163f5511355a03272
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    backend_test
    ../backend/src/index.cpp
    ../backend/src/block.cpp
    backend/src/blocktest.cpp
    ../backend/headers/tetrisboard.h
    ../backend/src/tetrisboard.cpp
    ../backend/headers/tetromino.h
    ../backend/src/tetromino.cpp
    backend/src/tetrominotest.cpp
    backend/src/gameboardtest.cpp
)

target_link_libraries(
    backend_test
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(backend_test)
