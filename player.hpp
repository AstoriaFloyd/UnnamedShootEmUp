#pragma once

#include <raylib.h>

#include "entity.hpp"

class Player : public Entity {
    public:
        Player();
        float speed;
        float leftStickDeadzoneX;
        float leftStickDeadzoneY;
        bool collided;

        void update();
        void collide(std::vector<Entity*> entities);
    private:
        void controllerRoutine();
};