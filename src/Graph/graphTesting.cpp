#include <iostream>
#include "Graph.h"
#include "DNode.h"
#include "../Algorithms/Dijkstra.h"
//#include "Algorithms/dijkstra.h"

int main(){

	std::cout << "Up and running...\n" << std::endl;

	Graph<char> g(10);

	int nodeId0 = g.addNode('a');
	int nodeId1 = g.addNode('b');
	int nodeId2 = g.addNode('c');
	int nodeId3 = g.addNode('d');
	int nodeId4 = g.addNode('e');
    int nodeId5 = g.addNode('f');
    int nodeId6 = g.addNode('g');
    int nodeId7 = g.addNode('h');


	std::cout << "Node 1 value: " << g.getNodeVal(nodeId1).first << std::endl;
	std::cout << "Node 2 value: " << g.getNodeVal(nodeId2).first << std::endl;
	std::cout << "Node 3 value: " << g.getNodeVal(nodeId3).first << std::endl;
	std::cout << "Node 4 value: " << g.getNodeVal(nodeId4).first << std::endl;
	std::cout << "Node 5 value: " << g.getNodeVal(nodeId5).first << std::endl << std::endl;

	g.addEdge(nodeId0,nodeId1,314);
	g.addEdge(nodeId1,nodeId3,216);
	g.addEdge(nodeId1,nodeId4,1337);
    g.addEdge(nodeId1, nodeId5, 512);
    g.addEdge(nodeId1, nodeId2, 16);
    g.addEdge(nodeId2, nodeId5, 16);

	std::cout << "Edge value between Node 1 and Node 2: " << g.getEdgeVal(nodeId1,nodeId2).first << std::endl;
	std::cout << "Edge value between Node 2 and Node 4: " << g.getEdgeVal(nodeId2,nodeId4).first << std::endl;
	std::cout << "Edge value between Node 2 and Node 5: " << g.getEdgeVal(nodeId2,nodeId5).first << std::endl;
	//std::cout << "Edge value between Node 5 and Node 2: " << g.getEdgeVal(nodeId2,nodeId5).first << std::endl;

	std::cout << "\nGraph Size: " << g.getNumNodes() << std::endl;


	// Testing DNode creation
	DNode dn1(0 , 1 , 100);
	DNode dn2(1);

	std::cout << "\n" << std::endl;

	std::cout << "Dijkstra Node 1" << std::endl;
	std::cout << "Node Id: " << dn1.getNodeId() << std::endl;
	std::cout << "Last Node Id: " << dn1.getLastNodeId() << std::endl;
	std::cout << "Weight: " << dn1.getTotalWeight() << std::endl;

	std::cout << "\nDijkstra Node 2" << std::endl;
	std::cout << "Node Id: " << dn2.getNodeId() << std::endl;
	std::cout << "Last Node Id: " << dn2.getLastNodeId() << std::endl;
	std::cout << "Weight: " << dn2.getTotalWeight() << std::endl;

	std::cout << "\nApplying Setters...\n" << std::endl;

	dn1.setNodeId(20);
	dn1.setLastNodeId(15);
	dn1.setTotalWeight(999.80);

	std::cout << "Dijkstra Node 1" << std::endl;
	std::cout << "Node Id: " << dn1.getNodeId() << std::endl;
	std::cout << "Last Node Id: " << dn1.getLastNodeId() << std::endl;
	std::cout << "Weight: " << dn1.getTotalWeight() << std::endl;

    for(Node<char> n : Dijkstra(g,nodeId0,nodeId5)){
		cout << n.id << " - " << n.data << endl;
	}
/*
    try {
        auto n2Connections = g.getConnections(6);

        for (int i = 0; i < n2Connections.size(); ++i) {
            std::cout << "Node 6 is connected with node " << n2Connections.at(i).first->id << " via an edge with value " << n2Connections.at(i).second << std::endl;
        }
    } catch(Graph<char,int>::NodeNotFound & e) {
        std::cout << "Could not find any node with id: " << e.id << std::endl;
    }


    //Testing Dijkstra's Algorithm
    std::cout << "Testing Dijkstra's Algorithm" << std::endl;
    auto path = getShortestPath(g, g.getNodeByIndex(nodeId1), g.getNodeByIndex(nodeId6));

    for (auto node : path) {
        std::cout << "--" << node.data << std::endl;
    }*/

	std::cout << "\nProgram ran successfully.\n" << std::endl;

	return 0;
}
