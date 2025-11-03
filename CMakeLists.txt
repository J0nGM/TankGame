cmake_minimum_required(VERSION 3.16)
project(Tank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#target_compile_definitions(${arg_NAME} PRIVATE DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")

include(FetchContent)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
set(THREEPP_USE_ASSIMP ON)

FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 619cdaacc2e7dc6ea709d8c7f482e2994af7349d
)
FetchContent_MakeAvailable(threepp)

set(CATCH2_BUILD_TESTING OFF)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)

enable_testing()
add_subdirectory(tests)


include(FetchContent)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.2
)
FetchContent_MakeAvailable(assimp)



add_subdirectory(src)
add_executable(TankSim main.cpp)


target_link_libraries(TankSim PUBLIC TankLib)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#Legg til tanrget_compile_definitions(TankSim PRIVATE THREEPP_USE_ASSIMP)
