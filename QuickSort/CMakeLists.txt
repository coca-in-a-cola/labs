cmake_minimum_required(VERSION 3.10)
project(QuickSort LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

# ---- asciichart как header-only зависимость ----
add_library(asciichart INTERFACE)
target_include_directories(asciichart INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/asciichart/include"
)

# QuickSort "знает", что ему нужна asciichart
target_link_libraries(${PROJECT_NAME} INTERFACE asciichart)

# ---- Tests ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE ${PROJECT_NAME}_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cxx"
)

add_executable(${PROJECT_NAME}Tests ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}Tests PRIVATE ${PROJECT_NAME} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}Tests)
