/*
 * Node.h
 *
 *  Created on: 24/02/2018
 *      Author: Rui Alves
 */

#ifndef GRAPH_ELEMENTS_H_
#define GRAPH_ELEMENTS_H_

#include "defs.h"

// Edge class forward declaration
template <typename N>
class Edge;


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////                NODE CLASS               /////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

static u_int nodeCount = 0;

// Node class, used by graph class
// Every node has its own unique ID, which makes the node Unique and "locatable"
// N is Node Data Type and E is Edge Data Type
template <typename N>
class Node{
private:
	// Gets the connection with the Node (with id) passed in as parameter index , -1 if not found
	int getConnectionIndex(u_int otherNodeId) const{
		// Search for the connection
		for (int i=0 ; i<edges.size() ; i++){
			if (edges.at(i).otherNode->id == otherNodeId){
				return i;
			}
		}

		// Connection not found
		return -1;
	}

	// Gets the connection with the Node (with Pointer) passed in as parameter index , -1 if not found
	int getConnectionIndexPtr(Node<N> * otherNodePtr) const{
		// Search for the connection
		for (int i=0 ; i<edges.size() ; i++){
			if (edges.at(i).otherNode == otherNodePtr){
				return i;
			}
		}

		// Connection not found
		return -1;
	}
public:
	u_int id;
	N data;
	std::vector< Edge<N> > edges;

	// Empty Constructor is needed for Graph
	Node();

	// Construct node with its value
	Node(const N & data);


	// Add a connection
	bool addNodeConnection(Node<N> * nodePtr , const double & weight);

	// Returns a pair with the Edge value and a boolean that says if the connection with the other node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<double , bool> getEdgeVal(u_int otherNodeId) const;

	// Returns success / failure (failure is when the connection with the other node does not exist)
	bool setEdgeVal(u_int otherNodeId , const double & newWeight);

};


template <typename N>
Node<N>::Node() {
	this->id = 0;
}


template <typename N>
Node<N>::Node(const N & data) {
	this->data = data;
	this->id = ++nodeCount;
}


template <typename N>
bool Node<N>::addNodeConnection(Node<N> * nodePtr , const double & weight){
	// Verify if nodePtr isn't null / isn't self / isn't already connected
	if (nodePtr == NULL || nodePtr == this || getConnectionIndexPtr(nodePtr) != -1){
		return false;
	}

	// Add the node connection
	edges.push_back( Edge<N>(nodePtr, weight) );
	return true;
}


template <typename N>
std::pair<double , bool> Node<N>::getEdgeVal(u_int otherNodeId) const {
	// Find if the node with id 'otherNodeId' is in my connections ; If so, return the edge value
	int otherNodeIndex = getConnectionIndex(otherNodeId);

	if(otherNodeIndex != -1){
		return std::make_pair(edges.at(otherNodeIndex).value , true);
	}

	// This node does not connect with other node...
	return std::make_pair(UNDEFINED_VALUE , false);
}

template <typename N>
bool Node<N>::setEdgeVal(u_int otherNodeId , const double & newWeight) {
	// Find if the node with id 'otherNodeId' is in my connections
	int otherNodeIndex = getConnectionIndex(otherNodeId);

	// If it exists, set the value of the edge that connects them
	if (otherNodeIndex == -1) {
		return false;
	}
	else {
		edges.at(otherNodeIndex).value = newWeight;
		return true;
	}
}






////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////                EDGE CLASS               /////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

template <typename N>
class Edge{
public:
	Node<N> * otherNode;
	double value;

	Edge();
	Edge(Node<N>* otherNode , const double & value);
};

template <typename N>
Edge<N>::Edge(Node<N>* otherNode , const double & value) {
	this->value = value;
	this->otherNode = otherNode;
}

template <typename N>
Edge<N>::Edge() {
	this->value = UNDEFINED_VALUE;
	this->otherNode = nullptr;
}



#endif /* GRAPH_ELEMENTS_H_ */