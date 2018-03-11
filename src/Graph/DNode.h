/*
 * DNode.h
 *
 *  Created on: 10/03/2018
 *      Author: Rui Alves
 */

#ifndef DNODE_H_
#define DNODE_H_

#include "defs.h"
#include "GraphElements.h"

template<typename N>
class DNode: public Node<N>{
private:
	u_int lastNodeId;
	double totalWeight;

public:
    DNode(Node<N> node , u_int lastNodeId , double totalWeight):Node<N>(node) {
        this->lastNodeId = lastNodeId;
        this->totalWeight = totalWeight;
    }

    DNode(Node<N> node, double totalWeight) :Node<N>(node){
        this->lastNodeId = UINT_MAX;
        this->totalWeight = totalWeight;
    }

    DNode(Node<N> node) :Node<N>(node){
        this->lastNodeId = UINT_MAX;
        this->totalWeight = DBL_MAX;
    }

    DNode() {
        this->id = UINT_MAX;
        this->lastNodeId = UINT_MAX;
        this->totalWeight = DBL_MAX;
    }

    DNode(u_int id) {
        this->id = id;
        this->lastNodeId = UINT_MAX;
        this->totalWeight = DBL_MAX;
    }

    void setLastNodeId(u_int lastNodeId) {
        this->lastNodeId = lastNodeId;
    }

    void setTotalWeight(double totalWeight) {
        this->totalWeight = totalWeight;
    }

    u_int getLastNodeId() const {
        return lastNodeId;
    }

    double getTotalWeight() const {
        return totalWeight;
    }

    bool operator<(const DNode<N>& d2) const{
        if(this->totalWeight == d2.getTotalWeight()){
            return this->id < d2.id;
        } else {
            return this->totalWeight < d2.getTotalWeight();
        }
    }

    bool operator==(const DNode<N>& d2) const{
        return this->id == d2.id;
    }

    bool operator!=(const DNode<N>& d2) const{
        return !(this->id == d2.id);
    }



};


#endif /* DNODE_H_ */
