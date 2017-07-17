
#include <map>
#include <string>
#include <stdio.h>
#include <TTree.h>
#include <TFile.h>
#include <stdint.h>
#include <TKey.h>

bool gAddAuto;
std::map<std::string, uint64_t> gNums;


void add_file(std::string file) {

    auto f = TFile::Open(file.c_str());
    if(!f) {
        fprintf(stderr, "can't open file %s; ignored\n", file.c_str());
        return;
    }

    if(gAddAuto) {
        auto keys = f->GetListOfKeys();
        TIter next(keys);
        TKey *key;
        for(;(key = (TKey*)next());) {

            auto obj = key->ReadObj();
            auto tree = dynamic_cast<TTree*>(obj);

            if(tree) {
                std::string tname = tree->GetName();
                gNums[tname] += tree->GetEntries();
            }

        }


    } else {
        
        for(auto it = gNums.begin(); it != gNums.end(); ++it) {
            auto &p = *it;
            auto obj = f->Get(p.first.c_str());
            if(!obj) continue;
            auto tre = dynamic_cast<TTree*>(obj);
            if(tre)
                p.second += tre->GetEntries();
        }
    }
    


    f->Close();
}

int main(int argc, char *argv[])
{

    if(argc == 1) {
        printf("count number of events of tree(s) in given file(s)\n");
        printf("usage: root_event_counter [-t tree_name]... <files...>\n");
        printf("    if no tree name is specified, all trees in root files will be counted\n");
    }

    std::vector<std::string> files;

    gAddAuto = true;
    for(int i = 1; i < argc; ++i) {

        char *arg = argv[i];
        if(strcmp("-t", arg) == 0) {
            ++i;
            if(i < argc) {
                char *tree = argv[i];
                gNums[tree] = 0;
                gAddAuto = false;
            } else {
                fprintf(stderr, "single -t will be ignored\n");
            }
        } else {
            files.push_back(argv[i]);
        }


    }
    

    for(size_t i = 0; i < files.size(); ++i) {
        
        add_file(files.at(i)); 
    }


    for(auto it = gNums.begin(); it != gNums.end(); ++it) {
        auto &p = *it;
        printf("%10s %10lld\n", p.first.c_str(), (long long)p.second);
    }
 

}

