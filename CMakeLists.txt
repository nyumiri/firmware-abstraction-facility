cmake_minimum_required(VERSION 3.15)
project(FAF LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(FAF STATIC)

target_include_directories(FAF 
    PUBLIC 
    "include"
)

# - ESP32 ARDUINO DRIVERS ------------------------------------------------

set(ESP_ARD_SOURCES
    "src/drivers/esp32/arduino/ArduinoLED_Impl.cpp"
    "src/drivers/esp32/arduino/ArduinoMQTT_Impl.cpp"
    "src/drivers/esp32/arduino/ArduinoWifi_Impl.cpp"
)

# ------------------------------------------------------------------------

target_sources(FAF 
    PRIVATE
    "src/infra/FAF_Provider.c"
    "src/infra/FAF_Manager.c"
    ${ESP_ARD_SOURCES}
)

# - LINKER SETTINGS ------------------------------------------------------

set(FAF_NATIVE_LINKER 
    "${CMAKE_CURRENT_SOURCE_DIR}/conf/faf_linker_native.ld"
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR 
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    target_link_options(FAF INTERFACE 
        "LINKER:-T${FAF_NATIVE_LINKER}"
    )

endif()
# ------------------------------------------------------------------------

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(test)
