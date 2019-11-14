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

    std::vector<std::vector<double>> m;
    std::string line;

    while (getline(std::cin,line)) {
        if (line.empty()) {
            break;
        }

        std::istringstream s(line);
        std::vector<double> v;
        double d;
        while(s >> d) {
            v.push_back(d);
            if(s.get() == '\n'){
                break;
            }
        }
        m.push_back(v);
    }

    for(int i = 0; i < m.size(); i++){
        std::vector<double> v = m.at(i);
        sort(v);
        std::cout << getMin(v) << ' ' << getMax(v) << ' ' << getMean(v) << ' ' << getQuartile(v, n) << std::endl;
    }

    for(int i = 0; i < m[0].size(); i++){
        std::vector<double> v;
        for(int j = 0; j < m.size(); j++) {
            v.push_back(m.at(j).at(i));
        }
        sort(v);
        std::cout << getMin(v) << ' ' << getMax(v) << ' ' << getMean(v) << ' ' << getQuartile(v, n) << std::endl;
    }

    std::vector<double> diag;
    for(int i = 0; i < m.size(); i++){
        diag.push_back(m.at(i).at(i));
    }
    sort(diag);
    std::cout << getMin(diag) << ' ' << getMax(diag) << ' ' << getMean(diag) << ' ' << getQuartile(diag, n) << std::endl;

    std::vector<double> lt;
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j < i; j++){
            lt.push_back(m.at(i).at(j));
        }

    }
    sort(lt);
    std::cout << getMin(lt) << ' ' << getMax(lt) << ' ' << getMean(lt) << ' ' << getQuartile(lt, n) << std::endl;

}