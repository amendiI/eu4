#include "graphtypes.hpp"
#include <cstddef>
#include "constants.hpp"

int init_graph(graphnode*** out) {
    graphnode** graph = new graphnode*[N_PROV];

    for (uint16_t i = 0; i < N_PROV; i++) {
        province_data* pdata = new province_data{};
        graph[i] = new graphnode{i, pdata, 0, 0, NULL};
    }
    *out = graph;
    return 0;
}

int dealloc_graph(graphnode** graph) {
    for (int i = 0; i < N_PROV; i++) {
        delete graph[i]->data;
        delete graph[i];
    }
    delete graph;
    return 0;
}