#include "Graph.h"

Graph::Graph(){

}


u_int Graph::addNode(double x, double y, const std::string & name){
    u_int id = nodes.size();
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


u_int Graph::getNumNodes() const {
    return nodes.size();
}


u_int Graph::getNumEdges() const {
    u_int numEdges = 0;

    for (Node n : nodes){
        numEdges = n.getNumEdges();
    }

    return numEdges;
}