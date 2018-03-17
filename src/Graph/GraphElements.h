/*
 * Node.h
 *
 *  Created on: 24/02/2018
 *      Author: Rui Alves
 */

#ifndef GRAPH_ELEMENTS_H_
#define GRAPH_ELEMENTS_H_

#include "../Utilities/defs.h"

using namespace std;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////                EDGE CLASS               /////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


class Edge{
public:
    u_int destNodeId;
    double value;

    Edge();
    Edge(u_int destNodeId, const double & value);
};


Edge::Edge(u_int destNodeId, const double & value) : value(value), destNodeId(destNodeId){}


Edge::Edge(): value(UNDEFINED_VALUE), destNodeId(UINT_MAX) {}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////                NODE CLASS               /////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// Node class, used by graph class
// Every node has its own unique ID, which makes the node Unique and "locatable"
// N is Node Data Type and E is Edge Data Type
class Node{
protected:
    u_int id;
    double x;
    double y;
    string name;
    std::vector< Edge > edges;

private:

	// Gets the connection with the Node (with id) passed in as parameter index , -1 if not found
	int getConnectionIndex(u_int destNodeId) const{
		// Search for the connection
		for (int i=0 ; i<edges.size() ; i++){
			if (edges.at(i).destNodeId == destNodeId){
				return i;
			}
		}

		// Connection not found
		return -1;
	}
public:

    Node();

    Node(u_int id);

	// Construct node with its value
	Node(u_int id, double x, double y, const string &name);

    const vector<Edge>& getEdges() const{
        return this->edges;
    }

	// Add a connection
	bool addNodeConnection(u_int destNodeId, const double & weight);

	// Returns a pair with the Edge value and a boolean that says if the connection with the other node exists or not ;
	// if the boolean is false, value makes no sense
	std::pair<double , bool> getEdgeVal(u_int otherNodeId) const;

	// Returns success / failure (failure is when the connection with the other node does not exist)
	bool setEdgeVal(u_int otherNodeId , const double & newWeight);

    u_int getId() const{
        return this->id;
    }
};

Node::Node(u_int id, double x, double y, const string &name) :
        id(id),
        x(x),
        y(y),
        name(name)
{}

Node::Node(u_int id) :
        id(id),
        x(DBL_MAX),
        y(DBL_MAX),
        name("")
{}

Node::Node() :
        id(UINT_MAX),
        x(DBL_MAX),
        y(DBL_MAX),
        name("")
{}


bool Node::addNodeConnection(u_int destNodeId , const double & weight){
	if (getConnectionIndex(destNodeId) != -1){
		return false;
	}

	// Add the node connection
	edges.push_back( Edge(destNodeId, weight) );
	return true;
}


std::pair<double , bool> Node::getEdgeVal(u_int otherNodeId) const {
	// Find if the node with id 'otherNodeId' is in my connections ; If so, return the edge value
	int otherNodeIndex = getConnectionIndex(otherNodeId);

	if(otherNodeIndex != -1){
		return std::make_pair(edges.at(otherNodeIndex).value , true);
	}

	// This node does not connect with other node...
	return std::make_pair(UNDEFINED_VALUE , false);
}



#endif /* GRAPH_ELEMENTS_H_ */
