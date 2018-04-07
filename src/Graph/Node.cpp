#include "Node.h"


Node::Node(u_int id, double x, double y, const std::string &name) :
        id(id),
        x(x),
        y(y),
        name(name) {

}

Node::Node(u_int id) :
        id(id),
        x(DBL_MAX),
        y(DBL_MAX),
        name("") {

}

Node::Node() :
        id(UINT_MAX),
        x(DBL_MAX),
        y(DBL_MAX),
        name("") {

}


bool Node::addNodeConnection(u_int destNodeId , const double & weight, const std::string & name){
    if (getConnectionIndex(destNodeId) != -1){
        return false;
    }

    // Add the node connection
    edges.push_back( Edge(destNodeId, weight, name) );
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


const std::vector<Edge>& Node::getEdges() const{
    return this->edges;
}


u_int Node::getId() const{
    return this->id;
}


u_int Node::getNumEdges() const{
    return edges.size();
}


double Node::getDistanceToOtherNode(const Node & otherNode) const{
    std::pair<double,double> distanceVector = std::make_pair(
            otherNode.x - this->x ,
            otherNode.y - this->y );

    return sqrt(distanceVector.first*distanceVector.first + distanceVector.second*distanceVector.second);
}


bool Node::operator==(const Node & other) const{
    return this->id == other.id;
}

const std::string &Node::getName() const {
    return name;
}

double Node::getX() const {
    return x;
}

double Node::getY() const {
    return y;
}
