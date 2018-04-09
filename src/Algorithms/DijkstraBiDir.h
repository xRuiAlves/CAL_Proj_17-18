//
// Created by reeckset on 31-03-2018.
//

#ifndef CAL_DIJKSTRABIDIR_H
#define CAL_DIJKSTRABIDIR_H

#include "Dijkstra.h"

typedef vector<Edge> EdgeList;

class DijkstraBiDir : public Dijkstra {
private:
    vector<EdgeList> reversedEdges;
    set<DNode> pQueueReversed;
    DNode topDNodeReversed;
    DNodeHashTable checkedDNodesReversed;
    NodeHashTable pois;
    double bestPOIWeight = DBL_MAX;
    u_int bestPOIId = UINT_MAX;
    u_int regularSearchPOICounter = 0;
    u_int reverseSearchPOICounter = 0;
    bool finishedSearch = false;


    // Clears the data structures for new calculation, populates DNodes pQueue and Reversed edges
    void initDataStructures();
    void populateReversedEdges();

    void populateReversedQueue();

    void updateReversedQueue();

    bool isReverseCheckedNode(u_int nodeId) const;

    bool isNodePOI(const Node & node) const;

    void updateReversedTopNode();

    void updateBestPoi(const DNode & commonNode);

    void buildPath();

    // Checks if the node on top of the queue is a dead end
    bool isReversedTopNodeDeadEnd() const;

    // Removes the topDNode from the pQueue
    void removeReversedTopNodeFromQueue();

    void reverseSearch();

    void regularSearch();

public:
    DijkstraBiDir(const Graph &graph);
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId, const NodeHashTable & pois);
    Node getBestPOI();
    bool foundSolution() const;
};


#endif //CAL_DIJKSTRABIDIR_H
