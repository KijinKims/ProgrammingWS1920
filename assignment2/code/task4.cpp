#include <iostream>
#include <vector>
#include <string>

using namespace std;


int calculate(string s, vector< vector<int> > m, int i, int j){

    if(i >= j-2)
        return 0;

    int max_comp = 0;
    for(int k = i; k < j-2; k++){
        if(s[k] == s[j] & m[i][k-1] + m[k+1][j-1] + 1 > max_comp)
            max_comp = m[i][k-1] + m[k+1][j-1] + 1;
    }

    return max(m[i][j-1], max_comp);
}

int main(int argc, const char* argv[]) {

    string s;

    cin >> s;

    s = " " + s;

    int len = s.length() - 1;

    if(len <= 3){
        cout << "sequence is too short to have secondary structure." << endl;
        exit(1);
    }

    // make dynamic programming matrix
    vector< vector<int> > m;

    m.resize(len+1);
    for(int i = 0 ; i < len+1 ; ++i)
    {
        m[i].resize(len+1);
    }

    for(int k = 3; k < len; k++){
        for(int i = 1; i <= len - k; i++){
            int j = i + k;
            m[i][j] = calculate(s, m, i, j);
        }
    }




    return 0;
}
