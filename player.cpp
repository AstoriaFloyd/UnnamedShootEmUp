#include <raylib.h>

#include "player.hpp"

Player::Player(){
    position = {0.0f, 0.0f, 0.0f};
    size = {1.0f, 1.0f, 0.0f};
    color = GREEN;
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
}

void Player::render(){
    DrawCubeV(position, size, MAGENTA);
}