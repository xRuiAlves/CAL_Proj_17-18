#ifndef CAL_EDGE_H
#define CAL_EDGE_H

#include "../Utilities/defs.h"

class Edge{
public:
    u_int destNodeId;
    double value;

    Edge();
    Edge(u_int destNodeId, const double & value);
};


#endif //CAL_EDGE_H
