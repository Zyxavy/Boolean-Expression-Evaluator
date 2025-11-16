#include "tTable.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"

void printTruthTable(const std::string &expression)
{
    //Tokenize and parse the expression
    auto tokens = tokenize(expression);
    auto postfix = toPostfix(tokens);

    //Extract unique variables
    std::set<char> vars;
    for (const Token &tk : postfix)
    {
        if(tk.type == TokenType::VAR) vars.insert(tk.varName); 
    }

    const int n = vars.size();
    if (n == 0)
    {
        std::cout << "No variables!\n"; 
        return;
    }


    for(char v : vars) std::cout << v << ' ';
    std::cout << "| " << expression << '\n';

    for(std::size_t i = 0; i < n*2 + 2 + expression.size(); i++) std::cout << '-';
    std::cout << '\n';

    for(int i = 0; i < (1 << n); ++i) //Iterate through all combinations of variable assignments
    {
        std::map<char, bool> row;
        int k = 0;
        for(char v : vars) row[v] = (i >>k++) & 1;

        for (char v : vars) std::cout << (row[v] ? '1' : '0') << ' ';
        std::cout << "| " << std::boolalpha << evaluate(postfix, row) << '\n';
    } 
}