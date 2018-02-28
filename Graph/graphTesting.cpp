#include <iostream>
#include "Graph.h"

int main(){

	std::cout << "Up and running...\n" << std::endl;

	Graph<char,int> g(10);

	int nodeId1 = g.addNode('a');
	int nodeId2 = g.addNode('b');
	int nodeId3 = g.addNode('c');
	int nodeId4 = g.addNode('d');
	int nodeId5 = g.addNode('e');

	std::cout << "Node 1 value: " << g.getNodeVal(nodeId1).first << std::endl;
	std::cout << "Node 2 value: " << g.getNodeVal(nodeId2).first << std::endl;
	std::cout << "Node 3 value: " << g.getNodeVal(nodeId3).first << std::endl;
	std::cout << "Node 4 value: " << g.getNodeVal(nodeId4).first << std::endl;
	std::cout << "Node 5 value: " << g.getNodeVal(nodeId5).first << std::endl << std::endl;

	g.addEdge(nodeId1,nodeId2,314);
	g.addEdge(nodeId2,nodeId4,216);
	g.addEdge(nodeId2,nodeId5,1337);

	std::cout << "Edge value between Node 1 and Node 2: " << g.getEdgeVal(nodeId1,nodeId2).first << std::endl;
	std::cout << "Edge value between Node 2 and Node 4: " << g.getEdgeVal(nodeId2,nodeId4).first << std::endl;
	std::cout << "Edge value between Node 2 and Node 5: " << g.getEdgeVal(nodeId2,nodeId5).first << std::endl;
	std::cout << "Edge value between Node 5 and Node 2: " << g.getEdgeVal(nodeId2,nodeId5).first << std::endl;

	std::cout << "\nGraph Size: " << g.getNumNodes() << std::endl;


	std::cout << "\nProgram ran successfully.\n" << std::endl;

	return 0;
}
