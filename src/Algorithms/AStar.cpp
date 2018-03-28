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
            this->pQueue.emplace(this->startNode, this->startNode.getDistanceToOtherNode(this->finishNode));
        }else {
            this->pQueue.emplace(this->graph.getNodeById(i));
        }
    }
}