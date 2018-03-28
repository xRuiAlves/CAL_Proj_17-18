//
// Created by angelo on 27-03-2018.
//

#include "Dijkstra.h"

Dijkstra::Dijkstra(const Graph &graph): graph(graph) {}

// CALCULATE OPTIMAL PATH
vector<u_int> Dijkstra::calcOptimalPath(const Node &startNode, const Node &finishNode) {
    this->startNode = startNode;
    this->finishNode = finishNode;

    // Verify if ids are valid
    if( !(isNodeIdValid(startNode.getId()) && isNodeIdValid(finishNode.getId())) ){
        throw InvalidNodeId();
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

void Dijkstra::printSolution(){
    cout << endl;
    if(checkedDNodes.empty()){
        cout << "No solution available. Run calcOptimalSolution before printing" << endl;
        return;
    }
    cout << "Optimal path between " << this->startNode.getId() << " and " << this->finishNode.getId() << endl;
    if(getCheckedNode(finishNode.getId()).getTotalWeight() == DBL_MAX){
        cout << "No path could be calculated. Could not print." << endl;
        return;
    }
    cout << "Successfully generated with a total weight of " << solutionTotalCost << ":" << endl;
    for(u_int nodeId : lastSolution){
        cout << nodeId  /*
             << " - W : "
             << checkedDNodes.find(nodeId)->getTotalWeight()
             << " distToEnd: "
             << checkedDNodes.find(nodeId)->getDistanceToOtherNode(finishNode)
             << " Path Weight: "
             << checkedDNodes.find(nodeId)->getTotalWeight() - checkedDNodes.find(nodeId)->getDistanceToOtherNode(finishNode) */
             << "  ";
    }
}

void Dijkstra::removeNodeFromQueue() {
    this->pQueue.erase(topDNode);
}

void Dijkstra::populateQueue() {
    for (u_int i = 0; i < this->graph.getNumNodes(); i++) {
        if(i == this->startNode.getId()){
            this->pQueue.emplace(this->startNode,0);
        }else {
            this->pQueue.emplace(this->graph.getNodeById(i));
        }
    }
}

// Check if the current node has been analised (if it has, it will be in checkedDNodes)
bool Dijkstra::isCheckedNode(const DNode &currDNode) const {
    return (checkedDNodes.find(currDNode) != checkedDNodes.end());
}

/*
// Gets the node in the queue for a specified id (returns node with weight -1 if it cant find it)
DNode Dijkstra::getDNodeInQueueById(u_int id) const {
    DNode badResult = DNode(id);
    badResult.setTotalWeight(-1); //means node is not in queue

    if(isCheckedNode(DNode(id))) return badResult;

    for (DNode d : pQueue) {
        if (d.getId() == id) {
            return d;
        }
    }

    return badResult;
} */


void Dijkstra::updateNodeOnQueue(const DNode & currDNode) {
    // If it has not been analised and the current path offers a better way, update it on the priority queue
    for (DNode d : pQueue) {
        if (d.getId() == currDNode.getId()) {
            if (currDNode.getTotalWeight() < d.getTotalWeight()) {
                pQueue.erase(d);
                pQueue.insert(currDNode);
                return;
            }
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
    pQueue.erase(pQueue.find(topDNode));
    checkedDNodes.insert(this->topDNode);

    for (Edge e : this->topDNode.getEdges()) {

        //get edge's destination
        DNode currDNode = DNode(this->graph.getNodeById(e.destNodeId));

        if (isCheckedNode(currDNode)) { // Already checked this node
            continue;
        }

        currDNode.setLastNodeId(topDNode.getId());
        currDNode.setTotalWeight(topDNode.getTotalWeight() + e.value);

        updateNodeOnQueue(currDNode);
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

// Checks if a Node Id is valid within the graph
bool Dijkstra::isNodeIdValid(u_int nodeID) const{
    return (nodeID < graph.getNumNodes());
}

// Clears the data structures for new calculation and populates DNodes pQueue
void Dijkstra::initDataStructures() {
    pQueue.clear();
    checkedDNodes.clear();
    lastSolution.clear();
    populateQueue();
}