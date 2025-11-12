#pragma once

#include "tokenizer.hpp"
#include <vector>
#include <stack>

//helper functions
int precedence(OpType op);
bool isRightAssociative(OpType op);

std::vector<Token> toPostfix(const std::vector<Token> &tokens); //converts infix tokens to postfix notation using the Shunting Yard algorithm