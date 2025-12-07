cmake_minimum_required(VERSION 3.10)

project(Hammurabi LANGUAGES CXX)  # Явно указываем C++

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

# Связываем с Shared библиотекой
if(TARGET Shared)
    target_link_libraries(Hammurabi
        PRIVATE
            Shared  # Это автоматом добавит include пути от Shared
    )
endif()

# Заголовочные файлы
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

message(STATUS "${PROJECT_NAME} sources: ${SHARED_SOURCES}")