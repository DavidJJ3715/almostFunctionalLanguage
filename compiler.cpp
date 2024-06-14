#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <utility>

enum tokens
{
    token_whitespace,
    token_let,
    token_be,
    token_is,
    token_if,
    token_elif,
    token_else,
    token_then,
    token_main,
    token_void,
    token_leftParentheses,
    token_rightParentheses,
    token_hash,
    token_print,
    token_throw,
    token_semicolon,
    token_arrow,
    token_leftBrace,
    token_rightBrace,
    token_identifier,
    token_endLine,
    token_true,
    token_false,
    token_and,
    token_or,
};

std::map<std::string,tokens> match = 
{
    {"let", token_let},
    {"be", token_be},
    {"is", token_is},
    {"if", token_if},
    {"elif", token_elif},
    {"else", token_else},
    {"then", token_then},
    {"main", token_main},
    {"void", token_void},
    {"(", token_leftParentheses},
    {")", token_rightParentheses},
    {"{", token_leftBrace},
    {"}", token_rightBrace},
    {"#", token_hash},
    {"print", token_print},
    {"throw", token_throw},
    {";", token_semicolon},
    {"->", token_arrow},
    {"true", token_true}, {"True", token_true},
    {"false", token_false}, {"False", token_false},
    {"and", token_and},
    {"or", token_or},
};

std::vector<tokens> tokenList;
std::vector<std::string> varList;

void tokenize(std::string input)
{
    std::string buffer;

    auto it = input.begin();
    while(it != input.end())
    {
        if(buffer == "print(")
        {
            buffer.clear();
            while(*it != ';') 
            {
                buffer.push_back(*it);
                ++it;
            }
            tokenList.push_back(token_print);
            tokenList.push_back(token_identifier);
            tokenList.push_back(token_semicolon);
            buffer.pop_back();
            varList.push_back(buffer);
            buffer.clear();
        }
        else if(buffer == "throw(\"")
        {
            buffer.clear();
            while(*it != '"')
            {
                buffer.push_back(*it);
                ++it;
            }
            ++it; ++it;
            tokenList.push_back(token_throw);
            tokenList.push_back(token_identifier);
            tokenList.push_back(token_semicolon);
            varList.push_back(buffer);
            buffer.clear();
        }
        if(*it == '#')
            {while(*it != '\n' && it != input.end()) {++it;}}
        else if(*it != ' ' && *it != ';' && *it != '\n')
            {buffer.push_back(*it); ++it;}
        else
        {
            if(!buffer.empty())
            {
                auto it = match.find(buffer);
                if(it == match.end())
                {
                    tokenList.push_back(token_identifier);
                    varList.push_back(buffer);
                }
                else
                    {tokenList.push_back(match[buffer]);}
                buffer.clear();
            }
            if(*it == ';') {tokenList.push_back(token_semicolon);}
            ++it;
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
        {std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl; return 1;}

    std::ifstream file(argv[1]);
    if(!file.is_open())
        {std::cerr << "Failed to open the file: " << argv[1] << std::endl; return 1;}

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();
    file.close();

    tokenize(input);
    std::cout << tokenList.size() << " " << varList.size() << "\n";
    for(auto it : varList)
        {std::cout << it << " ";}
    return 0;
}