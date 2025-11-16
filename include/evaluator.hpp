#pragma once

#include "tokenizer.hpp"
#include <stack>
#include <vector>
#include <map>

bool evaluate(const std::vector<Token> &postfix, const std::map<char, bool> &vars);