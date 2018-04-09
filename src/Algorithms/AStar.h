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

    // Populates the ANode priority Queue
    void populateQueue();

    // Verifies if optimal solution if found in the present calculation
    bool foundOptimalSolution();

    // Verifies if the node has no edges (not relevant for solution)
    bool isTopNodeDeadEnd() const;

    // Verifies if the ANode priority Queue is empty
    bool queueIsEmpty() const;

    // Removes the top from the ANode priority Queue
    void removeNodeFromQueue();

    // Updates top ANode
    void updateTopNode();

    // Updates a node in the ANode priority Queue, by removing it, changing it and inserting it again
    void updateNodeOnQueue(const ANode & currNode);

    // Updates the priority Queue
    void updateQueue();

    // Builds the final path to return it to the the user
    void buildPath();

public:
    AStar(const Graph &graph);
};


#endif //CAL_ASTAR_H
