//
// Created by reeckset on 10-04-2018.
//

#ifndef CAL_ASTARBIDIR_H
#define CAL_ASTARBIDIR_H


#include "AStar.h"

typedef vector<Edge> EdgeList;

class AStarBiDir : public AStar {
private:
    vector<double> distancesToStart;
    vector<EdgeList> reversedEdges;
    set<ANode> pQueueReversed;
    ANode topNodeReversed;
    DNodeHashTable checkedDNodesReversed;
    double bestPOIWeight = DBL_MAX;
    u_int commonNode = UINT_MAX;
    bool finishedSearch = false;


    // Clears the data structures for new calculation, populates ANodes pQueue and Reversed edges
    void initDataStructures();

    // Populates the reversed edges container
    void populateReversedEdges();

    // Populates the priority queue for the reversed A* Expansion
    void populateReversedQueue();

    // Updates the priority queue for the reversed A* Expansion
    void updateReversedQueue();

    // Check if the current node has been analised by the reversed A* Expansion
    // Iif it has, it will be in checkedDNodesReversed
    bool isReverseCheckedNode(u_int nodeId) const;

    // Updates the topDNodeReversed
    void updateReversedTopNode();

    // Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
    void buildPath();

    // Checks if the node on top of the queue is a dead end
    bool isReversedTopNodeDeadEnd() const;

    // Removes the topDNode from the pQueue
    void removeReversedTopNodeFromQueue();

    // Reversed A* Expansion 'main loop'
    void reverseSearch();

    // Regular A* Expansion 'main loop'
    void regularSearch();

    void populateDistancesToStart();

public:
    AStarBiDir(const Graph &graph);

    // Calculates optimal path between two nodes, passing through all the points of interest
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId);

    // Verifies if there is a solution at the present moment
    bool foundSolution() const;
};

#endif //CAL_ASTARBIDIR_H
