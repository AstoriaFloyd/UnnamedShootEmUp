#include <raylib.h>
#include <algorithm>


#include "entity.hpp"

extern std::vector<Entity*> entities;

extern Camera3D camera;

extern Texture2D missingTexture;

extern bool renderDebug;

Entity::Entity(){
    Entity({0.0f, 0.0f, 0.0f}, 1.0f, 0.5f, missingTexture, ENEMY);
}

Entity::Entity(Vector3 position, float scale, float hitboxSize, Texture2D texture, int team){
    this->position = position;
    this->scale = scale;
    this->hitboxSize = hitboxSize;
    this->team = team;
    this->texture = texture;
    this->tint = WHITE;
    collideWith = {PLAYER, PLAYERPORJECTILECONVENTIONAL, PLAYERPORJECTILEENERGY};
}

void Entity::render(){
    //DrawCubeV(position, size, color);
    //DrawPlane(position, {size.x, size.y}, color);
    if(!renderDebug)
        DrawBillboard(camera, texture, position, scale, tint);
    else
        DrawBillboard(camera, texture, position, scale, debugTint);
    //Breaks tinting, for debug purposes.
}

void Entity::renderHitbox(){
    //DrawCubeV(position, size, color);
    //DrawPlane(position, {size.x, size.y}, color);
    DrawSphere({position.x, position.y, position.z}, hitboxSize * scale, { 230, 41, 55, 155 });
}

void Entity::update(){
    this->debugTint = GREEN;
}

void Entity::erase(){
    auto it = std::find(entities.begin(), entities.end(), this);
    if (it != entities.end()) { entities.erase(it); }
    //Causes a crash. Possibly unessesary?
    //delete this;
}

void Entity::onCollide(Entity* e){
    this->debugTint = RED;
}

void Entity::collide(std::vector<Entity*> entities){
    for(auto e : entities)
        for(int collide : collideWith)
            if(collide == e->team)
                if(CheckCollisionSpheres(position, this->hitboxSize * e->scale, e->position, e->hitboxSize * e->scale))
                    this->debugTint = RED;
}