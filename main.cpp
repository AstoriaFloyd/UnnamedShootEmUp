#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <string>

#include "entity.hpp"
#include "player.hpp"
#include "projectile.hpp"

#ifdef __DREAMCAST__
#  define PLATFORM_IS_DREAMCAST 1
#else
#  define PLATFORM_IS_DREAMCAST 0
#endif

//480p my beloved
#define SCREEN_WDITH 640
#define SCREEN_HEIGHT 480


//Don't think WindowShouldClose() works right on dreamcast? Check into that.
bool quitGame = false;

const float leftStickDeadzoneX = 0.1f;
const float leftStickDeadzoneY = 0.1f;

//List of entities
std::vector<Entity*> entities;

//Create camera
Vector3 cameraPosition = { 0.0f, 0.0f, 25.0f };
Vector3 upVector = { 0.0f, 1.0f, 0.0f };
Camera3D camera = { cameraPosition, { 0.0f, 0.0f, 0.0f }, upVector, 60.0f, CAMERA_PERSPECTIVE };

Texture2D missingTexture;

bool renderDebug = false;

float pitch = 0.0f;
float roll = 0.0f;
float yaw = 0.0f;

Vector3 centerPoint = {14.0f, 3.0f, 0.0f};

int main() {
    InitWindow(SCREEN_WDITH, SCREEN_HEIGHT, "Unnamed Broken-Moon Shmup.");

    //Target 60, for now.
    //SetTargetFPS(60);
    
    entities.reserve(1024);

    std::string path;

    if(PLATFORM_IS_DREAMCAST){
        path = "/pc/home/astoria/dev/raylib4dc/BrokenMoonShmupC++/assets";
    } else {
        path = "assets";
    }
    
    Image image = LoadImage((path + "/MissingTexture.png").c_str());
    missingTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    Model skybox = LoadModel((path + "/ParkingLot.obj").c_str());

    //Mesh sphereMesh = GenMeshHemiSphere(1.0f, 16, 16);
    //Model skybox = LoadModelFromMesh(sphereMesh);

    //Image skyboxImage = LoadImage("/cd/TropicalSunnyDay/sphereTexture.png");
    //Texture2D skyboxTexture = LoadTextureFromImage(skyboxImage);
    //skybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = skyboxTexture;
    //UnloadImage(skyboxImage);

    

    Player player = Player(missingTexture, missingTexture);
    entities.push_back(&player);

    entities.push_back(new Entity({ -4.0f, 1.0f, 0.0f }, 1.0f, 0.5f, missingTexture, ENEMY));
    entities.push_back(new Entity({ 4.0f, 1.0f, 0.0f }, 1.0f, 0.5f, missingTexture, ENEMY));
    entities.push_back(new Entity({ 2.0f, -3.0f, 0.0f }, 0.5f, 0.5f, missingTexture, ENEMY));

    entities.push_back(new Projectile({ -3.5f, -1.0f, 0.0f }, 1.0f, 0.5f, {0.05f, 0.0f}, missingTexture, ENEMYPROJECTILEENERGY));

    while(!quitGame) {

        if (WindowShouldClose()){
            quitGame = true;
        }

        int counter = 0;
        for(Entity* e:entities){
            e->update();
            counter++;
        }

        //Collision detection

        for(Entity* e:entities){
            e->collide(entities);
        }


        //yaw += 0.1f;

        camera.position = Vector3Add(centerPoint, Vector3Transform(cameraPosition, MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*roll })));
        camera.target = centerPoint;
        camera.up = Vector3Transform(upVector, MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*roll }));
        //camera.up = (Vector3){ DEG2RAD*pitch, DEG2RAD*yaw + 180, DEG2RAD*roll };

        BeginDrawing();
            BeginMode3D(camera);

                ClearBackground(RED);

                rlDisableBackfaceCulling();
                rlDisableDepthMask();
                    DrawModel(skybox, camera.position, 1.0f, WHITE);
                rlEnableBackfaceCulling();
                rlEnableDepthMask();
            
                for(Entity* e:entities){
                    e->render(MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*roll }), centerPoint);
                    if(renderDebug)
                        e->renderHitbox(MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*roll }), centerPoint);
                }
                //TestEntity.render();
                //player.render();
                //DrawCubeV(player.position, player.size, player.color);
                //DrawBillboard(camera, missingTexture2, player.position, 1.0f, WHITE);
            EndMode3D();


            //DrawText("Broken-Moon.net games. Not yet finished.", 0, 0, 12, BLACK);

            //DrawText(std::to_string(player.position.x).c_str(), 0, 12, 12, BLACK);
            //DrawText(std::to_string(player.position.y).c_str(), 0, 24, 12, BLACK);
            //DrawText(std::to_string(player.position.z).c_str(), 0, 36, 12, BLACK);
            DrawText(std::to_string(counter).c_str(), 0, 0, 12, BLACK);
            DrawText(std::to_string(cameraPosition.x).c_str(), 0, 12, 12, BLACK);
            DrawText(std::to_string(cameraPosition.y).c_str(), 64, 12, 12, BLACK);
            DrawText(std::to_string(cameraPosition.z).c_str(), 128, 12, 12, BLACK);
            DrawFPS(0, 24);


        EndDrawing();
    }

    CloseWindow();
}
