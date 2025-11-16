#include "layout.hpp"
#include <cstring>   
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include <set>
#include <map>
#include <string>
#include <iostream>

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

//Text
int textSize = 27;
int textX = inputBox.x + 5;
int textY = inputBox.y + (inputBox.height - textSize)/2;

//buffer
char expression[100] = "";
bool focused = true;
int key;

void mainLayout()
{
    ClearBackground(mainColor);
    DrawText("WINDOW OK", 10, 10, 20, RED);

    //Shapes
    DrawRectangleRec(inputBox, secColor); 
    DrawRectangleRec(outputBox, quatColor);
    DrawRectangleRec(exitButton, terColor);
    DrawRectangleRec(confirmButton, terColor);

    //Text
    DrawText(expression, textX, textY, textSize, quiColor);
    DrawRectangleLinesEx(inputBox, 2, focused ? YELLOW : WHITE);

    DrawText(TextFormat("BUF:%s", expression),inputBox.x + 5, inputBox.y + inputBox.height + 5,20, GREEN); //For debuging

    EndDrawing();
}

void handleTyping()
{

    while((key = GetKeyPressed()) != 0)
    {    
        DrawText(TextFormat("Keypressed: %d", key), 40, 4, 25, BLACK); //For debuging

        if (key >= KEY_A && key <= KEY_Z) 
        { 
           std::size_t len = strlen(expression);

            if (len + 1 < sizeof(expression)) 
            {
                expression[len]   = 'A' + (key - KEY_A); // force upper
                expression[len+1] = '\0';
            }
            
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE) && strlen(expression) > 0) expression[strlen(expression) - 1] = '\0';
}