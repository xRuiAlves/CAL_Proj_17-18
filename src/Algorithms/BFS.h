#ifndef CAL_BFS_H
#define CAL_BFS_H

#include "GraphSearchAlgorithm.h"

class BFS : public GraphSearchAlgorithm {
public:
    BFS(const Graph & graph);

    // Returns hash table with the nodes that are reachable starting in startNode
    NodeHashTable performSearch(u_int startNodeId);

    // Verifies if it is possible to reach node with id 'finishNodeId' from node with id 'startNodeId'
    bool isPathPossible(u_int startNodeId, u_int finishNodeId);
};


#endif //CAL_BFS_H
