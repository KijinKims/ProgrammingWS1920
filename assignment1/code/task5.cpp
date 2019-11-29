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
            std::vector<double> sub(v.begin() + v.size() / 2 + 1, v.end());
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

    // make vector for storing data as matrix
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

    // for every row, sort and print required measures
    for(int i = 0; i < v_data.size(); i++){
        std::vector<double> v = v_data.at(i);
        sort(v);
        std::cout << getMin(v) << ' ' << getMax(v) << ' ' << getMean(v) << ' ' << getQuartile(v, n) << std::endl;
    }
    // for every column, sort and print required measures
    for(int i = 0; i < v_data[0].size(); i++){
        std::vector<double> v;
        for(int j = 0; j < v_data.size(); j++) {
            v.push_back(v_data.at(j).at(i));
        }
        sort(v);
        std::cout << getMin(v) << ' ' << getMax(v) << ' ' << getMean(v) << ' ' << getQuartile(v, n) << std::endl;
    }

    // for diagonal elements, sort and print required measures
    std::vector<double> diag;
    for(int i = 0; i < v_data.size(); i++){
        diag.push_back(v_data.at(i).at(i));
    }
    sort(diag);
    std::cout << getMin(diag) << ' ' << getMax(diag) << ' ' << getMean(diag) << ' ' << getQuartile(diag, n) << std::endl;

    // make vector for lower triangle and store elements
    std::vector<double> lt;
    for(int i = 0; i < v_data.size(); i++){
        for(int j = 0; j < i; j++){
            lt.push_back(v_data.at(i).at(j));
        }

    }
    // for lower triangle elements, sort and print required measures
    sort(lt);
    std::cout << getMin(lt) << ' ' << getMax(lt) << ' ' << getMean(lt) << ' ' << getQuartile(lt, n) << std::endl;

}