#include "evaluator.hpp"
#include <stdexcept>


bool evaluate(const std::vector<Token> &postfix, const std::map<char, bool> &vars)
{
    std::stack<bool> valStack;

    for(const Token &tk : postfix) //Iterate through each token in the postfix expression
    {
        if(tk.type == TokenType::VAR) 
        {
            auto it = vars.find(tk.varName); //Find the variable in the provided map

            if(it == vars.end()) //Variable not found
            {
                throw std::runtime_error("Undefined variable");
            }
            valStack.push(it->second); //Push the variable's value onto the stack
        }
        else if(tk.type == TokenType::OP)
        {
            switch (tk.op)
            {
                case OpType::NOT:
                {
                    if(valStack.empty()) throw std::runtime_error("Stack underflow");
                    bool a = valStack.top();
                    valStack.pop();
                    valStack.push(!a); //Push the negated value
                    break;
                }
                case OpType::AND:
                {
                    if(valStack.size() < 2) throw std::runtime_error("Stack underflow");
                    bool b = valStack.top();
                    valStack.pop();
                    bool a = valStack.top();
                    valStack.pop();
                    valStack.push(a && b); //Push the AND result
                    break;
                }
                case OpType::OR:
                {
                    if(valStack.size() < 2) throw std::runtime_error("Stack underflow");
                    bool b = valStack.top();
                    valStack.pop();
                    bool a = valStack.top();
                    valStack.pop();
                    valStack.push(a || b); //Push the OR result
                    break;
                }
                case OpType::XOR:
                {
                    if(valStack.size() < 2) throw std::runtime_error("Stack underflow");
                    bool b = valStack.top();
                    valStack.pop();
                    bool a = valStack.top();
                    valStack.pop();
                    valStack.push(a ^ b); //Push the XOR result
                    break;
                }
                default: throw std::runtime_error("Unknown Operator");
            }
        }
        else
        {
            //INC
        }
    }
    //Final result should be the only value on the stack
    if(valStack.size() != 1) throw std::runtime_error("Ill-formed expression?"); 
    
    return valStack.top();
}