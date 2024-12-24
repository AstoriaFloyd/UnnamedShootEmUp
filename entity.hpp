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
        float scale;
        float hitboxSize;
        //Maybe shouldnt be public.
        //Used to determine if class SHOULD collide.
        int team;
        std::vector<int> collideWith;
        Texture2D texture;
        Color tint;
        //For debugging reasons.
        Color debugTint;
        Model model;
        Entity();
        Entity(Vector3 position, float scale, float hitboxSize, Texture2D texture, int team);

        //Basic renderer, to be overridden
        virtual void render(Matrix rotationMatrix, Vector3 centerPoint);
        //DEBUG FUNCTION
        virtual void renderHitbox();
        //Updates every frame
        virtual void update();

        virtual void collide(std::vector<Entity*> entities);
        virtual void onCollide(Entity* entity);
        void erase();
};