cmake_minimum_required(VERSION 3.20)
project(miniSTL VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(mini_stl INTERFACE)
target_include_directories(mini_stl INTERFACE
  ${PROJECT_SOURCE_DIR}/include
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(test_smoke
  tests/test_smoke.cpp
)
target_link_libraries(test_smoke PRIVATE mini_stl GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_smoke)
