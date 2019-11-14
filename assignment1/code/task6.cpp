#include <iostream>
#include <fstream>
#include <map>
#include <vector>

bool isPalindrome(std::string seq){
    std::string seq_c = seq;
    reverse(seq_c.begin(), seq_c.end());
    if(seq == seq_c){
        return true;
    }
    else{
        return false;
    }
}

void checkAndCount(std::string& seq, std::string& id, std::map<char,int>& base_counts, std::vector<std::string>& pal_v){
        if(!seq.empty()){
            for(int i = 0; i < seq.size(); i++){
                if(seq[i] == 'a'){
                    seq[i] = 'A';
                }
                if(seq[i] == 'g'){
                    seq[i] = 'G';
                }
                if(seq[i] == 'c'){
                    seq[i] = 'C';
                }
                if(seq[i] == 'u'){
                    seq[i] = 'U';
                }
                if(seq[i] == 'T' || seq[i] == 't'){
                    seq[i] = 'U';
                }
                if(seq[i] == 'A' || seq[i] == 'G' || seq[i] == 'C' || seq[i] == 'U'){
                    continue;
                }
                else{
                    std::cerr<<id;
                    id.clear();
                    seq.clear();
                    break;
                }
            }
        }

        if(!seq.empty()){
            if(isPalindrome(seq)){
                pal_v.push_back(seq);
            }

            for(auto e : seq){
                switch(e){
                    case 'A' :
                        base_counts['A']++;
                        break;

                    case 'C' :
                        base_counts['C']++;
                        break;

                    case 'G' :
                        base_counts['G']++;
                        break;

                    case 'U' :
                        base_counts['U']++;
                        break;
                }
            }
            seq.clear();
        }
};


int main(int argc, char* argv[]) {

    std::map<char, int> base_counts;
    base_counts['A'] = 0;
    base_counts['C'] = 0;
    base_counts['G'] = 0;
    base_counts['U'] = 0;
    std::vector<std::string> pal_v;

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    std::string line;
    std::string seq, id;
    int line_n = 0, seq_n = 0;
    while(getline(input, line)){
        line_n++;
        if(line.empty()){
            continue;
        }

        if(line[0] == '>'){
            checkAndCount(seq, id, base_counts, pal_v);

            id = line.substr(1);
            seq_n++;
        }
        else{
            seq = seq + line;
        }
    }
    checkAndCount(seq, id, base_counts, pal_v);

    int sum = base_counts['A'] + base_counts['C'] + base_counts['G'] + base_counts['U'];

    std::cout << "Lines: " << line_n << std::endl;
    std::cout << "Sequences: " << seq_n << std::endl;
    std::cout << "AU ratio: " << (double) (base_counts['A'] + base_counts['U']) / sum << std::endl;
    std::cout << "A: " << (double) base_counts['A'] / sum << std::endl;
    std::cout << "C: " << (double) base_counts['C'] / sum << std::endl;
    std::cout << "G: " << (double) base_counts['G'] / sum << std::endl;
    std::cout << "U: " << (double) base_counts['U'] / sum << std::endl;

    for(int i = 0; i < pal_v.size(); i++){
        output<<pal_v.at(i)<<std::endl;
    }

    return 0;
}
