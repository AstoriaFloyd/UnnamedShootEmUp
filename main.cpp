#include <raylib.h>
#include <vector>
#include <string>

#include "entity.hpp"
#include "player.hpp"

//480p my beloved
#define SCREEN_WDITH 640
#define SCREEN_HEIGHT 480


//Don't think WindowShouldClose() works right on dreamcast? Check into that.
static bool quitGame = false;

const float leftStickDeadzoneX = 0.1f;
const float leftStickDeadzoneY = 0.1f;

int main() {
    InitWindow(SCREEN_WDITH, SCREEN_HEIGHT, "Does this get used? Unnamed Broken-Moon Shmup.");

    //Target 60, for now.
    SetTargetFPS(60);

    //Create camera
    Camera3D camera = { { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 60.0f, CAMERA_PERSPECTIVE };

    //List of entities
    std::vector<Entity*> entityList;

    //Create player
    //SEE IF THIS IS A GOOD WAY OF DOING THIS
    Player player;
    entityList.push_back(&player);

    entityList.push_back(new Entity({ -4.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, BLUE));
    entityList.push_back(new Entity({ 4.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, YELLOW));
    entityList.push_back(new Entity({ 2.0f, -3.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, ORANGE));

    while(!quitGame) {
        for(Entity* e : entityList){
            e->update();
        }

        /*
        collidedWithEnemies = false;

        if (CheckCollisionBoxes(
        (BoundingBox){(Vector3){ playerPos.x - playerSize.x/2,
                                    playerPos.y - playerSize.y/2,
                                    playerPos.z - playerSize.z/2 },
                        (Vector3){ playerPos.x + playerSize.x/2,
                                    playerPos.y + playerSize.y/2,
                                    playerPos.z + playerSize.z/2 }},
        (BoundingBox){(Vector3){ enemyBoxPos.x - enemyBoxSize.x/2,
                                    enemyBoxPos.y - enemyBoxSize.y/2,
                                    enemyBoxPos.z - enemyBoxSize.z/2 },
                        (Vector3){ enemyBoxPos.x + enemyBoxSize.x/2,
                                    enemyBoxPos.y + enemyBoxSize.y/2,
                                    enemyBoxPos.z + enemyBoxSize.z/2 }})) collidedWithEnemies = true;

        if (CheckCollisionBoxSphere(
        (BoundingBox){(Vector3){ playerPos.x - playerSize.x/2,
                                    playerPos.y - playerSize.y/2,
                                    playerPos.z - playerSize.z/2 },
                        (Vector3){ playerPos.x + playerSize.x/2,
                                    playerPos.y + playerSize.y/2,
                                    playerPos.z + playerSize.z/2 }},
        enemySpherePos, enemySphereSize)) collidedWithEnemies = true;

        if (collidedWithEnemies) playerColor = RED;
        else playerColor = GREEN;
        */

        BeginDrawing();

            ClearBackground(SKYBLUE);
            DrawText("Broken-Moon.net games. Not yet finished.", 0, 0, 12, BLACK);

            DrawText(std::to_string(player.position.x).c_str(), 0, 12, 12, BLACK);
            DrawText(std::to_string(player.position.y).c_str(), 0, 24, 12, BLACK);
            DrawText(std::to_string(player.position.z).c_str(), 0, 36, 12, BLACK);

            BeginMode3D(camera);
                for(Entity* e : entityList){
                    e->render();
                }
                //TestEntity.render();
                //player.render();
                //DrawCubeV(player.position, player.size, player.color);
            EndMode3D();

        EndDrawing();
    }
}