cmake_minimum_required(VERSION 3.16)
project(Tank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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


set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v6.0.2
)
FetchContent_MakeAvailable(assimp)


#used https://gist.github.com/jeffamstutz/992723dfabac4e3ffff265eb71a24cd9 for imgui
FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/docking.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(imgui)

find_package(OpenGL REQUIRED)

add_library(imgui_glfw STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(imgui_glfw PUBLIC
        threepp::threepp
        glfw
        OpenGL::GL
)
#Tried to fix Git-hub actions build error by adding this. It was suggested by AI.
#Found out that X11 required for ImGui on Linux
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(TankSim PUBLIC ${X11_LIBRARIES})
endif()

target_include_directories(imgui_glfw PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
get_target_property(GLFW_INCLUDES glfw INTERFACE_INCLUDE_DIRECTORIES)
if(GLFW_INCLUDES)
    target_include_directories(imgui_glfw PUBLIC ${GLFW_INCLUDES})
endif()


add_subdirectory(src)

add_executable(TankSim main.cpp)
target_link_libraries(TankSim PUBLIC TankLib imgui_glfw)

enable_testing()
add_subdirectory(tests)


file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



#Legg til tanrget_compile_definitions(TankSim PRIVATE THREEPP_USE_ASSIMP)
