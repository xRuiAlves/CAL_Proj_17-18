#include "ANode.h"

bool ANode::operator<(const ANode &d2) const {

    if(this->heuristicWeight == d2.heuristicWeight){
        return this->id < d2.id;
    } else {
        return this->heuristicWeight < d2.heuristicWeight;
    }
}

ANode::ANode(const Node & node) : DNode(node) {
    this->distToFinish = DBL_MAX;
    this->heuristicWeight = DBL_MAX;
}

ANode::ANode(double distToFinish) : DNode(){
    this->distToFinish = distToFinish;
    this->heuristicWeight = DBL_MAX;
}

ANode::ANode(const Node &  node, u_int lastNodeId, double totalWeight, double distToFinish)
        : DNode(node, lastNodeId, totalWeight) {

    this->distToFinish = distToFinish;
    this->heuristicWeight = this->distToFinish + this->totalWeight;
}

ANode::ANode(const Node &  node, double totalWeight, double distToFinish)
        : DNode(node, totalWeight) {

    this->distToFinish = distToFinish;
    this->heuristicWeight = this->distToFinish + this->totalWeight;
}

ANode::ANode(const Node &  node, double distToFinish) : DNode(node) {
    this->distToFinish = distToFinish;
    this->heuristicWeight = DBL_MAX;
}

ANode::ANode(u_int id, double distToFinish) : DNode(id) {
    this->distToFinish = distToFinish;
    this->heuristicWeight = DBL_MAX;
}

ANode::ANode(const DNode &  dnode, double distToFinish) : DNode(dnode) {
    this->distToFinish = distToFinish;
    this->heuristicWeight = this->distToFinish + this->totalWeight;
}

double ANode::getHeuristicWeight() const {
    return this->heuristicWeight;
}

double ANode::getDistToFinish() const {
    return this->distToFinish;
}

double ANode::setTotalWeight(double totalWeight) {
    this->totalWeight = totalWeight;
    this->heuristicWeight = this->totalWeight + this->distToFinish;
}


double ANode::setDistToFinish(double dist) {
    this->distToFinish = dist;
    this->heuristicWeight = this->totalWeight + this->distToFinish;
}
