#include <raylib.h>

#include "entity.hpp"

Entity::Entity(){
    Entity({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, PURPLE);
}

Entity::Entity(Vector3 position, Vector3 size, Color color){
    this->position = position;
    this->size = size;
    this->color = color;
}

void Entity::render(){
    DrawCubeV(position, size, color);
}

void Entity::update(){
}