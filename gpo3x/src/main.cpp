#include <iostream>

#include "graph.hpp"
#include "graphtypes.hpp"

int main() {
    graphnode** graph;
    init_graph(&graph);
    dealloc_graph(graph);
    int i = 45;
    char c = 'c' ;  
    std::cout << "Hello World!\n";
    
    return 0;   
}