#pragma once

#include <vector>
#include <string>

enum class TokenType {VAR, OP, LPAREN, RPAREN};
enum class OpType {NOT, AND, OR, XOR, NONE};

struct Token 
{
    TokenType type;
    char varName{}; //if type is VAR
    OpType op{}; //if type is OP
};

std::vector<Token> Tokenize(const std::string& expression);