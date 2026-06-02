add_library(unity STATIC)

target_include_directories(unity 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/unity
)

target_sources(unity 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.c
)

add_executable(provider_t)

target_sources(provider_t 
    PRIVATE 
    main_t.c
    mock/drivers/DummyDriver.c
    mock/BoardDefinition.c
    units/provider_u/Provider_t.c
)

target_link_libraries(provider_t 
    PRIVATE 
    unity
    FAF
)