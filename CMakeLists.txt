cmake_minimum_required(VERSION 3.15)
project(FAF LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(FAF STATIC)

target_include_directories(FAF 
    PUBLIC 
    "include"
)

# - ESP32 ARDUINO DRIVERS ------------------------------------------------

file(GLOB_RECURSE ESP_ARD_SOURCES "src/drivers/esp32/arduino/*.cpp")

# ------------------------------------------------------------------------

target_sources(FAF 
    PRIVATE 
    "src/infra/FAF_Provider.c"
    "src/infra/FAF_Manager.c"
    ${ESP_ARD_SOURCES}
)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()