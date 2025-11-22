#include "rayFunctions.hpp"

int main()
{
    InitWindow(800,480,"Logic Calculator");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing(); 
        handleTyping();
        
        //Draw
        mainLayout();  
    }
    CloseWindow();

    return 0;
}


