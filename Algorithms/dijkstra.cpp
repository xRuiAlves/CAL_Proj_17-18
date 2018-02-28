//
// Created by Angelo on 28-02-2018.
//
#include <vector>
#include <queue>
#include <Graph/Graph.h>
#include "dijkstra.h"


std::vector<Node<char, int>> getShortestPath(Graph<char, int> g, Node<char, int> n1, Node<char, int> n2) {

    // each element of the queue is a DijkstraNode,
    // storing the current node, previous node, and total weight
    std::priority_queue<DijkstraNode> nodesToAnalyze;

    //starts the queue with the starting node
    nodesToAnalyze.emplace(n1, n1, 0);


    // stores the best path between n1 and n2
    std::vector<Node<char, int>> currentBestPath = {};
    int currentTotalWeight = 0; // stores the total weight, accumulated between nodes

    //TODO
//    while(!nodesToAnalyze.empty()) { // While not all required Nodes are processed
//
//        //process the first one
//
//    }

    return currentBestPath;
};

