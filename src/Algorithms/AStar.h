//
// Created by angelo on 27-03-2018.
//

#ifndef CAL_ASTAR_H
#define CAL_ASTAR_H


#include "Dijkstra.h"

class AStar : public Dijkstra {
public:
    AStar(const Graph &graph);
private:
    double calcTotalWeight(const DNode & d) const;

};


#endif //CAL_ASTAR_H
