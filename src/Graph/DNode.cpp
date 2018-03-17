#include "DNode.h"


DNode::DNode() : Node(){
    this->lastNodeId = UINT_MAX;
    this->totalWeight = DBL_MAX;
}


DNode::DNode(Node node , u_int lastNodeId , double totalWeight):Node(node) {
    this->lastNodeId = lastNodeId;
    this->totalWeight = totalWeight;
}


DNode::DNode(Node node, double totalWeight) :Node(node){
    this->lastNodeId = UINT_MAX;
    this->totalWeight = totalWeight;
}


DNode::DNode(Node node) : Node(node){
    this->lastNodeId = UINT_MAX;
    this->totalWeight = DBL_MAX;
}


DNode::DNode(u_int id) : Node(id){
    this->lastNodeId = UINT_MAX;
    this->totalWeight = DBL_MAX;
}


void DNode::setLastNodeId(u_int lastNodeId) {
    this->lastNodeId = lastNodeId;
}


void DNode::setTotalWeight(double totalWeight) {
    this->totalWeight = totalWeight;
}


u_int DNode::getLastNodeId() const {
    return lastNodeId;
}


double DNode::getTotalWeight() const {
    return totalWeight;
}


bool DNode::operator<(const DNode& d2) const{
    if(this->totalWeight == d2.getTotalWeight()){
        return this->id < d2.id;
    } else {
        return this->totalWeight < d2.getTotalWeight();
    }
}


bool DNode::operator==(const DNode& d2) const{
    return this->id == d2.id;
}


bool DNode::operator!=(const DNode& d2) const{
    return !(this->id == d2.id);
}