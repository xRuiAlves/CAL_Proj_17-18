#include <iostream>
#include "../Utilities/exceptions.h"
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"

int main() {

    std::cout << "Starting tests ..." << std::endl;

    Graph g1 = Graph();

    u_int id0 = g1.addNode(0,0,"Rio Tinto aka DORGAS");
    u_int id1 = g1.addNode(10, 10, "Maia");
    u_int id2 = g1.addNode(2,2,"Areosa");
    u_int id3 = g1.addNode(-10, -10, "Sra da Hora");
    u_int id4 = g1.addNode(-15, -15, "Matosinhos");
    u_int id5 = g1.addNode(-10, -5, "S. Mamede");

    g1.addEdge(id0,id2,2);
    g1.addEdge(id0,id1,2);
    g1.addEdge(id1, id3, 4);
    g1.addEdge(id3, id1, 3);
    g1.addEdge(id3, id4, 2);
    g1.addEdge(id5,id4,1);
    g1.addEdge(id4,id5,1);
    g1.addEdge(id5, id0, 5);

    Dijkstra d = Dijkstra(g1, g1.getNodeById(id0), g1.getNodeById(id5));
    d.calcOptimalPath();
    d.printSolution();

    Dijkstra d2 = Dijkstra(g1, g1.getNodeById(id0), g1.getNodeById(id0));
    d2.calcOptimalPath();
    d2.printSolution();

    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
