#include "tokenizer.hpp"
#include <iostream>


std::vector<Token> tokenize(const std::string &expression)
{
    std::vector<Token> output;

    for(size_t i = 0; i < expression.size(); ) //iterate through expression
    {
        char c = expression[i];

        if(std::isspace(c)) ++i; continue; //skip whitespace


        //Check if Operators or Parenthesis
        if(c == '!') 
        {
            output.push_back({TokenType::OP, 0, OpType::NOT});
            ++i;
            continue;
        }

        if(c == '(')
        {
            output.push_back({TokenType::LPAREN});
            ++i;
            continue;
        } 

        if(c == ')')
        {
            output.push_back({TokenType::RPAREN});
            ++i;
            continue;
        } 

        if(c == '&' && i + 1 < expression.size() && expression[i + 1] == '&')
        {
            output.push_back({TokenType::OP, 0, OpType::AND});
            i += 2; //skip next character as well
            continue;
        }

        if(c == '|' && i + 1 < expression.size() && expression[i + 1] == '|')
        {
            output.push_back({TokenType::OP, 0, OpType::OR});
            i += 2;
            continue;
        }

        if(c == '^')
        {
            output.push_back({TokenType::OP, 0, OpType::XOR});
            ++i;
            continue;
        }

        //Check if Variables
        if(c >= 'A' && c <= 'Z')
        {
            output.push_back({TokenType::VAR, c, OpType::NONE});
            ++i;
            continue;
        }

        throw std::runtime_error(std::string("Unknown char: ") + c); //throw error on unknown character

    }

    return output;
}