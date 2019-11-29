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

    // store program arguments as string
    std::vector<std::string> v_arg;
    for(int i = 1; i < argc; i++){
        v_arg.push_back(argv[i]);
    }

    // vector string to store lines from stdin
    std::vector<std::string> v_input;
    std::string line;

    // parse the input
    while (std::cin >> line) {

        // put element into input vector
        v_input.push_back(line);
    }

    // find the location of each parameter in input vectors
    for(int i = 0; i < v_arg.size(); i++){
        std::cout << where(v_arg.at(i), v_input) << std::endl;
    }

    return 0;
}
