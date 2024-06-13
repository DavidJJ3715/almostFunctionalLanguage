#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> tokenize(std::string input)
{
    std::vector<std::string> tokenList;
    for(size_t i=0; i < input.size(); ++i)
    {
        if(input.at(i) == ' ') {}
        else if(input.at(i) == '\n') {}
        else {std::cout << input[i];}
    }
    return tokenList;
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

    std::vector<std::string> tokenList = tokenize(input);

    return 0;
}