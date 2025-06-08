cmake_minimum_required(VERSION 3.10)

project(image_server LANGUAGES CXX)

# Требуем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем OpenCV через vcpkg
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found! Run vcpkg integrate install or pass toolchain.")
endif()

# Добавляем include для httplib
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Собираем исполняемый
add_executable(image_server
    src/image_server.cpp
)

# Линкуем OpenCV
target_link_libraries(image_server ${OpenCV_LIBS})

# Выкладываем exe в build/bin
set_target_properties(image_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
