#include <iostream>
#include "../Utilities/exceptions.h"
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"

int main() {

    std::cout << "Starting tests ..." << std::endl;

    Graph g1 = Graph();

    u_int id0 = g1.addNode(0,0,"Rio Tinto");
    u_int id1 = g1.addNode(10, 10, "Maia");
    u_int id2 = g1.addNode(2,2,"Areosa");
    u_int id3 = g1.addNode(-10, -10, "Sra da Hora");
    u_int id4 = g1.addNode(-15, -15, "Matosinhos");
    u_int id5 = g1.addNode(-10, -5, "S. Mamede");
    u_int id6 = g1.addNode(-1000, 1000, "Castro d'Aire");

    g1.addEdge(id0,id2,2);
    g1.addEdge(id0,id1,2);
    g1.addEdge(id1, id3, 4);
    g1.addEdge(id3, id1, 3);
    g1.addEdge(id3, id4, 2);
    g1.addEdge(id5,id4,1);
    g1.addEdge(id4,id5,1);

    Dijkstra d = Dijkstra(g1);

    // Impossible Case #1
    d.calcOptimalPath(g1.getNodeById(id5), g1.getNodeById(id3));
    d.printSolution();

    // Regular Scenario
    d.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id5));
    d.printSolution();

    // Impossible Case #2 (Isolated Node)
    d.calcOptimalPath(g1.getNodeById(id6), g1.getNodeById(id0));
    d.printSolution();

    // Self-Node path
    d.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id0));
    d.printSolution();
    


    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
