#include "raylib.hpp"
#include "mainMenuScene.hpp"

#include "heroScene.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define WIDTH 920
#define HEIGHT 720 

int main(void)
{


    InitWindow(WIDTH,HEIGHT, "raylib [core] example - basic window");

    std::shared_ptr<game::GameScene> currscene = std::make_shared<game::MainMenuScene>();

    currscene->loadGameResources();

    currscene->start();


    while (!WindowShouldClose())
    {
        auto nextScene = currscene->update();

        if (nextScene)
        {
            nextScene->loadGameResources();
            currscene = nextScene;
        }
        BeginDrawing();
           // ClearBackground(BLUE);

            currscene->draw();


        EndDrawing();
    }


    CloseWindow();

    return 0;

}

