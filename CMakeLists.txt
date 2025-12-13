cmake_minimum_required(VERSION 3.10)
project(labs VERSION 1.0.0 LANGUAGES CXX)  # Явно указываем C++

# Настройки компилятора для C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установка выходных директорий
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Включаем поддиректории (СНАЧАЛА библиотеки, ПОТОМ исполняемый файл)
add_subdirectory(Shared)
add_subdirectory(Hammurabi)
add_subdirectory(Array)

# Основной исполняемый файл - добавляем конкретные исходные файлы
add_executable(${PROJECT_NAME} 
    main.cpp
)

# Явно указываем язык цели
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Линкуем библиотеки к основному исполняемому файлу
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Shared
        Hammurabi
)

# Устанавливаем пути для include файлов
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Shared
        ${CMAKE_CURRENT_SOURCE_DIR}/Hammurabi
        ${CMAKE_CURRENT_SOURCE_DIR}/Shared/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Hammurabi/include
)

# Для отладки - проверяем что все найдено
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Building labs project with C++${CMAKE_CXX_STANDARD}")

# Указываем директорию с ресурсами
set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")

# Проверяем существование директории data
if(EXISTS ${DATA_DIR})
    message(STATUS "Found data directory: ${DATA_DIR}")
    
    # Определяем куда копировать данные
    set(DATA_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")
    
    # Копируем директорию data в билд
    file(COPY ${DATA_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    message(STATUS "Data directory copied to: ${DATA_DESTINATION}")
    
    # Добавляем пользовательскую цель для копирования данных
    add_custom_target(CopyData ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${DATA_DIR}"
            "${DATA_DESTINATION}"
        COMMENT "Copying data files to build directory"
    )
else()
    message(WARNING "Data directory not found: ${DATA_DIR}")
    # Создаем пустую директорию для сборки
    file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")
endif()
