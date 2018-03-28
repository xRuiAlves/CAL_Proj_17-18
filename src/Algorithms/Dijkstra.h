//
// Created by reeckset on 10-03-2018.
//

#ifndef CAL_DIJKSTRA_H
#define CAL_DIJKSTRA_H

#include "../Graph/Graph.h"
#include "../Graph/DNode.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <set>
#include <unordered_set>

using namespace std;

struct DNodeHash {
    bool operator()(const DNode &d1, const DNode &d2) const {
        return d1 == d2;
    }

    int operator()(const DNode &d) const {
        return d.getId();
    }
};


typedef unordered_set<DNode, DNodeHash, DNodeHash> DNodeHashTable;


class Dijkstra {
protected:
    // Data Structures
    const Graph &graph;
    set<DNode > pQueue;
    DNodeHashTable checkedDNodes;

    // Variables for current calculation
    Node finishNode;
    Node startNode;
    double solutionTotalCost = DBL_MAX;
    DNode topDNode;

    vector<u_int> lastSolution;

    // Sets all queue's elements to the nodes in the graph and then puts the first node on top
    virtual void populateQueue();

    // Check if the current node has been analised (if it has, it will be in checkedDNodes)
    bool isCheckedNode(const DNode &currDNode) const;

    // Gets the node in the queue for a specified id (returns node with weight -1 if it cant find it)
    // virtual DNode getDNodeInQueueById(u_int id) const;

    // Updates a DNode in the pQueue
    virtual void updateNodeOnQueue(const DNode & currDNode);

    // Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
    virtual void buildPath();

    // Removes the topDNode from the pQueue
    virtual void removeNodeFromQueue();

    // Goes through queue's top node's children and updates them in the queue
    virtual void updateQueue();

    // Sets values of topDNode based on the current pQueue
    virtual void updateTopNode();

    // Checks if the node on top of the queue is a dead end
    virtual bool isTopNodeDeadEnd() const;

    // Checks if the optimal solution has been found (if final node is on top of the queue)
    virtual bool foundOptimalSolution();

    // Verifies if the priority Queue is empty.
    virtual bool queueIsEmpty() const;

    // Retrived a node in checkedNodes by its id
    DNode getCheckedNode(u_int id) const;

    // Checks if a Node Id is valid within the graph
    bool isNodeIdValid(u_int nodeID) const;

    // Clears the data structures for new calculation and populates DNodes pQueue
    void initDataStructures();



public:

    Dijkstra(const Graph &graph);

    // CALCULATE OPTIMAL PATH
    vector<u_int> calcOptimalPath(const Node &startNode, const Node &finishNode);

    //Prints the solution found
    void printSolution();
};

#endif //CAL_DIJKSTRA_H
