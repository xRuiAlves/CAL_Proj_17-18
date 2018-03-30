#include "DFS.h"

DFS::DFS(const Graph & graph): graph(graph) {}

NodeHashTable DFS::performDephtFirstSearch(u_int startNodeId) {
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

bool DFS::isNodeVisited(const Node & node) const {
    return (visitedNodes.find(node) != visitedNodes.end());
}

void DFS::visitNode(const Node & node) {
    if (!isNodeVisited(node)){
        visitedNodes.insert(node);

        for (Edge e : node.getEdges()) {
            visitNode(graph.getNodeById(e.destNodeId));
        }
    }
}

void DFS::printSolution() const {
    if (visitedNodes.empty()) {
        cout << "No solution available. Run performDephtFirstSearch before printing." << endl;
    }
    else {
        cout << "Generated Solution with " << visitedNodes.size() << " reachable nodes: " << endl;

        int i = 0;
        for (Node node : visitedNodes) {
            if (i++ % 10 == 0) {
                cout << endl;
            }
            cout << node.getId() << "  ";
        }
    }
}