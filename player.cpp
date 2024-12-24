#include <raylib.h>

#include "player.hpp"
#include "projectile.hpp"

#include <vector>
#include "entity.hpp"

extern std::vector<Entity*> entities;

extern bool renderDebug;

extern Vector3 cameraPosition;


extern float pitch;

extern float roll;

extern float yaw;

Player::Player(Texture2D texture, Texture2D bullet){
    this->position = {0.0f, 0.0f, 0.0f};
    this->scale = 1.0f;
    this->hitboxSize = 0.2f;
    this->tint = WHITE;
    this->texture = texture;
    this->bulletTexture = bullet;
    this->team = PLAYER;
    collideWith = {ENEMY, ENEMYPROJECTILECONVENTIONAL, ENEMYPROJECTILEENERGY};
    Mesh mesh = GenMeshCube(1.0f, 1.0f, 0.0f);
    model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
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
        /*
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
            */

        if(left)
            yaw -= 2.0f;
        if(right)
            yaw += 2.0f;
        if(up)
            pitch -= 2.0f;
        if(down)
            pitch += 2.0f;
    } else {
        //Do analog stick
        float leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        //Dead zones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;

        position.y -= leftStickY * 2.0f;

        position.x += leftStickX * 2.0f;
    }

        float leftTrigger = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER);
        float rightTrigger = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER);
        if (leftTrigger > -leftStickDeadzoneX && leftTrigger < leftStickDeadzoneX) leftTrigger = 0.0f;
        if (rightTrigger > -leftStickDeadzoneY && rightTrigger < leftStickDeadzoneY) rightTrigger = 0.0f;

        //cameraPosition.z -= leftTrigger * speed;
        //cameraPosition.z += rightTrigger * speed;

        roll -= leftTrigger * 2.0f;
        roll += rightTrigger * 2.0f;


    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
        entities.push_back(new Projectile(position, 1.0f, 0.5f, {0.5f, 0.0f}, bulletTexture, PLAYERPORJECTILECONVENTIONAL));
    }

    if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)){
        renderDebug = !renderDebug;
    }
}