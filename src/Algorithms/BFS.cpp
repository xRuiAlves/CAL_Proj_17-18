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

// Verifies if it is possible to reach node with id 'finishNodeId' from node with id 'startNodeId'
bool BFS::isPathPossible(u_int startNodeId, u_int finishNodeId) {
    if (startNodeId == finishNodeId) {
        return true;
    }

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
    visitedNodes.insert(startNode);

    queue<Node> nodes;
    nodes.push(startNode);

    Node currentNode;

    while (!nodes.empty()) {

        for (Edge e : nodes.front().getEdges()) {
            currentNode = graph.getNodeById(e.destNodeId);

            if (currentNode == finishNode) {
                return true;
            }
            else if (!isNodeVisited(currentNode)) {
                nodes.push(currentNode);
                visitedNodes.insert(currentNode);
            }
        }
        nodes.pop();
    }

    return false;
}