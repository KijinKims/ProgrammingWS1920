#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

// check if sequence is palindrome
bool isPalindrome(std::string seq){
    std::string seq_c = seq;
    std::reverse(seq_c.begin(), seq_c.end());
    // compare original sequence and reversed sequence
    if(seq == seq_c){
        return true;
    }
    else{
        return false;
    }
}

// check the validity of each base and if valid, count the base
void checkAndCount(std::string& seq, std::string& id, std::map<char,int>& base_counts, std::vector<std::string>& pal_v){
        if(!seq.empty()){
            // convert small letter to capital and thymine into urasil
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
                // if any base is not valid, output its header on the standard error stream
                else{
                    std::cerr<<id;
                    id.clear();
                    seq.clear();
                    break;
                }
            }
        }

        // with valid sequence, check if it's palindrome and check counts of base
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

    // make map storing count of each base
    std::map<char, int> base_counts;
    base_counts['A'] = 0;
    base_counts['C'] = 0;
    base_counts['G'] = 0;
    base_counts['U'] = 0;
    std::vector<std::string> pal_v;

    // file stream
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    // initial some variables
    std::string line;
    std::string seq, id;
    int line_n = 0, seq_n = 0;
    while(getline(input, line)){
        // count number of lines
        line_n++;
        // skip empty line
        if(line.empty()){
            continue;
        }

        // if it meets id line, check the validity and counts base of sequece of previous id
        if(line[0] == '>'){
            checkAndCount(seq, id, base_counts, pal_v);

            // store id
            id = line.substr(1);
            // count number of sequence
            seq_n++;
        }
        else{
            // if line is sequence line, it will be added to sequence
            seq = seq + line;
        }
    }
    // because last sequence cannot meet id line, operate check and count once more
    checkAndCount(seq, id, base_counts, pal_v);

    // sum base counts
    int sum = base_counts['A'] + base_counts['C'] + base_counts['G'] + base_counts['U'];

    // print all information
    std::cout << "Lines: " << line_n << std::endl;
    std::cout << "Sequences: " << seq_n << std::endl;
    std::cout << "AU ratio: " << (double) (base_counts['A'] + base_counts['U']) / sum << std::endl;
    std::cout << "A: " << (double) base_counts['A'] / sum << std::endl;
    std::cout << "C: " << (double) base_counts['C'] / sum << std::endl;
    std::cout << "G: " << (double) base_counts['G'] / sum << std::endl;
    std::cout << "U: " << (double) base_counts['U'] / sum << std::endl;

    // write palindrome sequence into output file
    for(int i = 0; i < pal_v.size(); i++){
        output<<pal_v.at(i)<<std::endl;
    }

    return 0;
}
