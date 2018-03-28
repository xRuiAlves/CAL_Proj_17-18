//
// Created by angelo on 28-03-2018.
//

#include "ANode.h"

bool ANode::operator<(const ANode &d2) const {
    if(this->totalWeight == d2.getTotalWeight()){
        return this->id < d2.id;
    } else {
        return this->totalWeight + distanceToFinish < d2.getTotalWeight() + distanceToFinish;
    }
}

ANode::ANode(double distToFinish) : DNode(){
    this->distanceToFinish = distToFinish;
}

ANode::ANode(Node node, u_int lastNodeId, double totalWeight, double distToFinish)
        : DNode(node, lastNodeId, totalWeight) {

    this->distanceToFinish = distToFinish;
}

ANode::ANode(Node node, double totalWeight, double distToFinish)
        : DNode(node, totalWeight) {
    this->distanceToFinish = distToFinish;
}

ANode::ANode(Node node, double distToFinish) : DNode(node) {
    this->distanceToFinish = distToFinish;
}

ANode::ANode(u_int id, double distToFinish) : DNode(id) {
    this->distanceToFinish = distToFinish;
}
