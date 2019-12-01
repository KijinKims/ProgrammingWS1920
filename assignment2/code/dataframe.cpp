#include "dataframe.hpp"
#include <iostream>

using namespace std;

std::ostream& operator<<(std::ostream& os, const Dataframe& df){
    int nrows = df.data.back().size();
    for(int i = 0; i < nrows; i++){
        for(auto p = df.data.begin(); p != df.data.end(); p++)
            os << ((*p).at(i)->get()) << '\t';
        cout << endl;
    }
}
