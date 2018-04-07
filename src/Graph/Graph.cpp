#include "Graph.h"

Graph::Graph(){

}


u_int Graph::addNode(double x, double y, const std::string & name){
    u_int id = nodes.size();
    nodes.push_back( Node(id, x, y, name) );
    if(id==0){
        this->boundBot = y;
        this->boundLeft = x;
        this->boundRight = x;
        this->boundTop = y;
    }else{
        if(x > boundRight) boundRight = x;
        else if(x < boundLeft) boundLeft = x;
        if(y > boundTop) boundTop = y;
        else if (y < boundBot) boundBot = y;
    }
    // Return the node's id
    return id;
}

bool Graph::addEdge(u_int nodeId1 , u_int nodeId2 , const double & weight) {

    addEdge(nodeId1, nodeId2, weight, "");
}

bool Graph::addEdge(u_int nodeId1, u_int nodeId2, const double &weight, const std::string &name) {
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
    return nodes.at(node1index).addNodeConnection(node2index, weight, name);
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
        throw InvalidNodeId(nodeId);
    }
    else{
        return nodes.at(nodeId);
    }
}


u_int Graph::getNumNodes() const {
    return nodes.size();
}


u_int Graph::getNumEdges() const {
    u_int numEdges = 0;

    for (Node n : nodes){
        numEdges += n.getNumEdges();
    }

    return numEdges;
}

int Graph::getNodeIndex(u_int nodeId) const {
    for (int i=0 ; i<nodes.size() ; i++){
        if(nodes.at(i).getId() == nodeId) {
            return i;	// Found it
        }
    }

    // Node not found
    return -1;
}

double Graph::getBoundBot() const {
    return boundBot;
}

double Graph::getBoundTop() const {
    return boundTop;
}

double Graph::getBoundLeft() const {
    return boundLeft;
}

double Graph::getBoundRight() const {
    return boundRight;
}
