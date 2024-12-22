#pragma once

#include <raylib.h>

#include "entity.hpp"

class Player : public Entity {
    public:
        Player(Texture2D texture, Texture2D bullet);
        float speed;
        float leftStickDeadzoneX;
        float leftStickDeadzoneY;
        bool collided;
        Texture2D bulletTexture;
        void update();
        void collide(std::vector<Entity*> entities);
    private:
        void controllerRoutine();
};