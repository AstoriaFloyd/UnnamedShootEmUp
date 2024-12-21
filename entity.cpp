#include <raylib.h>

#include "entity.hpp"

Entity::Entity(){
    Entity({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, PURPLE, ENEMY);
}

Entity::Entity(Vector3 position, Vector3 size, Color color, int team){
    this->position = position;
    this->size = size;
    this->color = color;
    this->team = team;
}

void Entity::render(){
    DrawCubeV(position, size, color);
}

void Entity::update(){
}

void Entity::collide(std::vector<Entity*> entities){
}