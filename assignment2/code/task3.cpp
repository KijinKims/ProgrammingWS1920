#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

class Manager{
public:
    int dist = 0;
    int cluster_count = 1;
    map<string, int> chr_order = { {"chr1", 1}, {"chr2", 2}, {"chr3", 3},
                                   {"chr4", 4}, {"chr5", 5}, {"chr6", 6},
                                   {"chr7", 7}, {"chr8", 8}, {"chr9", 9},
                                   {"chr10", 10}, {"chr11", 11}, {"chr12", 12},
                                   {"chr13", 13}, {"chr14", 14}, {"chr15", 15},
                                   {"chr16", 16}, {"chr17", 17}, {"chr18", 18},
                                   {"chr19", 19}, {"chr20", 20}, {"chr21", 21},
                                   {"chr22", 22}, {"chrX", 23}, {"chrY", 24}};

};

class Gene{
private:
    string chr;
    int start;
    int end;
    int middle;
    int cluster = 0;

public:

    Gene(string chr, int start, int end):chr(chr), start(start), end(end) {
        middle = (start + end) / 2;
    }

    string getChr() const{
        return chr;
    }

    int getStart() const {
        return start;
    }

    int getEnd() const {
        return end;
    }

    int getCluster() const{
        return cluster;
    }

    void setCluster(Manager& manager){
        cluster = manager.cluster_count;
    }

    friend bool inSameChr(const Gene& gene, const Gene& otherGene);

    friend bool inSameCluster(const Gene& gene, const Gene& otherGene, Manager manager);

    friend ofstream& operator<<(ofstream& os, const Gene& gene);
};


bool inSameChr(const Gene& gene, const Gene& otherGene) {
    return gene.chr.compare(otherGene.chr) ==0;
}

bool inSameCluster(const Gene& gene, const Gene& otherGene, Manager manager){
    return abs(gene.middle - otherGene.middle) < manager.dist;
}

ofstream& operator<<(ofstream& os, const Gene& ge){
    os << ge.getChr() << '\t' << ge.getStart() << '\t' << ge.getEnd() << '\t' << "cluster=" << ge.getCluster() << endl;
    return os;
}

int main(int argc, const char* argv[]) {

    Manager manager;

    ifstream input(argv[1]);
    manager.dist = strtol(argv[2], NULL, 10);
    manager.cluster_count = 1;
    ofstream output(argv[3]);

    vector<Gene> v;
    string chr;
    int start;
    int end;
    string error_message;

    string line;
    while(getline(input, line)) {

        // skip empty line
        if(line.empty())
            continue;

        istringstream iss(line);
        iss >> chr >> start >> end;

        if ( manager.chr_order.find(chr) == manager.chr_order.end() ) {
            error_message = error_message + "Invalid chromosome name; ";
        }

        if(start > end){
            swap(start, end);
        }

        if(start < 0 || end < 0)
            error_message = error_message + "Start or end coordinate is below zero. Invalid coordinate; ";

        if(!v.empty()){
            if (manager.chr_order[v.back().getChr()] > manager.chr_order[chr])
                error_message = error_message + "Chromosome is not sorted; ";
            else if (v.back().getChr() == chr) {
                if (v.back().getStart() > start)
                    error_message = error_message + "Coordinate is not sorted; ";
            }
        }

        if(!error_message.empty()){
            error_message = "Error! " + error_message;
            cerr<<error_message<<endl;
            exit(1);
        }

        v.push_back(Gene(chr, start, end));

    }

    v.at(0).setCluster();
    for(int i = 0; i < v.size() - 1; i++){
        if(!inSameChr(v.at(i), v.at(i+1))) {
            manager.cluster_count++;
            v.at(i+1).setCluster(manager);
            continue;
        }

        if(!inSameCluster(v.at(i), v.at(i+1), manager))
            manager.cluster_count++;
        v.at(i+1).setCluster(manager);
    }

    for(auto& x: v){
        output<<x;
    }

    return 0;
}
