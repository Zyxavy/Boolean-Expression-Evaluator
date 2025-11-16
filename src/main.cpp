#include <layout.hpp>

int main()
{
    InitWindow(800,480,"Logic Calculator");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_BACK > KEY_F12)) {handleInputs();}


        //Draw
        mainLayout();
    }
    CloseWindow();

    return 0;
}