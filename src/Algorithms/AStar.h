//
// Created by angelo on 27-03-2018.
//

#ifndef CAL_ASTAR_H
#define CAL_ASTAR_H


#include "Dijkstra.h"
#include "../Graph/ANode.h"

class AStar : public Dijkstra {
private:
    set<ANode> pQueueWeighted; // stores the ANodes with the A* weight function
    vector<double> distancesToFinish;
    ANode topANode;

    void populateQueue();

    bool foundOptimalSolution();

    bool isTopNodeDeadEnd() const;

    bool queueIsEmpty() const;

    void removeNodeFromQueue();

    void updateTopNode();

    void updateNodeOnQueue(const ANode & currNode);

    void updateQueue();

    void buildPath();

public:
    AStar(const Graph &graph);
};


#endif //CAL_ASTAR_H
