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
    set<ANode> pQueueWeighted; // stores the ANodes with the A* weight function
    ANode topANode;

    void populateQueue();

    bool foundOptimalSolution();

    bool isTopNodeDeadEnd() const;

    bool queueIsEmpty() const;

    void removeNodeFromQueue();

    void updateTopNode();

    void updateNodeOnQueue(const DNode & currDNode);

    void updateQueue();

    void buildPath();

    // DNode getDNodeInQueueById(u_int id) const;
};


#endif //CAL_ASTAR_H
