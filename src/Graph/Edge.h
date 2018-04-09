#ifndef CAL_EDGE_H
#define CAL_EDGE_H

#include "../Utilities/defs.h"

struct Edge{
    u_int destNodeId;
    double value;
    std::string name;

    // Constructors
    Edge();
    Edge(u_int destNodeId, const double & value);
    Edge(u_int destNodeId, const double & value, const std::string & name);
};


#endif //CAL_EDGE_H
