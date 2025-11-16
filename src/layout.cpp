#include "layout.hpp"

//Colors
Color mainColor = {32, 91, 122, 255};
Color secColor = {162,187,207,255};
Color terColor = {20,47,68,255};
Color quatColor = {29,56,73,255};
Color quiColor = {0,0,0,255};

//Buttons and Boxes
Rectangle inputBox = {24, 32, 744, 56};
Rectangle outputBox = {16, 136, 768, 312};
Rectangle exitButton = {720, 3, 80, 24};
Rectangle confirmButton = {680, 96, 88, 32};

void mainLayout()
{

    BeginDrawing();
    ClearBackground(mainColor);

    DrawRectangleRec(inputBox, secColor);
    DrawRectangleRec(outputBox, quatColor);
    DrawRectangleRec(exitButton, terColor);
    DrawRectangleRec(confirmButton, terColor);

    EndDrawing();
}

void handleInputs()
{
    if(IsKeyPressed(KEY_A))
    {
        DrawText("A", inputBox.x + 3, inputBox.y + 3, 25, BLACK);
    }
}