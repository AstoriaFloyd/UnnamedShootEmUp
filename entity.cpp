#include <raylib.h>
#include <algorithm>


#include "entity.hpp"

extern std::vector<Entity*> entities;

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

void Entity::erase(){
    auto it = std::find(entities.begin(), entities.end(), this);
    if (it != entities.end()) { entities.erase(it); }
    //Causes a crash. Possibly unessesary?
    //delete this;
}