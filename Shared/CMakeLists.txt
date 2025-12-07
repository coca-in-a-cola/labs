cmake_minimum_required(VERSION 3.10)

project(Shared LANGUAGES CXX)  # Явно указываем C++

# Ищем исходные файлы
file(GLOB_RECURSE SHARED_SOURCES 
    "*.cpp"
    "*.cxx"
    "*.cc"
)

# Создаем библиотеку
add_library(${PROJECT_NAME} ${SHARED_SOURCES})

# Явно указываем язык цели
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Заголовочные файлы
target_include_directories(Shared
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # Теперь Hammurabi будет видеть Helpers.h
)

message(STATUS "${PROJECT_NAME} sources: ${SHARED_SOURCES}")