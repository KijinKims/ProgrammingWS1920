#include <iostream>
#include <vector>
#include <string>

// operate binary search
int binarySearch(std::vector<std::string>& input_v, int low, int high, std::string x)
{
    if (low > high)
        return -1;

    int mid = (low + high)/2;

    if (x == input_v.at(mid))
        return mid;

    else if (x < input_v.at(mid))
        return binarySearch(input_v, low,  mid - 1, x);

    else
        return binarySearch(input_v, mid + 1,  high, x);
}

// find the location of argument in input vector with binary search
std::string binaryWhere(std::string arg, std::vector<std::string>& input_v){

    int loc = binarySearch(input_v, 0, (int)input_v.size(), arg) ;
    if(loc == -1){
        return "not found";
    }
    else{
        return std::to_string(loc + 1);
    }
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
        std::cout << binaryWhere(arg_v.at(i), input_v) << std::endl;
    }

    return 0;
}
