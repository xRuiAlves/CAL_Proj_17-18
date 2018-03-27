//
// Created by angelo on 27-03-2018.
//

#include "AStar.h"

AStar::AStar(const Graph &graph) : Dijkstra(graph) {}

double AStar::calcTotalWeight(const DNode & d) const {

    return d.getTotalWeight() + d.getDistanceToOtherNode(this->finishNode);
}
