#ifndef CAL_DFS_H
#define CAL_DFS_H

#include "GraphSearchAlgorithm.h"

class DFS : public GraphSearchAlgorithm {
private:
    void visitNode(const Node & node);

public:
    DFS(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    NodeHashTable performSearch(u_int startNodeId);
};


#endif //CAL_DFS_H
