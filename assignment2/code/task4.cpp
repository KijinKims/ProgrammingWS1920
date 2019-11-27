#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

ostream& operator<<(ostream& os, vector<set<pair<int, int>>>& v){
    for (int i = 0; i < v.size(); ++i) {
        for (auto& j : v.at(i))
        {
            os << j.first << " " << j.second << "  ";
        }
        os<<endl;
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

int calculate(string s, vector<vector<int>>& m, vector<vector<vector<set<pair<int,int>>>>>& tb, int i, int j){

    if(i >= j-2)
        return 0;

    vector<set<pair<int,int>>> tmp;

    int max_comp = 0;
    for(int k = i; k < j-2; k++){
        if(compliment(s[k], s[j]) && m[i][k-1] + m[k+1][j-1] + 1 >= max_comp) {
            if(m[i][k-1] + m[k+1][j-1] + 1 > max_comp){
                max_comp = m[i][k - 1] + m[k + 1][j - 1] + 1;
                tmp.clear();
            }

            if(!tb[i][k-1].empty()){
                for(auto& e : tb[i][k-1]){
                    if(!tb[k+1][j-1].empty()){
                        for(auto& f : tb[k+1][j-1]){
                            set<pair<int, int>> result;
                            result = e;
                            result.insert(f.begin(), f.end());
                            result.insert(make_pair(k, j));
                            tmp.push_back(result);
                        }
                    }
                    else{
                        set<pair<int, int>> result;
                        result = e;
                        result.insert(make_pair(k, j));
                        tmp.push_back(result);
                    }
                }
            }
            else{
                for(auto& f : tb[k+1][j-1]){
                    set<pair<int, int>> result;
                    result = f;
                    result.insert(make_pair(k, j));
                    tmp.push_back(result);
                }
            }

            if(tmp.empty()){
                set<pair<int,int>> empty_set;
                empty_set.insert(make_pair(k,j));
                tmp.push_back(empty_set);
            }
        }
    }

    if(m[i][j-1] == max_comp){
        for(auto& e : tb[i][j-1])
            tmp.push_back(e);
    }
    else if(m[i][j-1] > max_comp){
        max_comp = m[i][j-1];
        tmp.clear();
        tmp = tb[i][j-1];
    }

    tb[i][j] = tmp;

/*
    cout<<"i is "<<i<<". j is "<<j<<endl;
    for (int x = 1; x < tb.size(); ++x) {
        for (int y = 1; y < tb.at(x).size(); ++y) {
            cout << "i: "<< x << " j: "<<y<<endl;
            cout << tb[x][y];
        }
    }
*/

    return max_comp;
}

string convertToString(set<pair<int,int>> s, int len){
    string init(len, '.');

    for(auto& p: s){
        init[p.first-1] = '(';
        init[p.second-1] = ')';
    }
    return init;
}

int main(int argc, const char* argv[]) {

    string s;

    while (cin >> s) {
    }

    s = " " + s;

    int len = s.length() - 1;

    if(len <= 3){
        cout << "sequence is too short to have secondary structure." << endl;
        exit(1);
    }

    // make dynamic programming matrix
    vector< vector<int> > m;
    vector<vector<vector<set<pair<int,int>>>>> tb;

    m.resize(len+1);
    tb.resize(len+1);
    for(int i = 0 ; i < len+1 ; ++i)
    {
        m[i].resize(len+1);
        tb[i].resize(len+1);
    }



    for(int k = 3; k < len; k++){
        for(int i = 1; i <= len - k; i++){
            int j = i + k;
            m[i][j] = calculate(s, m, tb, i, j);
        }
    }

    for(int i = len; i > 1; i--){
        int j = len;
        if(m[i][j] == m[1][j])
            for(auto& e :tb[i][j])
                tb[1][j].push_back(e);
    }

    /*
    for (int i = 1; i < m.size(); ++i) {
        for (int j = 1; j < m.at(i).size(); ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
     */

    cout<<m[1][len]<<endl<<endl;
    set<string> string_s;
    unsigned size = tb[1][len].size();
    for(auto& e :tb[1][len]) string_s.insert( convertToString(e, len) );
    for(auto& e :string_s){
        cout<<e<<endl<<endl;
    }

    return 0;
}
