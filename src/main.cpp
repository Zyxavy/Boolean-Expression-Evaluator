#include "tokenizer.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

std::string toString(const Token& t) {
    switch (t.type) {
        case TokenType::VAR: return std::string(1, t.varName);
        case TokenType::LPAREN: return "(";
        case TokenType::RPAREN: return ")";
        case TokenType::OP:
            switch (t.op) {
                case OpType::NOT: return "!";
                case OpType::AND: return "&&";
                case OpType::OR:  return "||";
                case OpType::XOR: return "^";
                default: return "?";
            }
    }
    return "?";
}

int main() {
    std::string line;
    std::getline(std::cin, line);          // !(A || B) && C ^ D
    auto v  = tokenize(line);
    auto pf = toPostfix(v);
    for (const auto& tok : pf) std::cout << toString(tok) << ' ';
    std::cout << '\n';
}