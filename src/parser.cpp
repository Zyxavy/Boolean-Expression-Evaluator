#include "parser.hpp"
#include <stdexcept>

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

