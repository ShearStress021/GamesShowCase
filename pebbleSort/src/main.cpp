#include "pebbleSort.h"
#define WIDTH 1024
#define HEIGHT 768 

int main()
{
    InitWindow(WIDTH, HEIGHT, "raylib example - basic window");

    Container container{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        container.update(GetFrameTime());
        container.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
