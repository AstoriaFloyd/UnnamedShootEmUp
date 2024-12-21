#pragma once

#include <raylib.h>

#include "entity.hpp"

class Projectile : public Entity {
    public:
        Projectile(Vector3 position, Vector3 size, Vector2 speed, Color color, int team);
        Vector2 speed;
        void update();
    private:
};