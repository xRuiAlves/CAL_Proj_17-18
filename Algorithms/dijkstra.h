//
// Created by angelo on 28-02-2018.
//

#ifndef CAL_PROJ_17_18_DIJKSTRA_H
#define CAL_PROJ_17_18_DIJKSTRA_H

struct DijkstraNode {
    Node<char, int> node;
    Node<char, int> previousNode;
    int totalWeight;

    DijkstraNode(Node<char,int> currNode, Node<char,int> prevNode, int totalWeight) {
        this->node = currNode;
        this->previousNode = prevNode;
        this->totalWeight = totalWeight;
    }

    friend bool operator<(const DijkstraNode & d1, const DijkstraNode & d2) {
        return d1.totalWeight < d2.totalWeight;
    }
};


//Returns an ordered vector of Nodes, representing the shortest path to take between given Nodes n1 and n2
std::vector<Node<char, int>> getShortestPath(Graph<char, int> g, Node<char, int> n1, Node<char, int> n2);


#endif //CAL_PROJ_17_18_DIJKSTRA_H
