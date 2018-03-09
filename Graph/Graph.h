/*
 * Graph.h
 *
 *  Created on: 24/02/2018
 *      Author: Rui Alves
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "defs.h"
#include <vector>
#include <iostream>
#include <cstdlib>

#include "GraphElements.h"

// Graph class
// N is Node Data Type and E is Edge Data Type
template <typename N , typename E>
class Graph
{
private:
	std::vector< Node<N,E> > nodes;

	// Get the index of the node with id 'id' , -1 if not found
	int getNodeIndex(u_int nodeId) const {
		for (int i=0 ; i<nodes.size() ; i++){
			if(nodes.at(i).id == nodeId) {
				return i;	// Found it
			}
		}

		// Node not found
		return -1;
	}

public:
	Graph(int graphSize);

	// Add a new node to the graph
	int addNode(const N & data);

	// Add a new edge connecting two nodes
	bool addEdge(u_int nodeId1 , u_int nodeId2 , E weight);

	// Returns a pair with the Node value and a boolean that says if the node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<N,bool> getNodeVal(u_int nodeId) const;

	// Returns success / failure (failure is when the node does not exist)
	bool setNodeVal(u_int nodeId , N newVal);

	// Returns a pair with the Edge value and a boolean that says if the node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<E,bool> getEdgeVal(u_int nodeId1 , u_int nodeId2) const;

	// Returns success / failure (failure is when the node does not exist)
	bool setEdgeVal(u_int nodeId1 , u_int nodeId2 , const E & newVal);

    // Get the node with id 'id' , returns a Node with id of -1 if not found
    Node<N,E> getNodeByIndex(u_int nodeId) const;


	class NodeNotFound {
    public:
		NodeNotFound(u_int id) : id(id) {}

        u_int id;
    };

	// Returns all connected nodes with edge values
    // If it can't find any Node with the given nodeId, it throws NodeNotFound exception
	std::vector< Edge<N,E> > getEdges(u_int nodeId);

	u_int getNumNodes() const;
};




/////////////////////////////////////
//     METHODS IMPLEMENTATION     ///
/////////////////////////////////////




template <typename N , typename E>
Graph<N,E>::Graph(int graphSize) {
	nodes.reserve(graphSize);
}


template <typename N , typename E>
u_int Graph<N,E>::getNumNodes() const {
	return nodes.size();
}


template <typename N , typename E>
int Graph<N,E>::addNode(const N & data){
	nodes.push_back( Node<N,E>(data) );

	// Return the node's id
	return nodes.at(nodes.size()-1).id;
}


template <typename N , typename E>
bool Graph<N,E>::addEdge(u_int nodeId1 , u_int nodeId2 , E weight) {
	if (nodeId1 == nodeId2) {
		return false;
	}

	int node1index = getNodeIndex(nodeId1);
	if(node1index == -1){	// Node 1 not found
		return false;
	}

	int node2index = getNodeIndex(nodeId2);
	if(node2index == -1){	// Node 2 not found
		return false;
	}

	// Add the node connections
	nodes.at(node1index).addNodeConnection(&nodes.at(node2index) , weight);
	return true;	// Success
}


template <typename N , typename E>
std::pair<N,bool> Graph<N,E>::getNodeVal(u_int nodeId) const {
	int nodeIndex = getNodeIndex(nodeId);

	// Check if node exists
	if(nodeIndex == -1) {
		return std::make_pair(N() , false);
	}
	else {
		return std::make_pair(nodes.at(nodeIndex).data , true);
	}
}


template <typename N , typename E>
bool Graph<N,E>::setNodeVal(u_int nodeId , N newVal) {
	int nodeIndex = getNodeIndex(nodeId);

	// Check if the node exists
	if(nodeIndex == -1) {
		return false;
	}
	else {
		nodes.at(nodeIndex).val = newVal;
		return true;
	}
}


template <typename N , typename E>
std::pair<E,bool> Graph<N,E>::getEdgeVal(u_int nodeId1 , u_int nodeId2) const {
	// Get nodes indexes
	int node1Index = getNodeIndex(nodeId1);
	int node2Index = getNodeIndex(nodeId2);

	// Nodes not found
	if (node1Index == -1  ||  node2Index == -1){
		return std::make_pair(E() , false);
	}

	std::pair<E,bool> edgeValReturn = nodes.at(node1Index).getEdgeVal(nodeId2);

	// Nodes don't connect
	if (edgeValReturn.second == false) {
		return std::make_pair(E() , false);
	}
	else {
		return std::make_pair(edgeValReturn.first , true);
	}
}


template <typename N , typename E>
bool Graph<N,E>::setEdgeVal(u_int nodeId1 , u_int nodeId2 ,const E & newVal) {
	// Get nodes indexes
	int node1Index = getNodeIndex(nodeId1);
	int node2Index = getNodeIndex(nodeId2);

	// Nodes not found
	if (node1Index == -1  ||  node2Index == -1){
		return false;
	}

	// Set the new edge value
	nodes.at(node1Index).setEdgeVal(nodeId2 , newVal);
}

template<typename N, typename E>
std::vector< Edge<N,E> > Graph<N, E>::getEdges(u_int nodeId) {
    int nodeIndex = getNodeIndex(nodeId);

    if(nodeIndex == -1) { // not found
        throw NodeNotFound(nodeId);
    } else {
        return nodes.at(nodeIndex).edges;
    }
}

#endif /* GRAPH_H_ */
