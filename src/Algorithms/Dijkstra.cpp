//
// Created by angelo on 27-03-2018.
//

#include "Dijkstra.h"

Dijkstra::Dijkstra(const Graph &graph): graph(graph) {}

// CALCULATE OPTIMAL PATH
vector<u_int> Dijkstra::calcOptimalPath(u_int startNodeId, u_int finishNodeId) {

    try {
        startNode = graph.getNodeById(startNodeId);
        finishNode = graph.getNodeById(finishNodeId);
    }
    catch(const InvalidNodeId & except) {
        throw except;
    }

    initDataStructures();

    while (!queueIsEmpty()) {
        //Analise the node on top of the priority queue
        updateTopNode(); //set this->topDNode

        //Check if already reached the optimal solution (finish node will be on top of the queue)
        if(foundOptimalSolution()) {
            buildPath();    //Fills 'lastSolution' with the computed solution
            break;
        }

        //Check if node is a dead end
        if(isTopNodeDeadEnd()) {
            removeNodeFromQueue();
            continue;
        }

        //Analise next nodes and updateQueue
        updateQueue();

    }

    return lastSolution;
}

bool Dijkstra::queueIsEmpty() const {
    return this->pQueue.empty();
}

void Dijkstra::removeNodeFromQueue() {
    this->pQueue.erase(topDNode);
}

void Dijkstra::populateQueue() {
    pQueue.clear();

    for (u_int i = 0; i < this->graph.getNumNodes(); i++) {
        if (i == this->startNode.getId()) {
            this->pQueue.emplace(this->startNode,0);
        } else {
            this->pQueue.emplace(this->graph.getNodeById(i));
        }
    }
}

// Check if the current node has been analised (if it has, it will be in checkedDNodes)
bool Dijkstra::isCheckedNode(u_int nodeId) const {
    return (checkedDNodes.find(nodeId) != checkedDNodes.end());
}

void Dijkstra::updateNodeOnQueue(const DNode & currDNode, set<DNode> & queue) {
    // If it has not been analised and the current path offers a better way, update it on the priority queue
    for (set<DNode>::iterator it=queue.begin() ; it!=queue.end() ; it++) {
        if (it->getId() == currDNode.getId()) {
            if (currDNode.getTotalWeight() < it->getTotalWeight()) {
                queue.erase(it);
                queue.insert(currDNode);
            }
            return;
        }
    }
}

// Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
void Dijkstra::buildPath() {

    this->solutionTotalCost = this->topDNode.getTotalWeight();
    this->checkedDNodes.insert(topDNode);

    lastSolution.clear();

    u_int currDNodeId = this->finishNode.getId();
    while (currDNodeId != UINT_MAX) {
        lastSolution.insert(lastSolution.begin(), currDNodeId);
        currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
    }
}

// Goes through queue's top node's children and updates them in the queue
void Dijkstra::updateQueue(){
    pQueue.erase(pQueue.begin());
    checkedDNodes.insert(this->topDNode);

    for (Edge e : this->topDNode.getEdges()) {

        if (isCheckedNode(e.destNodeId)) { // Already checked this node
            continue;
        }

        //get edge's destination
        DNode currDNode = DNode(this->graph.getNodeById(e.destNodeId),
                                topDNode.getId(),
                                topDNode.getTotalWeight() + e.value);

        updateNodeOnQueue(currDNode, pQueue);
    }
}

// Sets values of topDNode based on the current pQueue
void Dijkstra::updateTopNode(){
    this->topDNode = *(pQueue.begin());
}

// Checks if the node on top of the queue is a dead end
bool Dijkstra::isTopNodeDeadEnd() const {
    return (this->topDNode.getEdges().empty());
}

// Checks if the optimal solution has been found (if final node is on top of the queue)
bool Dijkstra::foundOptimalSolution() {
    return (this->topDNode.getId() == this->finishNode.getId());
}

// Retrived a node in checkedNodes by its id
DNode Dijkstra::getCheckedNode(u_int id) const{
    return *(this->checkedDNodes.find(DNode(id)));
}

// Clears the data structures for new calculation and populates DNodes pQueue
void Dijkstra::initDataStructures() {
    checkedDNodes.clear();
    lastSolution.clear();
    populateQueue();
}

double Dijkstra::getSolutionWeight() const{
    return solutionTotalCost;
}

bool Dijkstra::foundSolution() const {
    return !(checkedDNodes.empty() || getCheckedNode(finishNode.getId()).getTotalWeight() == DBL_MAX);
}
