/*#include "tank.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tank creation") {
    using namespace threepp;

    // Create a tank instance
    Tank tank("../assets/Tank3.stl");

    // Check if the tank's mesh is created
    REQUIRE(tank.mesh != nullptr);

    // Check if the tank's mesh has geometry and material
    REQUIRE(tank.mesh->geometry != nullptr);
    REQUIRE(tank.mesh->material != nullptr);

    // Check if the tank's mesh is scaled correctly
    REQUIRE(tank.mesh->scale.x == Approx(0.001f));
    REQUIRE(tank.mesh->scale.y == Approx(0.001f));
    REQUIRE(tank.mesh->scale.z == Approx(0.001f));
}
*/