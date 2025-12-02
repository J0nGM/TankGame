add_library(TankLib
        collision/collision.cpp
        collision/collisionmanager.cpp

        landscape_arena/arenawalls.cpp
        landscape_arena/landscape.cpp

        level2/portalLVL2.cpp
        level2/landscape2.cpp
        level2/enemy.cpp
        level2/obstecalelvl2.cpp

        managers/pickupmanger.cpp
        managers/enemymanger.cpp
        managers/bulletmanger.cpp
        managers/levelmanger.cpp
        managers/trailmanager.cpp

        powerups/boost/boost.cpp
        powerups/bullet/bullet.cpp
        powerups/ammo/ammo.cpp

        imguihandler.cpp
        landscape_arena/arenawalls.cpp

        camercontrolls.cpp
        landscape_arena/landscape.cpp
        WindowResize.cpp
        collision/collision.cpp
        gamemanger.cpp

        keyinputhandler.cpp

        tank/tank.cpp
        tank/tankattack.cpp
        tank/tankmovment.cpp

)


target_include_directories(TankLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(TankLib PUBLIC threepp::threepp assimp::assimp)
target_link_libraries(TankLib PUBLIC
        threepp::threepp
        imgui_glfw
)

#Had major issues with imgui includes in TankLib without this, Ai assited me in fixing it
target_include_directories(TankLib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)