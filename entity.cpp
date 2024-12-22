#include <raylib.h>
#include <algorithm>


#include "entity.hpp"

extern std::vector<Entity*> entities;

extern Camera3D camera;

extern Texture2D missingTexture;

Entity::Entity(){
    Entity({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, missingTexture, ENEMY);
}

Entity::Entity(Vector3 position, Vector3 size, Texture2D texture, int team){
    this->position = position;
    this->size = size;
    this->team = team;
    this->texture = texture;
    this->tint = WHITE;
}

void Entity::render(){
    //DrawCubeV(position, size, color);
    //DrawPlane(position, {size.x, size.y}, color);
    DrawBillboard(camera, texture, position, 1.0f, WHITE);
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