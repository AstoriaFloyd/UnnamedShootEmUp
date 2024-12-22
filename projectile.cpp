#include <raylib.h>
#include <cmath>
#include <vector>
#include "projectile.hpp"

Projectile::Projectile(Vector3 position, Vector3 size, Vector2 speed, Texture2D texture, int team) {
    this->position = position;
    this->size = size;
    this->speed = speed;
    this->texture = texture;
    this->team = team;
};

void Projectile::update(){
    this->position.x += speed.x;
    this->position.y += speed.y;

    if(abs(this->position.x) > 15 || abs(this->position.y) > 15){
        this->erase();
    }
}