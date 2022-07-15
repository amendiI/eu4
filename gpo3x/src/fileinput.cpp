#include "graphtypes.hpp"

#include <iostream>
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

int get_terrain(graphnode** graph) {
    std::ifstream file("../data/terrain.txt");
    std::string str;
    terrain current = UNDEFINED;
    while(std::getline(file, str)) {
        if (str.size() == 0) {
            continue;
        }
        while (str.back() == 20) { //ascii " "
            str.pop_back();
        }
        if (str.size() == 0) {
            continue;
        }
        if (str.back() == 125) { //ascii "}"
            continue;
        }
        if (str.back() == 123) { //ascii "{"
            size_t space = str.find(" ");
            std::string land = str.substr(0, space);
            if (!land.compare("grasslands")) {
                current = GRASSLANDS;
            } else if (!land.compare("farmlands")) {
                current = FARMLANDS;
            } else if (!land.compare("drylands")) {
                current = DRYLANDS;
            } else if (!land.compare("coastline")) {
                current = COASTLINE;
            } else if (!land.compare("savannah")) {
                current = SAVANNAH;
            } else if (!land.compare("woods")) {
                current = WOODS;
            } else if (!land.compare("forest")) {
                current = FOREST;
            } else if (!land.compare("highlands")) {
                current = HIGHLANDS;
            } else if (!land.compare("steppe")) {
                current = STEPPES;
            } else if (!land.compare("hills")) {
                current = HILLS;
            } else if (!land.compare("marsh")) {
                current = MARSH;
            } else if (!land.compare("coastal_desert")) {
                current = COASTAL_DESERT;
            } else if (!land.compare("jungle")) {
                current = JUNGLE;
            } else if (!land.compare("mountain")) {
                current = MOUNTAIN;
            } else if (!land.compare("desert")) {
                current = DESERT;
            } else if (!land.compare("glacier")) {
                current = GLACIAL;
            } else {
                current = UNDEFINED;
                std::cout << "WARNING: Unexpected terrain: " << land << "\n";
            }
        } else {
            //Read provinces
            while (str.size() != 0) {
                size_t space = str.find(" ");
                if (space != 0) {
                    uint16_t id = std::stoi(str.substr(0, space));
                    graph[id]->data->prov_terrain = current;
                }
                str.erase(0, space+1);
            }
        }
    }
    return 0;
}

int get_climate(graphnode** graph) {
    std::ifstream file("../data/climate.txt");
    std::string str;
    climate current = TEMPERATE;
    while(std::getline(file, str)) {
        if (str.size() == 0) {
            continue;
        }
        while (str.back() == 20) { //ascii " "
            str.pop_back();
        }
        if (str.size() == 0) {
            continue;
        }
        if (str.back() == 125) { //ascii "}"
            continue;
        }
        if (str.back() == 123) { //ascii "{"
            size_t space = str.find(" ");
            std::string land = str.substr(0, space);
            if (!land.compare("tropical")) {
                current = TROPICAL;
            } else if (!land.compare("arid")) {
                current = ARID;
            } else if (!land.compare("arctic")) {
                current = ARCTIC;
            } else {
                current = TEMPERATE;
                std::cout << "Not considering climate " << land << "\n";
            }
        } else if (current != TEMPERATE) {
            //Read provinces
            while (str.size() != 0) {
                size_t space = str.find(" ");
                if (space != 0) {
                    uint16_t id = std::stoi(str.substr(0, space));
                    graph[id]->data->prov_climate = current;
                }
                str.erase(0, space+1);
            }
        }
    }
    return 0;
}

int get_colors(uint16_t** table) {
    std::ifstream file("../data/definition.csv");
    std::string str;
    uint16_t sep[4];
    uint8_t count = 0;

    std::getline(file, str);
    while (std::getline(file, str)) {
        count = 0;
        for (uint16_t i = 0; i < str.size(); i++) {
            if (str[i] == 59) { //ascii 59: ";"
                sep[count] = i;
            }
        }
        uint16_t* entry = new uint16_t[4];
        entry[0] = std::stoi(str.substr(0, sep[0]));
        entry[1] = std::stoi(str.substr(sep[0]+1, sep[1]-sep[0]-1));
        entry[2] = std::stoi(str.substr(sep[1]+1, sep[2]-sep[1]-1));
        entry[3] = std::stoi(str.substr(sep[2]+1, sep[3]-sep[2]-1));

        table[entry[0]] = entry;
    }
    return 0;
}