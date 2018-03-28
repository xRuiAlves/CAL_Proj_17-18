//
// Created by angelo on 27-03-2018.
//

#include "AStar.h"

AStar::AStar(const Graph &graph) : Dijkstra(graph) {}



void AStar::updateQueue(){
    for (Edge e : this->topDNode.getEdges()) {
        DNode currDNode = getDNodeInQueueById(e.destNodeId); //get edge's destination
        if(currDNode.getTotalWeight() >= 0) {
            currDNode.setTotalWeight(topDNode.getTotalWeight()
                                     + e.value
                                     + currDNode.getDistanceToOtherNode(this->finishNode)
                                     - topDNode.getDistanceToOtherNode(finishNode)); //update node's value
            currDNode.setLastNodeId(topDNode.getId()); //set node's last node id (for path building later)
            updateDNodeOnQueue(currDNode); //
        }
    }
}

void AStar::populateQueue() {
    for (u_int i = 0; i < this->graph.getNumNodes(); i++) {
        if(i == this->startNode.getId()){
            this->pQueue.emplace(this->graph.getNodeById(i),
                                 this->graph.getNodeById(i).getDistanceToOtherNode(this->finishNode));
        }else {
            this->pQueue.emplace(this->graph.getNodeById(i));
        }
    }
}

bool AStar::foundOptimalSolution() {
    if (this->topDNode.getId() != this->finishNode.getId()) {
        return false;
    }

    checkedDNodes.insert(topDNode);

    if (lastSolution.empty()) {
        buildPath();
        currentBestSolution = lastSolution;
        currentBestSolutionWeight = topDNode.getTotalWeight();
    } else {
        buildPath();
    }

    checkedDNodes.erase(topDNode);
    this->solutionTotalCost = this->topDNode.getTotalWeight();


    if (topDNode.getTotalWeight() < currentBestSolutionWeight) {
        currentBestSolution = lastSolution;
        currentBestSolutionWeight = topDNode.getTotalWeight();
    } else {
        lastSolution = currentBestSolution;
    }

    // Check for other potential candidates for best path, that is, nodes with less weight (without the euclidian
    // distance to the finish node)
    /*for (DNode d : pQueue) {
        if ( (d.getTotalWeight()-d.getDistanceToOtherNode(finishNode)) <= topDNode.getTotalWeight()) {
            this->topDNode = d;
            return false;
        }
    }*/

    // If no other node has potential to become a better path solution, then the optimal solution was found
    
    updateDNodeOnQueue(topDNode);
    return true;
}