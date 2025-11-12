#pragma once

#include <vector>
#include <string>
#include <cctype>

enum class TokenType {VAR, OP, LPAREN, RPAREN}; //variable, operator, left parenthesis, right parenthesis
enum class OpType {NOT, AND, OR, XOR, NONE}; 

struct Token 
{
    TokenType type;
    char varName{}; //if type is VAR
    OpType op{}; //if type is OP
};

std::vector<Token> tokenize(const std::string &expression);