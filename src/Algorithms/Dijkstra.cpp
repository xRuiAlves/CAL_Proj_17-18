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

    while (!pQueue.empty()) {
        //Analise the node on top of the priority queue

        //Check if already reached the optimal solution (finish node will be on top of the queue)
        if(foundOptimalSolution()) {
            this->solutionTotalCost = this->topDNode.getTotalWeight();
            this->checkedDNodes.insert(topDNode);
            buildPath();    //Fills 'lastSolution' with the computed solution
            return lastSolution;
        }

        //Check if node is a dead end
        if(isTopDNodeDeadEnd()) {
            this->pQueue.erase(this->pQueue.begin());
            updateTopDNode();
            continue;
        }

        //Analise next nodes and updateQueue
        updateQueue();

        //Delete parent from pQueue and put it in the hash table
        pQueue.erase(pQueue.begin());
        checkedDNodes.insert(this->topDNode);
        updateTopDNode(); //set this->topDNode
    }

    //No solution found, return empty vector
    lastSolution.clear();
    return lastSolution;
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
    cout << "Successfully generated with a total weight of " << getCheckedNode(finishNode.getId()).getTotalWeight() << ":" << endl;
    for(u_int nodeId : lastSolution){
        cout << nodeId << endl;
    }
}

void Dijkstra::populateQueue() {
    for (u_int i = 0; i < graph.getNumNodes(); i++) {
        if(i == this->startNode.getId()){
            pQueue.emplace(graph.getNodeById(i),0);
        }else {
            pQueue.emplace(graph.getNodeById(i));
        }
    }
}

// Check if the current node has been analised (if it has, it will be in checkedDNodes)
bool Dijkstra::isCheckedNode(const DNode &currDNode) const {
    return (checkedDNodes.find(currDNode) != checkedDNodes.end());
}

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
}

double Dijkstra::calcTotalWeight(const DNode & d) const {

    return d.getTotalWeight();
}

void Dijkstra::updateDNodeOnQueue(const DNode & currDNode) {

    if(isCheckedNode(currDNode)){
        return;
    }

    // If it has not been analised and the current path offers a better way, update it on the priority queue
    for (DNode d : pQueue) {
        if (d.getId() == currDNode.getId()) {
            if (calcTotalWeight(currDNode) < calcTotalWeight(d)) {
                pQueue.erase(d);
                pQueue.insert(currDNode);
                return;
            }
        }
    }
}

// Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
void Dijkstra::buildPath() {
    u_int currDNodeId = this->finishNode.getId();
    while (currDNodeId != UINT_MAX) {
        lastSolution.insert(lastSolution.begin(), currDNodeId);
        currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
    }
}

// Goes through queue's top node's children and updates them in the queue
void Dijkstra::updateQueue(){
    for (Edge e : this->topDNode.getEdges()) {
        DNode currDNode = getDNodeInQueueById(e.destNodeId); //get edge's destination
        if(currDNode.getTotalWeight() >= 0) {
            currDNode.setTotalWeight(topDNode.getTotalWeight() + e.value); //update node's value
            currDNode.setLastNodeId(topDNode.getId()); //set node's last node id (for path building later)
            updateDNodeOnQueue(currDNode); //
        }
    }
}

// Sets values of topDNode based on the current pQueue
void Dijkstra::updateTopDNode(){
    this->topDNode = *(pQueue.begin());
}

// Checks if the node on top of the queue is a dead end
bool Dijkstra::isTopDNodeDeadEnd() const {
    return (this->topDNode.getEdges().empty());
}

// Checks if the optimal solution has been found (if final node is on top of the queue)
bool Dijkstra::foundOptimalSolution() const{
    return (this->topDNode == this->finishNode);
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
    updateTopDNode();
}