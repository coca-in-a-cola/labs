cmake_minimum_required(VERSION 3.10)

project(Shared LANGUAGES CXX) 

file(GLOB_RECURSE SHARED_SOURCES 
    "*.cpp"
    "*.cxx"
    "*.cc"
)

add_library(${PROJECT_NAME} ${SHARED_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Shared
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "${PROJECT_NAME} sources: ${SHARED_SOURCES}")