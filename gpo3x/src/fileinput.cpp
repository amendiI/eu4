#include "graphtypes.hpp"

#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

int get_neighbors(graphnode** graph) {

    std::ifstream file("../data/neighbors.txt");
    std::string str;
    std::vector<uint16_t> wspace;
    while(std::getline(file, str)) {
        size_t separator = str.find(":");
        std::string provstr = str.substr(0, separator);
        int province = std::stoi(provstr);
        str.erase(0, separator+1);
        
        
        for (uint16_t i = 0; i < str.size(); i++) {
            if (str.at(i) == 32) {
                wspace.push_back(i);
            }
        }
        uint16_t nn = wspace.size()+1;
        uint16_t* neighbors = new uint16_t[nn];
        int base = 0;
        uint16_t i;
        for (i = 0; i < wspace.size(); i++) {
            provstr = str.substr(base, wspace[i]-base);
            neighbors[i] = std::stoi(provstr);
            base = wspace[i]+1;
        }
        neighbors[i] = std::stoi(str.substr(base, std::string::npos));
        graph[province]->n_neighbors = nn;
        graph[province]->neighbors = neighbors;

        wspace.clear();
    }
    return 0;
}