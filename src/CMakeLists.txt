add_library(TankLib tank.cpp keycontrolls.cpp camercontrolls.cpp landscape.cpp WindowResize.cpp collision.cpp powerups/doublespeed.cpp)

target_include_directories(TankLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(TankLib PUBLIC threepp::threepp assimp::assimp)