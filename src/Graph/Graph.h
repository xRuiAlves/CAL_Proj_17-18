#ifndef GRAPH_H_
#define GRAPH_H_

#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <vector>
#include <iostream>
#include <cstdlib>

#include "Node.h"


class Graph {
private:
	std::vector< Node > nodes;

	// Get the index of the node with id 'id' , -1 if not found
	int getNodeIndex(u_int nodeId) const {
		for (int i=0 ; i<nodes.size() ; i++){
			if(nodes.at(i).getId() == nodeId) {
				return i;	// Found it
			}
		}

		// Node not found
		return -1;
	}

public:
	Graph();

	// Add a new node to the graph
	u_int addNode(double x, double y, const std::string& name);

	// Add a new edge connecting two nodes
	bool addEdge(u_int nodeId1 , u_int nodeId2 , const double & weight);

    // Add a new edge connecting two nodes
    bool addEdge(u_int nodeId1 , u_int nodeId2 , const double & weight, const std::string& name);

	// Returns a pair with the Edge value and a boolean that says if the node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<double,bool> getEdgeVal(u_int nodeId1 , u_int nodeId2) const;

	// Returns success / failure (failure is when the node does not exist)
	bool setEdgeVal(u_int nodeId1 , u_int nodeId2 , const double & newVal);

    // Get the node with id 'id' , returns a Node with id of -1 if not found
    Node getNodeById(u_int id) const;

	// Returns all connected nodes with edge values
    // If it can't find any Node with the given nodeId, it throws NodeNotFound exception
	const std::vector< Edge > &getEdges(u_int nodeId);

	// Returns the number of nodes in the graph
	u_int getNumNodes() const;

	// Returns the number of edges in the graph
	u_int getNumEdges() const;
};


#endif /* GRAPH_H_ */
