//
// Created by reeckset on 10-04-2018.
//

#include "AStarBiDir.h"
#include <thread>

AStarBiDir::AStarBiDir(const Graph &graph) : AStar(graph), topNodeReversed(0){}

void AStarBiDir::initDataStructures(){
    AStar::initDataStructures();
    pQueueReversed.clear();
    reversedEdges.clear();
    populateReversedEdges();
    populateReversedQueue();
    populateDistancesToStart();
    commonNode = UINT_MAX;
    finishedSearch = false;
}

void AStarBiDir::populateReversedEdges(){
    //reversedEdges.assign(graph.getNumNodes(), EdgeList());
    reversedEdges.resize(graph.getNumNodes());
    for (u_int i = 0; i < graph.getNumNodes(); i++) {
        vector<Edge> nodeEdges = graph.getNodeById(i).getEdges();
        for (Edge e : nodeEdges){
            if(e.destNodeId >= graph.getNumNodes()) continue;
            reversedEdges.at(e.destNodeId).push_back(Edge(i, e.value));
        }
    }
}

vector<u_int> AStarBiDir::calcOptimalPath(u_int startNodeId, u_int finishNodeId) {
    try {
        startNode = graph.getNodeById(startNodeId);
        finishNode = graph.getNodeById(finishNodeId);
    }
    catch(const InvalidNodeId & except) {
        throw except;
    }

    initDataStructures();

    std::thread t([=](){regularSearch();});
    reverseSearch();
    t.join();

    buildPath();

    return lastSolution;
}


void AStarBiDir::regularSearch(){

    updateTopNode(); //set this->topANode

    while(!pQueueWeighted.empty() && topANode.getTotalWeight() != DBL_MAX && !finishedSearch) {
        //Check if node is a dead end
        if (isTopNodeDeadEnd()) {
            removeNodeFromQueue();
        } else {
            //Analise next nodes and updateQueue
            updateQueue();
        }

        if (isReverseCheckedNode(topANode.getId())) { //if node found in regular search was already found in reverse search
            commonNode = topANode.getId();
            finishedSearch = true;
            break;
        }

        updateTopNode();
    }

}

void AStarBiDir::reverseSearch(){

    updateReversedTopNode(); //set this->topANode

    //Analise the node on top of the priority queue
    while(!pQueueReversed.empty() && topNodeReversed.getTotalWeight() != DBL_MAX && !finishedSearch){

        //Check if node is a dead end
        if (isReversedTopNodeDeadEnd()) {
            removeReversedTopNodeFromQueue();
        } else {
            //Analise next nodes and updateQueue
            updateReversedQueue();
        }

        if (isCheckedNode(topNodeReversed.getId())) { //if node found in reverse search was already found in regular search
            commonNode = topNodeReversed.getId();
            finishedSearch = true;
            break;
        }

        updateReversedTopNode();
    }
}

void AStarBiDir::populateReversedQueue() {
    for(u_int i = 0; i < graph.getNumNodes(); i++){
        if (i == this->finishNode.getId()) {
            this->pQueueReversed.emplace(this->finishNode,0,0);
        } else {
            this->pQueueReversed.emplace(this->graph.getNodeById(i));
        }
    }
}

void AStarBiDir::updateReversedQueue() {
    pQueueReversed.erase(pQueueReversed.begin());
    checkedDNodesReversed.insert(DNode(topNodeReversed));

    vector<Edge> edges = this->reversedEdges.at(topNodeReversed.getId());

    for (Edge e : edges) {

        if (isReverseCheckedNode(e.destNodeId)) { // Already checked this node
            continue;
        }

        ANode currNode = ANode(graph.getNodeById(e.destNodeId),
                               topNodeReversed.getId(),
                               topNodeReversed.getTotalWeight() + e.value,
                               distancesToStart.at(e.destNodeId));


        updateNodeOnQueue(currNode, pQueueReversed);
    }
}

void AStarBiDir::updateReversedTopNode(){
    this->topNodeReversed = *(pQueueReversed.begin());
}

// Check if the current node has been analised (if it has, it will be in checkedDNodes)
bool AStarBiDir::isReverseCheckedNode(u_int nodeId) const {
    return (checkedDNodesReversed.find(nodeId) != checkedDNodesReversed.end());
}

void AStarBiDir::buildPath() {

    lastSolution.clear();

    if(commonNode != UINT_MAX) { //if a solution was found
        this->solutionTotalCost = (*checkedDNodesReversed.find(commonNode)).getTotalWeight() +
                                  (*checkedDNodes.find(commonNode)).getTotalWeight();

        this->checkedDNodesReversed.insert(topNodeReversed);
        this->checkedDNodes.insert(topANode);

        u_int currDNodeId = this->commonNode;
        while (currDNodeId != UINT_MAX) {
            lastSolution.insert(lastSolution.begin(), currDNodeId);
            currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
        }

        currDNodeId = (*checkedDNodesReversed.find(commonNode)).getLastNodeId();
        while (currDNodeId != UINT_MAX) {
            lastSolution.push_back(currDNodeId);
            currDNodeId = (*checkedDNodesReversed.find(currDNodeId)).getLastNodeId();
        }
    }
}

bool AStarBiDir::isReversedTopNodeDeadEnd() const {
    return reversedEdges.at(topNodeReversed.getId()).empty();
}

void AStarBiDir::removeReversedTopNodeFromQueue() {
    this->pQueueReversed.erase(topNodeReversed);
}

bool AStarBiDir::foundSolution() const {
    return !(checkedDNodes.empty() || lastSolution.empty());
}

void AStarBiDir::populateDistancesToStart(){
    for(int i = 0; i < graph.getNumNodes(); i++){
        this->distancesToStart.push_back(graph.getNodeById(i).getDistanceToOtherNode(startNode));
    }
}