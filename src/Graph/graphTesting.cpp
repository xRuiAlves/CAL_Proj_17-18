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


    Dijkstra<char> dijkstra1(graph1);
	dijkstra1.calcOptimalPath(0,5);
	dijkstra1.printSolution();





	// Initialize Graph 2 (Empty Graph)
	std::cout << "\n\n***************************************";
	std::cout << "\nTesting Graph 2 (Empty Graph) ..." << std::endl;
	Graph<unsigned int> graph2(0);

	Dijkstra<unsigned int> dijkstra2(graph2);
	dijkstra2.calcOptimalPath(0,5);
	dijkstra2.printSolution();





	// Initialize Graph 3 (No solution)
	std::cout << "\n\n***************************************";
	std::cout << "\nTesting Graph 3 (Impossible Solution Graph) ..." << std::endl;
	Graph<bool> graph3(5);

	nodeId0 = graph3.addNode(true);
	nodeId1 = graph3.addNode(true);
	nodeId2 = graph3.addNode(false);
	nodeId3 = graph3.addNode(true);

	graph3.addEdge(nodeId0,nodeId1,13);
	graph3.addEdge(nodeId0,nodeId2,15);
	graph3.addEdge(nodeId2,nodeId0,20);
	graph3.addEdge(nodeId3,nodeId2,71.75);
	graph3.addEdge(nodeId3,nodeId0,71.75);

	Dijkstra<bool> dijkstra3(graph3);
	dijkstra3.calcOptimalPath(nodeId0,nodeId3);
	dijkstra3.printSolution();


	std::cout << "\nProgram ran successfully." << std::endl;

	return 0;
}