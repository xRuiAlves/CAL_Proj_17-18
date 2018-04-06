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

bool DFS::isPathPossible(u_int startNodeId, u_int finishNodeId) {
    Node startNode;
    Node finishNode;

    try {
        startNode = graph.getNodeById(startNodeId);
        finishNode = graph.getNodeById(finishNodeId);
    }
    catch (const InvalidNodeId & except) {
        throw except;
    }

    visitedNodes.clear();
    return visitNodeWithCondition(startNode, finishNode);
}

bool DFS::visitNodeWithCondition(const Node & node, const Node & finishNode) {
    if (node == finishNode) {
        return true;
    }

    if (!isNodeVisited(node)){
        visitedNodes.insert(node);

        for (Edge e : node.getEdges()) {
            if (visitNodeWithCondition(graph.getNodeById(e.destNodeId), finishNode)) {
                return true;
            }
        }
    }

    return false;
}