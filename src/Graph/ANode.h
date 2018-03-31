#ifndef CAL_ANODE_H
#define CAL_ANODE_H


#include "DNode.h"

class ANode : public DNode {
private:
    double distToFinish;
    double heuristicWeight;
public:
    ANode(const Node & node);
    ANode(double distToFinish);
    ANode(const Node &  node , u_int lastNodeId , double totalWeight, double distToFinish);
    ANode(const Node &  node, double totalWeight, double distToFinish);
    ANode(const Node &  node, double distToFinish);
    ANode(const DNode &  dnode, double distToFinish);
    ANode(u_int id, double distToFinish);

    double getHeuristicWeight() const;
    double getDistToFinish() const;

    double setTotalWeight(double weight);
    double setDistToFinish(double dist);

    bool operator<(const ANode& d2) const;
};




#endif //CAL_ANODE_H
