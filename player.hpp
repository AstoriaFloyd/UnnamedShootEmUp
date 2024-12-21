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
        void render();
    private:
        void controllerRoutine();
};