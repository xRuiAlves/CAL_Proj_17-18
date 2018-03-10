/*
 * DNode.h
 *
 *  Created on: 10/03/2018
 *      Author: Rui Alves
 */

#ifndef DNODE_H_
#define DNODE_H_

#include "defs.h"

class DNode {
private:
	u_int nodeId;
	u_int lastNodeId;
	double totalWeight;

public:
	DNode(u_int nodeId , u_int lastNodeId , double totalWeight);
    DNode(u_int nodeId, double totalWeight);
	DNode(u_int nodeId);
    DNode();

	void setNodeId(u_int nodeId);
	void setLastNodeId(u_int lastNodeId);
	void setTotalWeight(double totalWeight);

	u_int getNodeId() const;
	u_int getLastNodeId() const;
	double getTotalWeight() const;

    bool operator<(const DNode&) const;
    bool operator==(const DNode&) const;
};


#endif /* DNODE_H_ */
