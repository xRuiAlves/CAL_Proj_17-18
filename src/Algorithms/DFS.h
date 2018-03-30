#ifndef CAL_DFS_H
#define CAL_DFS_H

#include "../Graph/Graph.h"
#include "../Graph/Node.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <set>
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

class DFS {
private:
    const Graph &graph;
    NodeHashTable visitedNodes;

    bool isNodeVisited(const Node & node) const;

    void visitNode(const Node & node);

public:
    DFS(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    NodeHashTable performDephtFirstSearch(u_int startNodeId);

    // Prints NodeHashTable contents
    void printSolution() const;
};


#endif //CAL_DFS_H
