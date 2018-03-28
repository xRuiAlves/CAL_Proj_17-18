#ifndef DNODE_H_
#define DNODE_H_

#include "../Utilities/defs.h"
#include "Node.h"


class DNode: public Node{
protected:
	u_int lastNodeId;
	double totalWeight;

public:
    // Constructors
    DNode();
    DNode(const Node & node , u_int lastNodeId , double totalWeight);
    DNode(const Node &  node, double totalWeight);
    DNode(const Node &  node);
    DNode(u_int id);
    DNode(u_int id , u_int lastNodeId);

    // Getters and Setters
    void setLastNodeId(u_int lastNodeId);
    void setTotalWeight(double totalWeight);
    u_int getLastNodeId() const;
    double getTotalWeight() const;

    // Operators
    virtual bool operator<(const DNode& d2) const;
    bool operator==(const DNode& d2) const;
    bool operator!=(const DNode& d2) const;
};


#endif /* DNODE_H_ */
