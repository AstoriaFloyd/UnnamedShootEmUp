#pragma once

#include <vector>

#include <raylib.h>

//Might need reevaluating
#define PLAYER 0
#define PLAYERPORJECTILEENERGY 1
#define PLAYERPORJECTILECONVENTIONAL 2
#define ENEMY 3
#define ENEMYPROJECTILEENERGY 4
#define ENEMYPROJECTILECONVENTIONAL 5

class Entity {
    public:
        Vector3 position;
        Vector3 size;
        //Maybe shouldnt be public.
        Color color;
        //Used to determine if class SHOULD collide.
        int team;
        Entity();
        Entity(Vector3 position, Vector3 size, Color color, int team);

        //Set positions
        void setPosition(Vector3 position);
        void setSize(Vector3 size);

        //Basic renderer, to be overridden
        virtual void render();

        //Updates every frame
        virtual void update();

        virtual void collide(std::vector<Entity*> entities);
};