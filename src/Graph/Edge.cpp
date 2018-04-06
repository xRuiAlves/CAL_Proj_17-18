#include "Edge.h"

Edge::Edge(u_int destNodeId, const double & value, const std::string & name) : value(value), destNodeId(destNodeId), name(name){

}

Edge::Edge(): value(UNDEFINED_VALUE), destNodeId(UINT_MAX) {

}

Edge::Edge(u_int destNodeId, const double & value) : value(value), destNodeId(destNodeId), name(""){

}
