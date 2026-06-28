cmake_minimum_required(VERSION 3.15)
project(FAF LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(FAF STATIC)

target_compile_options(FAF PRIVATE -O2)

target_include_directories(FAF 
    PUBLIC 
    "include"
)

# - FAF Common -----------------------------------------------------------

set(FAF_COMMON
    "src/FAF_Common/FAF_Panic.c"
)

# - FAF Core Module ------------------------------------------------------

set(FAF_CORE
    "src/FAF_Core/FAF_Container.c"
    "src/FAF_Core/FAF_Registry.c"
)

# - FAF Devices Module ---------------------------------------------------


# ------------------------------------------------------------------------

target_sources(FAF 
    PRIVATE 
    "${FAF_COMMON}"
    "${FAF_CORE}"
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

# - Unit Tests -----------------------------------------------------------

add_subdirectory("test/FAF_Core_U")

# ------------------------------------------------------------------------

