//
// Created by angelo on 27-03-2018.
//

#ifndef CAL_ASTAR_H
#define CAL_ASTAR_H


#include "Dijkstra.h"
#include "../Graph/ANode.h"

class AStar : public Dijkstra {
public:
    AStar(const Graph &graph);
private:
    vector<u_int> currentBestSolution;
    double currentBestSolutionWeight;
    set<ANode> pQueueWeighted; // stores the ANodes with the A* weight function




    void updateQueue();

    void populateQueue();

    bool foundOptimalSolution();

    // DNode getDNodeInQueueById(u_int id) const;
};


#endif //CAL_ASTAR_H
