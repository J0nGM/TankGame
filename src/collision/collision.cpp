
#include <iostream>
#include "collision.hpp"

using namespace threepp;
//Fått hjelp av Ai for å generer koden, slik at den faktisk fungerer
bool collision::check_collision(Box3 tank_box, std::vector<std::shared_ptr<threepp::Group>> objects) {
    for (const auto&obj : objects) {
        if (!obj->visible) continue; //Når trærene blir skutt blir det mulig å kjøre gjennom der de var plassert før.
        Box3 object_box;


        if (!obj->children.empty()) {
            auto trunk = obj->children[0];
            object_box.setFromObject(*trunk);
        }
        else{
            object_box.setFromObject(*obj);
        }


            //Shrinke boksen litt, slik at det ikke er så sensitivt for kollisjoner
            float shrink_amount = 7.5f;
            Vector3 min = object_box.min();
            Vector3 max = object_box.max();

            min.x += shrink_amount;
            min.z += shrink_amount;
            max.x -= shrink_amount;
            max.z -= shrink_amount;

            object_box.set(min, max);

            if (tank_box.intersectsBox(object_box)) {
                std::cout << "Collision detected!" << std::endl;
                return true;

            }
        }
    return false;
}