#include "BFS.h"
#include <queue>

BFS::BFS(const Graph & graph) : GraphSearchAlgorithm(graph) {}

NodeHashTable BFS::performSearch(u_int startNodeId) {
    Node startNode;

    try {
        startNode = graph.getNodeById(startNodeId);
    }
    catch (const InvalidNodeId & except) {
        throw except;
    }

    visitedNodes.clear();
    visitedNodes.insert(startNode);

    queue<Node> nodes;
    nodes.push(startNode);

    Node currentNode;

    while (!nodes.empty()) {
        for (Edge e : nodes.front().getEdges()) {
            currentNode = graph.getNodeById(e.destNodeId);
            if (!isNodeVisited(currentNode)) {
                nodes.push(currentNode);
                visitedNodes.insert(currentNode);
            }
        }
        nodes.pop();
    }

    return visitedNodes;
}