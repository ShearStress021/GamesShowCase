#include "raylib.h"
#include "raylib.hpp"

#include "mainMenuScene.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <memory>
#define WIDTH 920
#define HEIGHT 720 

int main(void)
{


    InitWindow(WIDTH,HEIGHT, "raylib [core] example - basic window");

    std::shared_ptr<game::GameScene> currscene = std::make_shared<game::MainMenuScene>();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            currscene->draw();


        EndDrawing();
    }


    CloseWindow();

    return 0;

}

