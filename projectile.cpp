#include <raylib.h>
#include <cmath>
#include <vector>
#include "projectile.hpp"



Projectile::Projectile(Vector3 position, Vector3 size, Vector2 speed, Color color, int team) {
    this->position = position;
    this->size = size;
    this->speed = speed;
    this->color = color;
    this->team = team;
};

void Projectile::update(){
    this->position.x += speed.x;
    this->position.y += speed.y;

    if(abs(this->position.x) > 15 || abs(this->position.y) > 15){
        this->erase();
    }
}