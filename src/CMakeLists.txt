add_library(TankLib tank.cpp)

target_include_directories(TankLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(TankLib PUBLIC threepp::threepp)
target_link_libraries(TankLib PUBLIC assimp::assimp)