#include "parser.hpp"
#include <stdexcept>
#include <iostream>

static int precedence(OpType op)
{
    switch (op)
    {
        case OpType::NOT: return 3;
        case OpType::AND: return 2;
        case OpType::OR: return 1;
        case OpType::XOR: return 0;    
        default: return -1;
    }
}

static bool isRightAssociative(OpType op)
{
    return op == OpType::NOT;
}



std::vector<Token> toPostfix(const std::vector<Token> &tokens)
{
    //init stack and queue
    std::vector<Token> outputQueue;
    std::stack<Token> opStack;

    for (const Token &t : tokens) //iterate through each token
    {
        if(t.type == TokenType::VAR) //if token is a variable then enqueue
        {
            outputQueue.push_back(t);
        }
        else if(t.type == TokenType::LPAREN)
        {
            opStack.push(t);
        }
        else if(t.type == TokenType::RPAREN)
        {
            while(!opStack.empty() && opStack.top().type != TokenType::LPAREN) //while top of stack is not LPAREN
            {
                //pop from stack and enqueue
                outputQueue.push_back(opStack.top()); 
                opStack.pop();
            }

            if(opStack.empty())
            {
                throw std::runtime_error("Mismatched ')'"); //error if no matching LPAREN
            }
            opStack.pop();
        }
        else if(t.type == TokenType::OP)
        {
            //while there is an operator at the top of the operator stack with greater precedence
           while (!opStack.empty() && opStack.top().type == TokenType::OP &&
                (precedence(opStack.top().op) > precedence(t.op) ||
                (precedence(opStack.top().op) == precedence(t.op) && !isRightAssociative(t.op)))) 
                {
                    outputQueue.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(t);
        }
    }

    while (!opStack.empty()) //pop remaining operators from stack to queue
    {
        if(opStack.top().type == TokenType::LPAREN) throw std::runtime_error("Mismatched '('");
        outputQueue.push_back(opStack.top());
        opStack.pop();
    }
    return outputQueue;
}