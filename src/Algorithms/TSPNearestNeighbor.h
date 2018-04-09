#ifndef CAL_TSPNEARESTNEIGHBOR_H
#define CAL_TSPNEARESTNEIGHBOR_H

#include "../Graph/Node.h"
#include "../Graph/Graph.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include "DFS.h"
#include "AStar.h"
#include <unordered_set>
#include <list>

using namespace std;

class TSPNearestNeighbor {
private:
    // Data Structures
    const Graph &graph;
    NodeHashTable pois;
    DFS dfs;
    vector<u_int> visitOrder;
    vector<u_int> lastSolution;

    // Variables for current calculation
    Node finishNode;
    Node startNode;
    double solutionTotalCost = DBL_MAX;
    u_int visitOrderFinalSize;

    // Verifies if nodes to visit are valid : throws InvalidNodeId(id) if invalid node is found!
    void verifyValidNodes(const vector<u_int> & pointsOfInterest);

    // Finds the best visit order between start and finish, placing that order in the 'visitOrder' list
    void findBestVisitOrder(const Node & start, const Node & finish);

    // Returns the closest node to 'node' in the 'otherNodes' hash table
    Node getClosestNode(const Node & node, const NodeHashTable otherNodes) const;

    // Adds 'node' to the visit order
    void addToVisitOrder(const Node & node);

    // Removes 'node' from the visit order
    void removeFromVisitOrder(const Node & node);

    // Builds the path by performing A-Star algorithm between the nodes in the visitOrder, in the corret order
    void buildSolution();

    // Appends two vectors
    void append_vector(vector<u_int> & v1, const vector<u_int> & v2);

    // Initializes Data Structures for algorithm to operate
    void initDataStructures();

public:
    TSPNearestNeighbor(const Graph &graph);

    // Calculates path between two nodes, passing through all the points of interest
    vector<u_int> calcPath(u_int startNodeId, u_int finishNodeId, const vector<u_int> & pois);

    // Returns a vector with the Points of Interest Visit Order
    vector<u_int> getVisitOrder() const;

    // Returns the solution weight, if there is a solution at the present moment
    double getSolutionWeight() const;
};


#endif //CAL_TSPNEARESTNEIGHBOR_H
