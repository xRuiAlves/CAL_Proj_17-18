#include <iostream>
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"

int main(){

	std::cout << "Starting tests ..." << std::endl;


	// Initialize Graph 1
	std::cout << "\n\n***************************************";
	std::cout << "\nTesting Graph 1 ..." << std::endl;

	Graph<char> graph1(10);

	int nodeId0 = graph1.addNode('a');
	int nodeId1 = graph1.addNode('b');
	int nodeId2 = graph1.addNode('c');
	int nodeId3 = graph1.addNode('d');
	int nodeId4 = graph1.addNode('e');
    int nodeId5 = graph1.addNode('f');
    int nodeId6 = graph1.addNode('g');
    int nodeId7 = graph1.addNode('h');

	graph1.addEdge(nodeId0,nodeId1,314);
	graph1.addEdge(nodeId1,nodeId3,216);
	graph1.addEdge(nodeId1,nodeId4,1337);
	graph1.addEdge(nodeId1, nodeId5, 512);
	graph1.addEdge(nodeId1, nodeId2, 16);
	graph1.addEdge(nodeId2, nodeId5, 16);


    Dijkstra<char> dijkstra1(graph1,graph1.getNodeById(0), graph1.getNodeById(5));
	dijkstra1.calcOptimalPath();
	dijkstra1.printSolution();

	std::cout << "\nProgram ran successfully." << std::endl;

	return 0;
}
