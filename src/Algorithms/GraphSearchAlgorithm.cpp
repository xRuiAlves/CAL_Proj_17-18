#include "GraphSearchAlgorithm.h"

GraphSearchAlgorithm::GraphSearchAlgorithm(const Graph & graph) : graph(graph) {}

bool GraphSearchAlgorithm::isNodeVisited(const Node & node) const {
    return (visitedNodes.find(node) != visitedNodes.end());
}

void GraphSearchAlgorithm::printSolution() const {
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