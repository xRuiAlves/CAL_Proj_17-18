#ifndef CAL_DFS_H
#define CAL_DFS_H

#include "GraphSearchAlgorithm.h"

class DFS : public GraphSearchAlgorithm {
private:
    // Visits a node, adding it to the 'visitedNodes' hash table if it has not been visited yet
    void visitNode(const Node & node);

    // Visits a node and verifies if it is the 'target node' (finish Node)
    bool visitNodeWithCondition(const Node & node, const Node & finishNode);

public:
    DFS(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    NodeHashTable performSearch(u_int startNodeId);

    // Verifies if it is possible to reach node with id 'finishNodeId' from node with id 'startNodeId'
    bool isPathPossible(u_int startNodeId, u_int finishNodeId);
};


#endif //CAL_DFS_H
