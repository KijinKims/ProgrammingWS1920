#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

void sort(std::vector<double>& v) {
    std::sort(v.begin(), v.end());
}

double getMin(std::vector<double>& v){
    return v.front();
}

double getMax(std::vector<double>& v){
    return v.back();
}

double getMean(std::vector<double>& v){
    return std::accumulate(v.begin(), v.end(), 0.0)/v.size();
}

double getMedian(std::vector<double>& v){
    if (v.size() % 2 == 0) {
        return (v.at(v.size() / 2 - 1) + v.at(v.size() / 2)) / 2;
    } else {
        return v.at(v.size() / 2);
    }
}

double getQuartile(std::vector<double>& v, int n) {
    switch(n){
        case 1: {
            std::vector<double> sub(v.begin(), v.begin() + v.size() / 2);
            return getMedian(sub);
        }
        case 2: {
            return getMedian(v);
        }
        case 3: {
            std::vector<double> sub(v.begin() + v.size() / 2 + 1, v.end());
            return getMedian(sub);
        }
    }
}

int main(int argc, char* argv[]) {

    std::istringstream iss(argv[1]);
    int n;
    iss >> n;

    while(1) {
        std::vector<double> v;

        double d;
        while (std::cin >> d) {
            v.push_back(d);
            if (std::cin.get() == '\n') {
                break;
            }
        }

        sort(v);
        std::cout << getMin(v) << ' ' << getMax(v) << ' ' << getMean(v) << ' ' << getQuartile(v, n) << std::endl;
    }
}
