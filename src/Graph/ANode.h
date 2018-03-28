//
// Created by angelo on 28-03-2018.
//

#ifndef CAL_ANODE_H
#define CAL_ANODE_H


#include "DNode.h"

class ANode : public DNode {
private:
    double distanceToFinish;
public:
    ANode(double distToFinish);
    ANode(const Node &  node , u_int lastNodeId , double totalWeight, double distToFinish);
    ANode(const Node &  node, double totalWeight, double distToFinish);
    ANode(const Node &  node, double distToFinish);
    ANode(const DNode &  dnode, double distToFinish);
    ANode(u_int id, double distToFinish);

    bool operator<(const ANode& d2) const;
};




#endif //CAL_ANODE_H
