//
// Created by angelo on 27-03-2018.
//

#include "AStar.h"

AStar::AStar(const Graph &graph) : Dijkstra(graph) , topANode(0) {}


void AStar::populateQueue() {
    for (u_int i = 0; i < this->graph.getNumNodes(); i++) {

        if(i == this->startNode.getId()){
            //this->pQueue.emplace(this->graph.getNodeById(i),
            //                     0);
            this->pQueueWeighted.emplace(this->graph.getNodeById(i),
                                         0,
                                         this->graph.getNodeById(i).getDistanceToOtherNode(finishNode));
        } else {
            //this->pQueue.emplace(this->graph.getNodeById(i));
            this->pQueueWeighted.emplace(this->graph.getNodeById(i),
                                         this->graph.getNodeById(i).getDistanceToOtherNode(finishNode));
        }
    }
}

void AStar::updateQueue(){
    pQueueWeighted.erase(pQueueWeighted.begin());
    checkedDNodes.insert(DNode(topANode));

    for (Edge e : this->topANode.getEdges()) {
        DNode currDNode = DNode(this->graph.getNodeById(e.destNodeId));

        if (isCheckedNode(currDNode)) { // Already checked this node
            continue;
        }

        currDNode.setTotalWeight(topANode.getTotalWeight() + e.value); //update node's value
        currDNode.setLastNodeId(topANode.getId()); //set node's last node id (for path building later)
        updateNodeOnQueue(currDNode);

    }
}


bool AStar::foundOptimalSolution() {
    return (this->topANode.getId() == this->finishNode.getId());
}

/*
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
 /*
    
    updateNodeOnQueue(topDNode);
    return true;
}*/

void AStar::removeNodeFromQueue() {
    //this->pQueue.erase(topDNode);
    this->pQueueWeighted.erase(topANode);
}

void AStar::updateTopNode(){
    //this->topDNode = *(pQueue.begin());
    this->topANode = *(pQueueWeighted.begin());
}

void AStar::updateNodeOnQueue(const DNode & currDNode) {

    /*
    bool wasUpdated = false;

    for (DNode d : pQueue) {
        if (d.getId() == currDNode.getId()) {
            if (currDNode.getTotalWeight() < d.getTotalWeight()) {
                pQueue.erase(d);
                pQueue.insert(currDNode);
                wasUpdated = true;
                break;
            }
        }
    }

    // Better value was found! Update ANode aswell
    if (wasUpdated) {
        for (ANode a : pQueueWeighted) {
            if (a.getId() == currDNode.getId()) {
                pQueueWeighted.erase(a);
                pQueueWeighted.insert(ANode(topDNode , currDNode.getTotalWeight() + currDNode.getDistanceToOtherNode(finishNode)));
                return;
            }
        }
    }
     */

    for (ANode a : pQueueWeighted) {
        if (a.getId() == currDNode.getId()) {
            if (currDNode.getTotalWeight() < a.getTotalWeight()) {
                pQueueWeighted.erase(a);
                pQueueWeighted.insert(ANode(currDNode , currDNode.getTotalWeight() + currDNode.getDistanceToOtherNode(finishNode)));
                return;
            }
        }
    }
}

bool AStar::isTopNodeDeadEnd() const {
    return (this->topANode.getEdges().empty());
}

void AStar::buildPath() {

    this->solutionTotalCost = this->topANode.getTotalWeight();
    this->checkedDNodes.insert(DNode(topANode));

    lastSolution.clear();

    u_int currDNodeId = this->finishNode.getId();
    while (currDNodeId != UINT_MAX) {
        lastSolution.insert(lastSolution.begin(), currDNodeId);
        currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
    }
}

bool AStar::queueIsEmpty() const {
    return this->pQueueWeighted.empty();
}

