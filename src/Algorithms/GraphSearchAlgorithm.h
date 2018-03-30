#ifndef CAL_GRAPHSEARCHALGORITHM_H
#define CAL_GRAPHSEARCHALGORITHM_H

#include "../Graph/Node.h"
#include "../Graph/Graph.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <unordered_set>

using namespace std;

struct NodeHash {
    bool operator()(const Node &d1, const Node &d2) const {
        return d1.getId() == d2.getId();
    }

    int operator()(const Node &d) const {
        return d.getId();
    }
};

typedef unordered_set<Node, NodeHash, NodeHash> NodeHashTable;

class GraphSearchAlgorithm {
protected:
    const Graph &graph;
    NodeHashTable visitedNodes;

    bool isNodeVisited(const Node & node) const;

public:
    GraphSearchAlgorithm(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    virtual NodeHashTable performSearch(u_int startNodeId) = 0;

    // Prints NodeHashTable contents
    void printSolution() const;

};


#endif //CAL_GRAPHSEARCHALGORITHM_H
