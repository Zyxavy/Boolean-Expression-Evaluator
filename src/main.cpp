#include "raylib.h"

int main()
{
    InitWindow(800,480,"Logic Calculator");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Boolean Expression Evaluator",10,10,20,DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}