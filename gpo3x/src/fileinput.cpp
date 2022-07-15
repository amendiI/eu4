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

int get_terrain(graphnode** graph) {
    std::ifstream file("../data/terrain.txt");
    std::string str;
    terrain current = UNDEFINED;
    while(std::getline(file, str)) {
        if (str.size() == 0) {
            continue;
        }
        if (str.last() == 125) { //ascii "}"
            continue;
        }
        if (str.last() == 123) { //ascii "{"
            size_t space = str.find(" ");
            std::string land = str.substr(0, space);
            switch (land) {
                case "grasslands":
                    current = GRASSLANDS;
                    break;
                case "farmlands":
                    current = FARMLANDS;
                    break;
                case "drylands":
                    current = DRYLANDS;
                    break;
                case "coastline":
                    current = COASTLINE;
                    break;
                case "savannah":
                    current = SAVANNAH;
                    break;
                case "woods":
                    current = WOODS;
                    break;
                case "forest":
                    current = FOREST;
                    break;
                case "highlands":
                    current = HIGHLANDS;
                    break;
                case "steppe":
                    current = STEPPES;
                    break;
                case "hills":
                    current = HILLS;
                    break;
                case "marsh":
                    current = MARSH;
                    break;
                case "coastal_desert":
                    current = COASTAL_DESERT;
                    break;
                case "jungle":
                    current = JUNGLE;
                    break;
                case "mountain":
                    current = MOUNTAIN;
                    break;
                case "desert":
                    current = DESERT;
                    break;
                case "glacier":
                    current = GLACIAL;
                    break;
                default:
                    current = UNDEFINED;
                    std::wout << "Unexpected terrain: " << land << "\n";
            }
        } else {
            //Read provinces
            while (str.size() != 0) {
                size_t space = str.find(" ");
                if (space != 0) {
                    uint16_t id = std::stoi(str.substr(0, space));
                    graph[id]->data.terrain = current;
                }
                str.erase(0, space+1);
            }
        }
    }
}

int get_climate(graphnode** graph) {
    std::ifstream file("../data/climate.txt");
    std::string str;
    climate current = TEMPERATE;
    while(std::getline(file, str)) {
        if (str.size() == 0) {
            continue;
        }
        if (str.last() == 125) { //ascii "}"
            continue;
        }
        if (str.last() == 123) { //ascii "{"
            size_t space = str.find(" ");
            std::string land = str.substr(0, space);
            switch (land) {
                case "tropical":
                    current = TROPICAL;
                    break;
                case "arid":
                    current = ARID;
                    break;
                case "arctic":
                    current = ARCTIC;
                    break;
                default:
                    current = TEMPERATE;
                    std::cout << "Other climate: " << land << "\n";
            }
        } else if (current != TEMPERATE) {
            //Read provinces
            while (str.size() != 0) {
                size_t space = str.find(" ");
                if (space != 0) {
                    uint16_t id = std::stoi(str.substr(0, space));
                    graph[id]->data.climate = current;
                }
                str.erase(0, space+1);
            }
        }
    }
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