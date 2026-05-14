
#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - world screen");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector2 cubeScreenPosition = { 0.0f, 0.0f };

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    Model model = LoadModel("Characters/gltf/Barbarian.glb");
//    Texture2D texture = LoadTexture("Characters/gltf/barbarian_texture.png");
  //  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    int animCount{0};

    ModelAnimation *anims = LoadModelAnimations("Characters/gltf/Barbarian.glb", &animCount);

    int animIndex = 10;                  // Current animation playing
    float animCurrentFrame = 0.0f;      // Current animation frame (supporting interpolated frames)
    float animFrameSpeed = 0.5f;


    char *animNames[64] = { 0 };
    for (int i = 0; i < animCount; i++) animNames[i] = anims[i].name;

    float animFrameProgress = 0.0f;
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // Calculate cube screen space position (with a little offset to be in top)
        cubeScreenPosition = GetWorldToScreen((Vector3){cubePosition.x, cubePosition.y + 2.5f, 
                cubePosition.z}, camera);

        if (animIndex < animCount)
        {
            // Update model animation
            animCurrentFrame += animFrameSpeed;
            if (animCurrentFrame >= anims[animIndex].keyframeCount) animCurrentFrame = 0.0f;
            UpdateModelAnimation(model, anims[animIndex], animCurrentFrame);
        }

        // NOTE: Animation and playing speed selected through UI

        // Update progressbar value with current frame
        animFrameProgress = animCurrentFrame;
        //-----------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                
//                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawModel(model, cubePosition, 1.f, WHITE);
  //              DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Enemy: 100/100", (int)cubeScreenPosition.x - MeasureText("Enemy: 100/100", 20)/2, 
                    (int)cubeScreenPosition.y, 20, BLACK);

            DrawText(TextFormat("Cube position in screen space coordinates: [%i, %i]", (int)cubeScreenPosition.x, (int)cubeScreenPosition.y), 10, 10, 20, LIME);
            DrawText("Text 2d should be always on top of the cube", 10, 40, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadModelAnimations(anims, animCount);
    UnloadModel(model);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
