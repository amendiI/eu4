#include "graphtypes.hpp"
#include <cstddef>

int init_graph(graphnode*** out) {
    graphnode** graph = new graphnode*[4940];

    for (uint16_t i = 0; i < 4940; i++) {
        province_data* pdata = new province_data{};
        graph[i] = new graphnode{i, pdata, 0, NULL};
    }
    *out = graph;
    return 0;
}

int dealloc_graph(graphnode** graph) {
    for (int i = 0; i < 4940; i++) {
        delete graph[i]->data;
        delete graph[i];
    }
    delete graph;
    return 0;
}