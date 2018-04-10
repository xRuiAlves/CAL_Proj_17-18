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
    u_int bestPOIId = UINT_MAX;
    bool finishedSearch = false;


    // Clears the data structures for new calculation, populates DNodes pQueue and Reversed edges
    void initDataStructures();

    // Populates the reversed edges container
    void populateReversedEdges();

    // Populates the priority queue for the reversed Dijkstra Expansion
    void populateReversedQueue();

    // Updates the priority queue for the reversed Dijsktra Expansion
    void updateReversedQueue();

    // Check if the current node has been analised by the reversed Dijsktra Expansion
    // Iif it has, it will be in checkedDNodesReversed
    bool isReverseCheckedNode(u_int nodeId) const;

    // Verify if the node is in the POIs Hash Table
    bool isNodePOI(const Node & node) const;

    // Updates the topDNodeReversed
    void updateReversedTopNode();

    // Updates the current best point of interest
    void updateBestPoi(const DNode & commonNode);

    // Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
    void buildPath();

    // Checks if the node on top of the queue is a dead end
    bool isReversedTopNodeDeadEnd() const;

    // Removes the topDNode from the pQueue
    void removeReversedTopNodeFromQueue();

    // Reversed Dijkstra Expansion 'main loop'
    void reverseSearch();

    // Regular Dijkstra Expansion 'main loop'
    void regularSearch();

    void populateDistancesToStart();

public:
    AStarBiDir(const Graph &graph);

    // Calculates optimal path between two nodes, passing through all the points of interest
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId);

    // Returns the Node chosen as the best POI
    Node getBestPOI();

    // Verifies if there is a solution at the present moment
    bool foundSolution() const;
};

#endif //CAL_ASTARBIDIR_H
