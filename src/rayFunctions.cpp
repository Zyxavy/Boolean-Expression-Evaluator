#include "rayFunctions.hpp"
#include <cstring>   
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include <set>
#include <map>
#include <iostream>
#include <cctype>

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

bool tableVisible = false;
std::string errorMsg;
std::vector<Token> postfixed;
std::vector<Token> tokens;

//Drawing or Layout
void mainLayout()
{
    ClearBackground(mainColor);

    //Shapes
    DrawRectangleRec(inputBox, secColor); 
    DrawRectangleRec(outputBox, quatColor);
    DrawRectangleRec(exitButton, terColor);
    DrawRectangleRec(confirmButton, terColor);

    //Text
    DrawText(expression, textX, textY, textSize, quiColor);
    DrawRectangleLinesEx(inputBox, 2, focused ? YELLOW : WHITE);
    DrawText("Submit", confirmButton.x + 7, confirmButton.y + 5, 20, WHITE);
    DrawText("X", exitButton.x + 20, exitButton.y + 6, 20, WHITE);

    if(tableVisible && errorMsg.empty()) //draw truth table
    {
        //similar to function in tTable.cpp
        try 
        {
            std::set<char> vars;
            for (const Token &tk : postfixed) if (tk.type == TokenType::VAR) vars.insert(tk.varName);

            const int n = vars.size();
            if (n == 0)
            {
                DrawText("No Variables!", outputBox.x + 20, outputBox.y + 10, 35, RED);
                return;
            }

            int x = outputBox.x + 5;
            for (char v : vars)
            {
                const char* label = TextFormat("%c ", v);
                DrawText(label, x, outputBox.y + 2, 35, BLACK);
                x += MeasureText(label, 35);
            }

            DrawText("| ", x, outputBox.y + 2, 35, BLACK);
            x += MeasureText("| ", 35);
            DrawText(expression, x, outputBox.y + 2, 35, BLACK);

            DrawLine(outputBox.x, outputBox.y + 40, outputBox.x + outputBox.width, outputBox.y + 40, BLACK);

            int y = outputBox.y + 50;
            for (int i = 0; i < (1 << n); ++i)
            {
                std::map<char, bool> row;
                int k = 0;
                for (char v : vars)
                {
                    row[v] = (i >> k) & 1;
                    k++;
                }

                x = outputBox.x + 10;
                for (char v : vars)
                {
                    const char* bit = TextFormat("%d ", (int)row[v]);
                    DrawText(bit, x, y, 35, BLACK);
                    x += MeasureText(bit, 35);
                }

                bool res = false;
                try 
                {
                    res = evaluate(postfixed, row);
                    DrawText(res ? "true" : "false", x + 10, y, 35, res ? GREEN : RED);
                } catch (const std::exception& e) 
                {
                    DrawText("ERR", x + 10, y, 30, YELLOW);
                }
                y += 35;
            }
        }
        catch(const std::exception& e)
        {
            DrawText("Evaluation Error!", outputBox.x + 20, outputBox.y + 10, 35, RED);
            return;
        }
    
    }
    else if(!errorMsg.empty())
    {
        DrawText("Input Error!", outputBox.x + 20, outputBox.y + 10, 35, RED);
    }

    //Handle logic:
    Vector2 mousePos = GetMousePosition();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(CheckCollisionPointRec(mousePos, exitButton))
        {
            CloseWindow();
        }
        else if(CheckCollisionPointRec(mousePos, confirmButton))
        {
            submitButtonPressed();
        }
    }

    EndDrawing();
}

//Logic
void handleTyping()
{

    while((key = GetKeyPressed()) != 0)
    {    

        if (key >= KEY_A && key <= KEY_Z) 
        { 
            std::size_t len = strlen(expression);// current length
            if (len + 1 >= sizeof(expression)) return;// prevent overflow

            expression[len] = 'A' + (key - KEY_A); // force upper
            expression[len+1] = '\0';

        
        }
        else if(key == KEY_SEVEN)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;
            
            expression[len] = '&';
            expression[len+1] = '&';
            expression[len+2] = '\0';
            
        }
        else if(key == KEY_BACKSLASH)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;

            expression[len] = '|';
            expression[len+1] = '|';
            expression[len+2] = '\0';
            
        }
        else if(key == KEY_SIX)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;
        
            expression[len] = '^';
            expression[len+1] = '\0';
                
        }
        else if(key == KEY_ONE)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;
            
            expression[len] = '!';
            expression[len+1] = '\0';
                
            
        }
        else if(key == KEY_NINE)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;
            
            expression[len] = '(';
            expression[len+1] = '\0';  
            
        }
        else if(key == KEY_ZERO)
        {
            std::size_t len = strlen(expression);
            if (len + 1 >= sizeof(expression)) return;
            
            expression[len] = ')';
            expression[len+1] = '\0';
                
            
        }

        tableVisible = false;
        errorMsg.clear();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && strlen(expression) > 0) 
    {
        expression[strlen(expression) - 1] = '\0';
        tableVisible = false;
        errorMsg.clear();
    }
}

void submitButtonPressed()
{
    //process expression
    if(!isValidExpression(expression))
    {
        errorMsg = "Invalid expression syntax";
        tableVisible = false;
        return;
    }
    try
    {
        tokens = tokenize(expression);
        postfixed = toPostfix(tokens);
        errorMsg.clear();
        tableVisible = true;
    }
    catch(const std::exception& e)
    {
        errorMsg = e.what();
        DrawText("Processing error!", outputBox.x + 20, outputBox.y + 10, 35, RED);
        tableVisible = false;
    }



}

bool isValidExpression(const std::string& expression)
{
    if(expression.empty()) 
    {
        return false;
    }

    int parenBalance = 0;//tracks parentheses balance
    bool expectOperand = true; //true if we expect an operand next, false if we expect an operator
    
    for(size_t i = 0; i < expression.size(); ) 
    {
        char c = expression[i];

        if(std::isspace(c)) 
        {
            ++i;
            continue;
        }

        //Unary operator
        if(c == '!') 
        {
            if(!expectOperand) return false; 
            ++i;
            continue;
        }

        if(c == '(') 
        {
            if(!expectOperand) return false;
            parenBalance++;
            ++i;
            expectOperand = true;
            continue;
        }

        if(c == ')') 
        {
            if(expectOperand || parenBalance <= 0) return false;
            parenBalance--;
            ++i;
            expectOperand = false; 
            continue;
        }

        //Two-character operators
        if(c == '&' && i + 1 < expression.size() && expression[i + 1] == '&') 
        {
            if(expectOperand) return false;
            i += 2;
            expectOperand = true;
            continue;
        }

        if(c == '|' && i + 1 < expression.size() && expression[i + 1] == '|') 
        {
            if(expectOperand) return false;
            i += 2;
            expectOperand = true;
            continue;
        }

        //Single-character operators
        if(c == '^') 
        {
            if(expectOperand) return false;
            ++i;
            expectOperand = true;
            continue;
        }

        // Variables
        if(c >= 'A' && c <= 'Z') 
        {
            if(!expectOperand) return false;
            ++i;
            expectOperand = false;
            continue;
        }
        return false;
    }

    if(parenBalance != 0) return false; // Unbalanced parentheses
    if(expectOperand) return false;// Expression ends unexpectedly

    return true;
}
       