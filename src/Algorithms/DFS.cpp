#include "DFS.h"

DFS::DFS(const Graph & graph): GraphSearchAlgorithm(graph) {}

NodeHashTable DFS::performSearch(u_int startNodeId) {
    Node startNode;

    try {
        startNode = graph.getNodeById(startNodeId);
    }
    catch (const InvalidNodeId & except) {
        throw except;
    }

    visitedNodes.clear();
    visitNode(startNode);

    return visitedNodes;
}

void DFS::visitNode(const Node & node) {
    if (!isNodeVisited(node)){
        visitedNodes.insert(node);

        for (Edge e : node.getEdges()) {
            visitNode(graph.getNodeById(e.destNodeId));
        }
    }
}