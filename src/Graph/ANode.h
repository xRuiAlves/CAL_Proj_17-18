#ifndef CAL_ANODE_H
#define CAL_ANODE_H


#include "DNode.h"

class ANode : public DNode {
private:
    double distToFinish;
    double heuristicWeight;
public:
    // Constructors
    ANode(const Node & node);
    ANode(double distToFinish);
    ANode(const Node &  node , u_int lastNodeId , double totalWeight, double distToFinish);
    ANode(const Node &  node, double totalWeight, double distToFinish);
    ANode(const Node &  node, double distToFinish);
    ANode(const DNode &  dnode, double distToFinish);
    ANode(u_int id, double distToFinish);

    // Returns node 'heuristicWeight' value
    double getHeuristicWeight() const;

    // ANode 'Less than' operator
    bool operator<(const ANode& d2) const;
};




#endif //CAL_ANODE_H
