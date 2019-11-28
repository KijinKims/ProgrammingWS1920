#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// to ge the contents of vector easily ----will be depricated
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

// check if base pair is complimentary
bool compliment(char& a, char& b){
    set<pair<char, char>> s {make_pair('A', 'U'), make_pair('U', 'A'),
                             make_pair('C', 'G'), make_pair('G', 'C'),
                             make_pair('G', 'U'), make_pair('U', 'G')};

    return s.find(make_pair(a, b)) != s.end();
}

// calculate the best score for range (i, j) and also trace the corresponding secondary structure
int calculate(string s, vector<vector<int>>& m, vector<vector<vector<set<pair<int,int>>>>>& tb, int i, int j){

    // if loop is smaller than 2, secondary structure cannot be made
    if(i >= j-2)
        return 0;

    // temporary vector for storing secondary structure for index i,j
    vector<set<pair<int,int>>> tmp;

    // check if best score can be made from sum of scores of range(i, k-1) and range(k+1, j-1) added by 1 (k and j)
    int max_comp = 0;
    // k can be from i to j-3 (because if k is j-2, it cannot make structure)
    for(int k = i; k < j-2; k++){
        // we will only find the best score
        if(compliment(s[k], s[j]) && m[i][k-1] + m[k+1][j-1] + 1 >= max_comp) {
            // if score is bigger than current score, it becomes current best score and temporary vector becomes empty
            if(m[i][k-1] + m[k+1][j-1] + 1 > max_comp){
                max_comp = m[i][k - 1] + m[k + 1][j - 1] + 1;
                tmp.clear();
            }

            // if score is current best score, corresponding structure will be added to temporary vector
            // in addition to new pair(k,j), all combination structures from range(i, k-1) and range(k+1, j-1) will be pushed into vector
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

            // if final vector is empty, only pair (k,j) will be pushed to vector.
            if(tmp.empty()){
                set<pair<int,int>> empty_set;
                empty_set.insert(make_pair(k,j));
                tmp.push_back(empty_set);
            }
        }
    }

    // if range(i, j-1) has score as same as current best score,
    // all secondary structures will be added
    if(m[i][j-1] == max_comp){
        for(auto& e : tb[i][j-1])
            tmp.push_back(e);
    }
    // if range(i, j-1) has bigger score than current best score,
    // vector becomes empty and all secondary structure from range(i,j-1) will be added
    else if(m[i][j-1] > max_comp){
        max_comp = m[i][j-1];
        tmp.clear();
        for(auto& e : tb[i][j-1])
            tmp.push_back(e);
    }

    // save tmp into table
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
    // return best score
    return max_comp;
}

// convert integer pair into string
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
        cout << "0" << endl;
        return
    }

    // make dynamic programming matrix
    vector<vector<int>> m;
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

    cout<<m[1][len]<<endl;
    set<string> string_s;
    unsigned size = tb[1][len].size();
    for(auto& e :tb[1][len]) string_s.insert( convertToString(e, len) );
    for(auto& e :string_s){
        cout<<e<<endl;
    }

    return 0;
}
