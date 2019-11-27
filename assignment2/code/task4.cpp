#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;


ostream& operator<<(ostream& os, vector<pair<int, int>>& v){
    for (int i = 0; i < v.size(); ++i) {
        os << v.at(i).first << "," << v.at(i).second << " ";
    }
    os<<endl;
    return os;
}

bool compliment(char& a, char& b){
    set<pair<char, char>> s {make_pair('A', 'U'), make_pair('U', 'A'),
                                       make_pair('C', 'G'), make_pair('G', 'C'),
                                       make_pair('G', 'U'), make_pair('U', 'G')};

    return s.find(make_pair(a, b)) != s.end();
}

void traceback(vector< vector<int> > m, int i, int j, vector<pair<int, int>> v, string s){

    if (i >= j-2){
        cout << v;
        return;
    }

    if (m[i][j] == m[i][j-1])
        traceback(m, i, j-1, v, s);

    for (int k = i; k < j-2; ++k) {
        if(m[i][j] == m[i][k-1] + m[k+1][j-1] + 1 && compliment(s[k], s[j])){
            v.push_back(make_pair(k, j));
            traceback(m, i, k-1, v, s);
            traceback(m, k+1, j-1, v, s);
        }
    }
}

int calculate(string s, vector< vector<int> > m, int i, int j){

    if(i >= j-2)
        return 0;

    int max_comp = 0;
    for(int k = i; k < j-2; k++){
        if(compliment(s[k], s[j]) & m[i][k-1] + m[k+1][j-1] + 1 > max_comp)
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

    for (int i = 1; i < m.size(); ++i) {
        for (int j = 1; j < m.at(i).size(); ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    vector<pair<int, int>> v;

    traceback(m, 1, len, v, s);

    return 0;
}
