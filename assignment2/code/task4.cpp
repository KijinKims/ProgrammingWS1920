#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// check if base pair is complimentary
bool compliment(char& a, char& b){
    set<pair<char, char>> s {make_pair('A', 'U'), make_pair('U', 'A'),
                             make_pair('C', 'G'), make_pair('G', 'C'),
                             make_pair('G', 'U'), make_pair('U', 'G')};

    return s.find(make_pair(a, b)) != s.end();
}

// calculate the best score for range (i, j) and also trace the corresponding secondary structure
int calculate(string s, vector<vector<int>>& m, vector<vector<vector<set<pair<int,int>>>>>& tb, int i, int j){

    // temporary vector for storing secondary structure for range(i,j)
    vector<set<pair<int,int>>> tmp;

    // check if best score can be made from sum of scores of range(i, k-1), range(k+1, j-1) added by 1 (k and j)
    int max_comp = 0;
    // k can be from i to j-3 (because if k is bigger than j-2, range(k,j) cannot make structure)
    for(int k = i; k < j-2; k++){
        // we will only find the best score
        if(compliment(s[k], s[j]) && m[i][k-1] + m[k+1][j-1] + 1 >= max_comp) {
            // if score is bigger than current score, it becomes current best score and temporary vector becomes empty
            if(m[i][k-1] + m[k+1][j-1] + 1 > max_comp){
                max_comp = m[i][k - 1] + m[k + 1][j - 1] + 1;
                tmp.clear();
            }

            // if sum of scores is current best score, corresponding structure will be added to temporary vector
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

    // if best score is 0, vector should not be saved
    if (max_comp == 0){
        return 0;
    }

    // save secondary structures into table
    tb[i][j] = tmp;

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
    // take input string
    string s;

    while(cin >> s){
    }
    // make 1-digit indexing
    s = " " + s;

    int len = s.length() - 1;
    // if length of string is smaller than 0, it cannot make any structure
    if(len <= 3){
        cout << "0" << endl;
        return 0;
    }

    // make dynamic programming matrix
    vector<vector<int>> m;
    // make matrix for storing secondary structures
    vector<vector<vector<set<pair<int,int>>>>> tb;

    // initialize the matrices
    m.resize(len+1);
    tb.resize(len+1);
    for(int i = 0 ; i < len+1 ; ++i)
    {
        m[i].resize(len+1);
        tb[i].resize(len+1);
    }

    // initialize the matrix
    for(int i = 0; i <= len; i++){
        int j = i-1;
        m[i][j] = 0;
    }
    // initialize the matrix
    for(int k = 0; k <= 2; k++){
        for(int i = 1; i <= len - k; i++){
            int j = i + k;
            m[i][j] = 0;
        }
    }

    // calculate the best score and secondary structure
    for(int k = 3; k < len; k++){
        for(int i = 1; i <= len - k; i++){
            int j = i + k;
            m[i][j] = calculate(s, m, tb, i, j);
        }
    }

    // because there is minimum loop length, all best secondary structures are not saved into 1,len index
    // so it shoud be collected from cells around the position
    for(int k = 1; k <=3 ; k++) {
        for (int j = len - 3 + k; j <= len; j++) {
            if(m[k][j] == m[1][j] && (k!=1 && j!=len)) {
                for (auto &e :tb[k][j])
                    tb[1][j].push_back(e);
            }
        }
    }

    // print the best score
    cout<<m[1][len]<<endl;
    set<string> string_s;
    // print string-converted secondary structures
    for(auto& e :tb[1][len]) string_s.insert( convertToString(e, len) );
    for(auto& e :string_s){
        cout<<e<<endl;
    }

    return 0;
}
