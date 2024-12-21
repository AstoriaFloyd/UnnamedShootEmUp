#pragma once

#include <raylib.h>

class Entity {
    public:
        Vector3 position;
        Vector3 size;
        //Maybe shouldnt be public.
        Color color;
        Entity();
        Entity(Vector3 position, Vector3 size, Color color);

        //Set positions
        void setPosition(Vector3 position);
        void setSize(Vector3 size);

        //Basic renderer, to be overridden
        virtual void render();

        //Updates every frame
        virtual void update();
};