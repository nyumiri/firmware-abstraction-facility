add_executable(FAF_Core_Tests)

include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY      https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG             v2.6.1
)

FetchContent_MakeAvailable(unity)

target_include_directories(FAF_Core_Tests PRIVATE "inc")

set(FAF_MOCK_DEVICE
    "src/devices/mock/FAF_MockDevice_Impl.c"
)

set(CORE_UT
    "src/units/FAF_Container_T.c"
    "src/units/FAF_Registry_T.c"
    "src/units/FAF_Dispatcher_T.c"
)

target_sources(FAF_Core_Tests
    PRIVATE 
    "src/main.c"
    ${FAF_MOCK_DEVICE}
    "src/conf/Mock_Conf.c"
    ${CORE_UT}
)

target_link_libraries(FAF_Core_Tests PRIVATE FAF unity)