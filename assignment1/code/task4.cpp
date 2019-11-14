#include <iostream>
#include <vector>
#include <string>

// find the location of argument in input vector
std::string where(std::string arg, std::vector<std::string>& input_v){
    for(int i = 0; i < input_v.size(); i++){
        if(arg == input_v.at(i)){
            return std::to_string(i+1);
        }
    }
    return "not found";
}

int main(int argc, char* argv[]) {

    // vector of string to store parameters
    std::vector<std::string> arg_v;
    for(int i = 0; i < argc; i++){
        arg_v.push_back(argv[i]);
    }

    // vector string to store lines from stdin
    std::vector<std::string> input_v;
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty())
            break;
        input_v.push_back(line);
    }

    // find the location of each parameter in input vectors
    for(int i = 1; i < arg_v.size(); i++){
        std::cout << where(arg_v.at(i), input_v) << std::endl;
    }

    return 0;
}
