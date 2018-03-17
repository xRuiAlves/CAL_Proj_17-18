#include "Edge.h"

Edge::Edge(u_int destNodeId, const double & value) : value(value), destNodeId(destNodeId){

}

Edge::Edge(): value(UNDEFINED_VALUE), destNodeId(UINT_MAX) {

}
