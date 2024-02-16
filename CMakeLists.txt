set(TARGET_NAME "algorithms_review")

option(BUILD_TESTS "Enable test building; users may want to turn this OFF.)" ON)

cmake_minimum_required(VERSION 3.26)

project(${TARGET_NAME})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GCC_LIKE_CXX "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(MSVC_LIKE_CXX "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,bugprone-*,cert-*,clang-analyzer-*,cppcoreguidelines-*,-cppcoreguidelines-pro-type-reinterpret-cast,hicpp-*,modernize-*,-modernize-use-trailing-return-type,performance-*,readability-*)

add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME} INTERFACE .)

target_compile_options(${TARGET_NAME} INTERFACE
  "$<${GCC_LIKE_CXX}:-g;-Wall;-Werror;-pedantic;-Wextra;-Wshadow;-Wsign-conversion;-Wunused>"
  "$<${MSVC_LIKE_CXX}:-W3>"
)
#add_executable( main graph.cpp main.cpp )

if (BUILD_TESTS)
  message(STATUS "Testing is on")

  enable_testing()
  set(TEST_PROJ "tests")

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_executable(${TEST_PROJ} chp21.cpp chp21_tests.cpp)
  target_link_libraries(
    ${TEST_PROJ}
    GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(${TEST_PROJ})
endif()
