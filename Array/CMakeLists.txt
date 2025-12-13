cmake_minimum_required(VERSION 3.10)

project(Array LANGUAGES CXX)  # Явно указываем C++

# Ищем исходные файлы
file(GLOB_RECURSE ARR_SOURCES 
    "*.hpp"
    "*.inl"
    "*.cpp"
)

# Создаем библиотеку
add_library(${PROJECT_NAME} ${ARR_SOURCES})

# Явно указываем язык цели
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Заголовочные файлы
target_include_directories(Array
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "${PROJECT_NAME} sources: ${ARR_SOURCES}")