/*
 * DNode.cpp
 *
 *  Created on: 10/03/2018
 *      Author: Rui Alves
 */

#include "DNode.h"

DNode::DNode(u_int nodeId , u_int lastNodeId , double totalWeight) {
	this->nodeId = nodeId;
	this->lastNodeId = lastNodeId;
	this->totalWeight = totalWeight;
}

DNode::DNode(u_int nodeId) {
	this->nodeId = nodeId;
	this->lastNodeId = UINT_MAX;
	this->totalWeight = DBL_MAX;
}

void DNode::setNodeId(u_int nodeId) {
	this->nodeId = nodeId;
}

void DNode::setLastNodeId(u_int lastNodeId) {
	this->lastNodeId = lastNodeId;
}

void DNode::setTotalWeight(double totalWeight) {
	this->totalWeight = totalWeight;
}

u_int DNode::getNodeId() const {
	return nodeId;
}

u_int DNode::getLastNodeId() const {
	return lastNodeId;
}

double DNode::getTotalWeight() const {
	return totalWeight;
}

bool DNode::operator<(const DNode& d2) const{
    if(this->totalWeight == d2.getTotalWeight()){
        return this->nodeId < d2.nodeId;
    } else {
        return this->totalWeight < d2.getTotalWeight();
    }
}

bool DNode::operator==(const DNode& d2) const{
    return this->nodeId == d2.nodeId;
}

