//
// Created by angelo on 27-03-2018.
//

#include "AStar.h"

AStar::AStar(const Graph &graph) : Dijkstra(graph) , topANode(0) {}


void AStar::populateQueue() {
    pQueueWeighted.clear();

    Node n;

    for (u_int i = 0; i < this->graph.getNumNodes(); i++) {
        n = graph.getNodeById(i);
        distancesToFinish.push_back(n.getDistanceToOtherNode(finishNode));

        if(i == this->startNode.getId()){
            this->pQueueWeighted.emplace(n, 0, n.getDistanceToOtherNode(finishNode));
        } else {
            this->pQueueWeighted.emplace(n);
        }
    }
}

void AStar::updateQueue(){
    pQueueWeighted.erase(pQueueWeighted.begin());
    checkedDNodes.insert(DNode(topANode));

    for (Edge e : this->topANode.getEdges()) {

        if (isCheckedNode(e.destNodeId)) { // Already checked this node
            continue;
        }

        ANode currNode = ANode(graph.getNodeById(e.destNodeId),
                               topANode.getId(),
                               topANode.getTotalWeight()+ e.value,
                               distancesToFinish.at(e.destNodeId));

        updateNodeOnQueue(currNode);
    }
}


bool AStar::foundOptimalSolution() {
    return (this->topANode.getId() == this->finishNode.getId());
}

void AStar::removeNodeFromQueue() {
    this->pQueueWeighted.erase(topANode);
}

void AStar::updateTopNode(){
    this->topANode = *(pQueueWeighted.begin());
}

void AStar::updateNodeOnQueue(const ANode & currNode) {

    for (set<ANode>::iterator it=pQueueWeighted.begin() ; it!=pQueueWeighted.end() ; it++) {
        if (it->getId() == currNode.getId()) {
            if (currNode.getHeuristicWeight() < it->getHeuristicWeight()) {
                pQueueWeighted.erase(it);
                pQueueWeighted.insert(currNode);
            }
            return;
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
