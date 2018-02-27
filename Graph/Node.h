/*
 * Node.h
 *
 *  Created on: 24/02/2018
 *      Author: Rui Alves
 */

#ifndef NODE_H_
#define NODE_H_

#include "defs.h"

static u_int nodeCount = 0;

// Node class, used by graph class
// Every node has its own unique ID, which makes the node Unique and "locatable"
// N is Node Data Type and E is Edge Data Type
template <typename N , typename E>
class Node{
private:
	// Gets the connection with the Node (with id) passed in as parameter index , -1 if not found
	int getConnectionIndex(u_int otherNodeId) const{
		// Search for the connection
		for (int i=0 ; i<neighborNodes.size() ; i++){
			if (neighborNodes.at(i).first->id == otherNodeId){
				return i;
			}
		}

		// Connection not found
		return -1;
	}

	// Gets the connection with the Node (with Pointer) passed in as parameter index , -1 if not found
	int getConnectionIndexPtr(Node<N,E> * otherNodePtr) const{
		// Search for the connection
		for (int i=0 ; i<neighborNodes.size() ; i++){
			if (neighborNodes.at(i).first == otherNodePtr){
				return i;
			}
		}

		// Connection not found
		return -1;
	}
public:
	u_int id;
	N data;
	std::vector< std::pair<Node<N,E>* , E> > neighborNodes;

	// Empty Constructor is needed for Graph
	Node();

	// Construct node with its value
	Node(const N & data);


	// Add a connection
	bool addNodeConnection(Node<N,E> * nodePtr , const E & weight);

	// Returns a pair with the Edge value and a boolean that says if the connection with the other node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<E , bool> getEdgeVal(u_int otherNodeId) const;

	// Returns success / failure (failure is when the connection with the other node does not exist)
	bool setEdgeVal(u_int otherNodeId , const E & newWeight);

};




/////////////////////////////////////
//     METHODS IMPLEMENTATION     ///
/////////////////////////////////////




template <typename N , typename E>
Node<N,E>::Node() {
	this->id = 0;
}


template <typename N , typename E>
Node<N,E>::Node(const N & data) {
	this->data = data;
	this->id = ++nodeCount;
}


template <typename N , typename E>
bool Node<N,E>::addNodeConnection(Node<N,E> * nodePtr , const E & weight){
	// Verify if nodePtr isn't null / isn't self / isn't already connected
	if (nodePtr == NULL || nodePtr == this || getConnectionIndexPtr(nodePtr) != -1){
		return false;
	}

	// Add the node connection
	neighborNodes.push_back( std::make_pair( nodePtr, weight) );
	return true;
}


template <typename N , typename E>
std::pair<E , bool> Node<N,E>::getEdgeVal(u_int otherNodeId) const {
	// Find if the node with id 'otherNodeId' is in my connections ; If so, return the edge value
	int otherNodeIndex = getConnectionIndex(otherNodeId);

	if(otherNodeIndex != -1){
		return std::make_pair(neighborNodes.at(otherNodeIndex).second , true);
	}

	// This node does not connect with other node...
	return std::make_pair(E() , false);
}

template <typename N , typename E>
bool Node<N,E>::setEdgeVal(u_int otherNodeId , const E & newWeight) {
	// Find if the node with id 'otherNodeId' is in my connections
	int otherNodeIndex = getConnectionIndex(otherNodeId);

	// If it exists, set the value of the edge that connects them
	if (otherNodeIndex == -1) {
		return false;
	}
	else {
		neighborNodes.at(otherNodeIndex).second = newWeight;
		return true;
	}
}



#endif /* NODE_H_ */
