/*
 * Graph.h
 *
 *  Created on: 24/02/2018
 *      Author: Rui Alves
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <vector>
#include <iostream>
#include <cstdlib>

#include "GraphElements.h"

// Graph class
// N is Node Data Type and E is Edge Data Type

class Graph
{
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
	int addNode(double x, double y, string name);

	// Add a new edge connecting two nodes
	bool addEdge(u_int nodeId1 , u_int nodeId2 , const double & weight);

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

	u_int getNumNodes() const;
};




/////////////////////////////////////
//     METHODS IMPLEMENTATION     ///
/////////////////////////////////////

Graph::Graph(){}

u_int Graph::getNumNodes() const {
	return nodes.size();
}



int Graph::addNode(double x, double y, string name){
	int id = nodes.size();
	nodes.push_back( Node(id, x, y, name) );

	// Return the node's id
	return id;
}



bool Graph::addEdge(u_int nodeId1 , u_int nodeId2 , const double & weight) {
	if (nodeId1 == nodeId2) {
		return false;
	}

	int node1index = getNodeIndex(nodeId1);
	if (node1index == -1) {    // Node 1 not found
		return false;
	}

	int node2index = getNodeIndex(nodeId2);
	if (node2index == -1) {    // Node 2 not found
		return false;
	}

	// Add the node connections
	nodes.at(node1index).addNodeConnection(node2index, weight);
	return true;    // Success
}


std::pair<double,bool> Graph::getEdgeVal(u_int nodeId1 , u_int nodeId2) const {
	// Get nodes indexes
	int node1Index = getNodeIndex(nodeId1);
	int node2Index = getNodeIndex(nodeId2);

	// Nodes not found
	if (node1Index == -1  ||  node2Index == -1){
		return std::make_pair(UNDEFINED_VALUE , false);
	}

	std::pair<double,bool> edgeValReturn = nodes.at(node1Index).getEdgeVal(nodeId2);

	// Nodes don't connect
	if (edgeValReturn.second == false) {
		return std::make_pair(UNDEFINED_VALUE , false);
	}
	else {
		return std::make_pair(edgeValReturn.first , true);
	}
}


const std::vector< Edge > &Graph::getEdges(u_int nodeId) {
    int nodeIndex = getNodeIndex(nodeId);

    if(nodeIndex == -1) { // not found
        throw NodeNotFound(nodeId);
    } else {
        return nodes.at(nodeIndex).getEdges();
    }
}


Node Graph::getNodeById(u_int nodeId) const{ //ID == INDEX = true
	if(nodeId >= nodes.size()) {
		throw InvalidNodeId();
	}
	else{
		return nodes.at(nodeId);
	}
}


#endif /* GRAPH_H_ */
