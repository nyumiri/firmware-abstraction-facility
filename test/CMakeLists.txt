add_library(unity STATIC)

target_include_directories(unity 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/unity
)

target_sources(unity 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.c
)

add_executable(unit_tests)

target_sources(unit_tests 
    PRIVATE 
    main_t.c
    mock/drivers/DummyDriver.c
    mock/config/CBoard_Valid.c
    mock/config/CBoard_Stress.c
    units/provider_u/Provider_t.c
    units/manager_u/Manager_t.c
)

target_link_libraries(unit_tests 
    PRIVATE 
    unity
    FAF
)