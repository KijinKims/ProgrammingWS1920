#include <iostream>
#include <vector>
#include <string>

// operate binary search for x in input vector
int binarySearch(std::vector<std::string>& v_input, int low, int high, std::string x)
{
    // if low becomes bigger than high, it means no element matched in the vector
    if (low > high)
        return -1;

    // set mid point
    int mid = (low + high)/2;

    // if mid point matches with x, return it
    if (x == v_input.at(mid))
        return mid;

    // if x is smaller than mid, continue search within the left range
    else if (x < v_input.at(mid))
        return binarySearch(v_input, low,  mid - 1, x);

    // if x is bigger than mid, continue search within the right range
    else
        return binarySearch(v_input, mid + 1,  high, x);
}

// find the location of argument in input vector with binary search
std::string binaryWhere(std::string x, std::vector<std::string>& input_v){

    // if value exist, return the result of binarySearch function, otherwise, return 'not found'
    int loc = binarySearch(input_v, 0, (int)input_v.size() - 1, x) ;

    if(loc == -1){
        return "not found";
    }
    else{
        // when returning, convert loc into 1-based numbering
        return std::to_string(loc + 1);
    }
}

int main(int argc, char* argv[]) {

    // // store program arguments as string
    std::vector<std::string> v_arg;
    for(int i = 1; i < argc; i++){
        v_arg.push_back(argv[i]);
    }

    // vector string to store lines from stdin
    std::vector<std::string> v_input;
    std::string seq;

    // parse the input
    while (std::cin >> seq) {
        // put element into input vector
        v_input.push_back(seq);
    }

    // find the location of each parameter in input vectors
    for(int i = 0; i < v_arg.size(); i++){
        std::cout << binaryWhere(v_arg.at(i), v_input) << std::endl;
    }

    return 0;
}
