#include <raylib.h>
#include <cmath>
#include <vector>
#include "projectile.hpp"

Projectile::Projectile(Vector3 position, float scale, float hitboxSize, Vector2 speed, Texture2D texture, int team) {
    this->position = position;
    this->scale = scale;
    this->hitboxSize = hitboxSize;
    this->speed = speed;
    this->texture = texture;
    this->team = team;
    this->tint = WHITE;
    this->debugTint = WHITE;
};

void Projectile::update(){
    this->position.x += speed.x;
    this->position.y += speed.y;

    if(abs(this->position.x) > 15 || abs(this->position.y) > 15){
        this->erase();
    }
}