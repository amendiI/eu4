#include <iostream>

#include "graph.hpp"
#include "graphtypes.hpp"
#include "neighbors.hpp"

int main() {
    graphnode** graph;
    init_graph(&graph);
    get_neighbors(graph);

    dealloc_graph(graph);
    int i = 45;
    char c = 'c' ;  
    std::cout << "Hello World!\n";
    
    return 0;   
}