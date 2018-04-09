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
    bool isCheckedNode(u_int nodeId) const;

    // Updates a DNode in the pQueue
    void updateNodeOnQueue(const DNode & currDNode, set<DNode> & queue);

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

    // Clears the data structures for new calculation and populates DNodes pQueue
    virtual void initDataStructures();



public:

    Dijkstra(const Graph &graph);

    // Calculates optimal path between two nodes
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId);

    // Returns the solution weight, if there is a solution at the present moment
    double getSolutionWeight() const;

    // Verifies if there is a solution at the present moment
    bool foundSolution() const;
};

#endif //CAL_DIJKSTRA_H
