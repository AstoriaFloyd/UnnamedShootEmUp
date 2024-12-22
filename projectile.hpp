#pragma once

#include <raylib.h>

#include "entity.hpp"

class Projectile : public Entity {
    public:
        Projectile(Vector3 position, float scale, float size, Vector2 speed, Texture texture, int team);
        Vector2 speed;
        void update();
    private:
};