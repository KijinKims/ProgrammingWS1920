#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

// sort given vector as increasing order
void sort(std::vector<double>& v) {
    std::sort(v.begin(), v.end());
}

// get the minimum value among elements of vector
double getMin(std::vector<double>& v){
    return v.front();
}

// get the maximum value among elements of vector
double getMax(std::vector<double>& v){
    return v.back();
}

// get the mean value of elements of vector
double getMean(std::vector<double>& v){
    return std::accumulate(v.begin(), v.end(), 0.0)/v.size();
}

// get the median value of elements of vector
double getMedian(std::vector<double>& v){
    if (v.size() % 2 == 0) {
        return (v.at(v.size() / 2 - 1) + v.at(v.size() / 2)) / 2;
    } else {
        return v.at(v.size() / 2);
    }
}

// get the quartile value of elements of vector for given type of quartile
double getQuartile(std::vector<double>& v, int n) {
    switch(n){
        // get first quartile
        case 1: {
            std::vector<double> sub(v.begin(), v.begin() + v.size() / 2);
            return getMedian(sub);
        }
        // get median
        case 2: {
            return getMedian(v);
        }
        // get third quartile
        case 3: {
            std::vector<double> sub(v.begin() + (v.size() / 2) + 1, v.end());
            return getMedian(sub);
        }
        default:
            throw std::invalid_argument( "invalid argument for quartile" );
    }
}

int main(int argc, char* argv[]) {

    // store program argument as integer
    std::istringstream iss(argv[1]);
    int n;
    iss >> n;

	// make vector for storing data
	std::vector<std::vector<double>> v_data;

	// get input as standard input and save it to the data vector
	double d;
	std::vector<double> v_input;

	// parse the input
	while (std::cin >> d) {

        // put element into input vector
        v_input.push_back(d);

	    // if it comes new line, put input vector into data vector and flush it
	    if (std::cin.get() == '\n') {
	        if (v_input.size() == 0){
	            continue;
	        }
            v_data.push_back(v_input);
	        v_input.clear();
        }
	}

	// for every data set, sort and print required measures
	for(int i = 0; i < v_data.size(); i++){
        sort(v_data[i]);
        std::cout << getMin(v_data[i]) << ' ' << getMax(v_data[i]) << ' ' << getMean(v_data[i]) << ' ' << getQuartile(v_data[i], n) << std::endl;
    }
}
