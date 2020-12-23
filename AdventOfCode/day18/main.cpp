#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <map>

std::vector<std::string> get_lines(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return lines;
    }

    std::string line;
    while (getline(infile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

enum TokenType
{
    NUMBER,
    PLUS,
    TIMES,
    LPAREN,
    RPAREN,
    WHITESPACE
};

struct Token
{
    TokenType type;
    long long value;
};

std::vector<Token> get_tokens(std::string line)
{
    std::vector<Token> tokens;

    bool in_num = false;
    std::string numStr = "";

    for (int i = 0; i < line.size(); ++i)
    {
        Token t;
        if (line[i] == ' ')
        {   
            if (in_num)
            {
                in_num = false;
                long long num = std::stoll(numStr);
                numStr = "";
                t.type = TokenType::NUMBER;
                t.value = num;
            }
            else 
            {
                continue;
            } 
        }
        else if (isdigit(line[i]))
        {
            if (!in_num)
            {
                in_num = true;
            }

            numStr += line[i];
            continue;
        }
        else if (line[i] == '+')
        {
            t.type = TokenType::PLUS;
        }
        else if (line[i] == '*')
        {
            t.type = TokenType::TIMES;
        }
        else if (line[i] == '(')
        {
            t.type = TokenType::LPAREN;
        }
        else if (line[i] == ')')
        {
            if (in_num)
            {
                in_num = false;
                long long num = std::stoi(numStr);
                numStr = "";
                Token newToken;
                newToken.type = TokenType::NUMBER;
                newToken.value = num;
                tokens.push_back(newToken);
            }

            t.type = TokenType::RPAREN;
        }
        tokens.push_back(t);
    }

    if (in_num)
    {
        Token t;
        in_num = false;
        long long num = std::stoll(numStr);
        numStr = "";
        t.type = TokenType::NUMBER;
        t.value = num;
        tokens.push_back(t);
    }

    return tokens;
}

void print(Token t)
{
    switch (t.type)
    {
        case TokenType::PLUS:
            std::cout << "'+'";
            break;
        case TokenType::TIMES:
            std::cout << "'*'";
            break;
        case TokenType::LPAREN:
            std::cout << "'('";
            break;
        case TokenType::RPAREN:
            std::cout << "')'";
            break;
        case TokenType::NUMBER:
            std::cout << "'Number': " << t.value;
            break;
    }

    return;
}

long long eval(std::vector<Token> tokens)
{
    std::stack<Token> tokenStack;

    // std::cout << "Tokens size: " << tokens.size() << std::endl;
    int counter = 0;
    tokenStack.push(tokens[counter++]);

    for (int i = 1; i < tokens.size(); ++i)
    {
        Token token = tokens[i];

        #define DEBUG
        #ifdef DEBUG

        // std::cout << "Current: ";
        // print(token);
        // std::cout << " \t\t Top: ";
        // print(tokenStack.top());
        // std::cout << "\n";

        #endif

        if (token.type == TokenType::NUMBER)
        {
            Token topToken = tokenStack.top();
            if (topToken.type == TokenType::PLUS || topToken.type ==  TokenType::TIMES)
            {
                Token op = tokenStack.top();
                tokenStack.pop();
                Token leftOperand = tokenStack.top();
                tokenStack.pop();

                Token newToken;
                newToken.type = TokenType::NUMBER;

                if (op.type == TokenType::PLUS)
                {
                    newToken.value = leftOperand.value + token.value;
                }
                else if (op.type == TokenType::TIMES)
                {
                    newToken.value = leftOperand.value * token.value;
                }

                tokenStack.push(newToken);
            }
            else if (topToken.type == TokenType::LPAREN)
            {
                tokenStack.push(token);
            }
        }
        else if (token.type == TokenType::PLUS || token.type == TokenType::TIMES)
        {
            tokenStack.push(token);
        }
        else if (token.type == TokenType::LPAREN)
        {
            tokenStack.push(token);
        }
        else if (token.type == TokenType::RPAREN)
        {
            Token rightOperand = tokenStack.top();
            Token newToken = rightOperand;
            tokenStack.pop();
            tokenStack.pop(); // left paren

            if (tokenStack.size())
            {
                Token topToken = tokenStack.top();
                if (topToken.type == TokenType::PLUS || topToken.type ==  TokenType::TIMES)
                {
                    Token op = tokenStack.top();
                    tokenStack.pop();
                    Token leftOperand = tokenStack.top();
                    tokenStack.pop();

                    newToken.type = TokenType::NUMBER;

                    if (op.type == TokenType::PLUS)
                    {
                        newToken.value = leftOperand.value + rightOperand.value;
                    }
                    else if (op.type == TokenType::TIMES)
                    {
                        newToken.value = leftOperand.value * rightOperand.value;
                    }
                }
            }
            
            tokenStack.push(newToken);
        }
    }

    return tokenStack.top().value;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day18.txt");
    std::vector<std::vector<Token>> token_seqs;
    
    std::transform(lines.begin(), lines.end(), std::back_inserter(token_seqs), [](std::string line) {
        return get_tokens(line);
    });

    long long sum = 0;
    for (auto seq: token_seqs)
    {
        long long result = eval(seq);
        sum += result;
        std::cout << "result: " << result << ", sum: " << sum << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num token seqs: " << token_seqs.size() << std::endl;

    return 0;
}