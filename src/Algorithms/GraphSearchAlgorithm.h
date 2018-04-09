#ifndef CAL_GRAPHSEARCHALGORITHM_H
#define CAL_GRAPHSEARCHALGORITHM_H

#include "../Graph/Node.h"
#include "../Graph/Graph.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <unordered_set>

using namespace std;

class GraphSearchAlgorithm {
protected:
    const Graph &graph;
    NodeHashTable visitedNodes;

    // Verifies if the node has already been visited
    bool isNodeVisited(const Node & node) const;

public:
    GraphSearchAlgorithm(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    virtual NodeHashTable performSearch(u_int startNodeId) = 0;

    // Verifies if it is possible to reach node with id 'finishNodeId' from node with id 'startNodeId'
    virtual bool isPathPossible(u_int startNodeId, u_int finishNodeId) = 0;

};


#endif //CAL_GRAPHSEARCHALGORITHM_H
