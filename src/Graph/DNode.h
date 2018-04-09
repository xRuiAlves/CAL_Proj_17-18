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

    // Returns the 'lastNodeId' value
    u_int getLastNodeId() const;

    // Returns the node's 'totalWeight' value
    double getTotalWeight() const;

    // DNode 'Less than' operator
    virtual bool operator<(const DNode& d2) const;

    // DNode Equality operator
    bool operator==(const DNode& d2) const;

    // DNode Difference Operator
    bool operator!=(const DNode& d2) const;
};



/////////////////////////////////////
//////     DNODE HASH TABLE     //////
/////////////////////////////////////

struct DNodeHash {
    bool operator()(const DNode &d1, const DNode &d2) const {
        return d1 == d2;
    }

    int operator()(const DNode &d) const {
        return d.getId();
    }
};

typedef unordered_set<DNode, DNodeHash, DNodeHash> DNodeHashTable;


#endif /* DNODE_H_ */
