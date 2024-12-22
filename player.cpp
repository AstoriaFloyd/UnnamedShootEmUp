#include <raylib.h>

#include "player.hpp"
#include "projectile.hpp"

#include <vector>
#include "entity.hpp"

extern std::vector<Entity*> entities;

extern bool renderDebug;

Player::Player(Texture2D texture, Texture2D bullet){
    this->position = {0.0f, 0.0f, 0.0f};
    this->scale = 1.0f;
    this->hitboxSize = 0.2f;
    this->tint = WHITE;
    this->texture = texture;
    this->bulletTexture = bullet;
    this->team = PLAYER;
    collideWith = {ENEMY, ENEMYPROJECTILECONVENTIONAL, ENEMYPROJECTILEENERGY};
}

void Player::update(){
    controllerRoutine();
}

void Player::controllerRoutine() {
    bool right;
    bool left;
    bool up;
    bool down;

    float speed = 0.05;

    float diagonalModifier = 0.70711f;

    if(!IsGamepadAvailable(0))
        return;

    //All of this is dpad
    right = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    left = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    up = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    down = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);

    if(right || left || up ||down){
        bool horizontal = right && left;
        bool vertical = up && down;

        if(horizontal && vertical)
            speed *= diagonalModifier;

        if(left)
            position.x -= speed;
        if(right)
            position.x += speed;
        if(up)
            position.y += speed;
        if(down)
            position.y -= speed;
    } else {
        //Do analog stick
        float leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        //Dead zones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;

        position.y -= leftStickY * speed;

        position.x += leftStickX * speed;

    }

    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
        entities.push_back(new Projectile(position, 1.0f, 0.5f, {0.5f, 0.0f}, bulletTexture, PLAYERPORJECTILECONVENTIONAL));
    }

    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)){
        renderDebug = !renderDebug;
    }
}