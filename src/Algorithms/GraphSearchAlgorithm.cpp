#include "GraphSearchAlgorithm.h"

GraphSearchAlgorithm::GraphSearchAlgorithm(const Graph & graph) : graph(graph) {}

bool GraphSearchAlgorithm::isNodeVisited(const Node & node) const {
    return (visitedNodes.find(node) != visitedNodes.end());
}