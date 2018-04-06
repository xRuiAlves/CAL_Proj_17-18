#ifndef CAL_EDGE_H
#define CAL_EDGE_H

#include "../Utilities/defs.h"

class Edge{
public:
    u_int destNodeId;
    double value;
    std::string name;

    Edge();
    Edge(u_int destNodeId, const double & value);
    Edge(u_int destNodeId, const double & value, const std::string & name);
};


#endif //CAL_EDGE_H
