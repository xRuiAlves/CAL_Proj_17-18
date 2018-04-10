//
// Created by reeckset on 31-03-2018.
//

#include "DijkstraBiDir.h"
#include <thread>

DijkstraBiDir::DijkstraBiDir(const Graph &graph) : Dijkstra(graph){}

void DijkstraBiDir::initDataStructures(){
    Dijkstra::initDataStructures();
    pQueueReversed.clear();
    reversedEdges.clear();
    populateReversedEdges();
    populateReversedQueue();
    bestPOIId = UINT_MAX;
    regularSearchPOICounter = 0;
    reverseSearchPOICounter = 0;
    finishedSearch = false;
}

void DijkstraBiDir::populateReversedEdges(){
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

vector<u_int> DijkstraBiDir::calcOptimalPath(u_int startNodeId, u_int finishNodeId, const NodeHashTable & givenPois) {
    try {
        startNode = graph.getNodeById(startNodeId);
        finishNode = graph.getNodeById(finishNodeId);
    }
    catch(const InvalidNodeId & except) {
        throw except;
    }

    this->pois = givenPois;
    initDataStructures();

    std::thread t([=](){reverseSearch();});
    regularSearch();
    t.join();

    buildPath();

    return lastSolution;
}


void DijkstraBiDir::regularSearch(){

    updateTopNode(); //set this->topDNode

    while(!pQueue.empty() && topDNode.getTotalWeight() != DBL_MAX && !finishedSearch) {
        //Check if node is a dead end
        if (isTopNodeDeadEnd()) {
            removeNodeFromQueue();
        } else {
            //Analise next nodes and updateQueue
            updateQueue();
        }

        if (isNodePOI(topDNode)) {
            regularSearchPOICounter++;
        }

        //***LOOP BREAKING CONDITIONS***
        if (isReverseCheckedNode(topDNode.getId()) && isNodePOI(topDNode)) { //if node found in regular search was already found in reverse search

            updateBestPoi(topDNode);

            if ((regularSearchPOICounter == 1 && reverseSearchPOICounter == 1)) {
                finishedSearch = true;
                break;
            }
        }

        if(isReverseCheckedNode(topDNode.getId()) && pois.empty()){ //If there are no POIs, stop on the first common node
            bestPOIId = topDNode.getId();
            finishedSearch = true;
            break;
        }

        if (topDNode.getTotalWeight() >= bestPOIWeight) {
            break;
        }

        updateTopNode();
    }

}

void DijkstraBiDir::reverseSearch(){

    updateReversedTopNode(); //set this->topDNode

    //Analise the node on top of the priority queue
    while(!pQueueReversed.empty() && topDNodeReversed.getTotalWeight() != DBL_MAX && !finishedSearch){

        //Check if node is a dead end
        if (isReversedTopNodeDeadEnd()) {
            removeReversedTopNodeFromQueue();
        } else {
            //Analise next nodes and updateQueue
            updateReversedQueue();
        }

        if(isNodePOI(topDNodeReversed)){
            reverseSearchPOICounter++;
        }

        //***LOOP BREAKING CONDITIONS***
        if (isCheckedNode(topDNodeReversed.getId()) && isNodePOI(topDNodeReversed)) { //if node found in reverse search was already found in regular search

            updateBestPoi(topDNodeReversed);

            if ((regularSearchPOICounter == 1 && reverseSearchPOICounter == 1)) {
                finishedSearch = true;
                break;
            }
        }

        if(isCheckedNode(topDNodeReversed.getId()) && pois.empty()){ //If there are no POIs, stop on the first common node
            bestPOIId = topDNodeReversed.getId();
            finishedSearch = true;
            break;
        }

        if(topDNodeReversed.getTotalWeight() >= bestPOIWeight){
            break;
        }

        updateReversedTopNode();
    }
}

void DijkstraBiDir::populateReversedQueue() {
    for(u_int i = 0; i < graph.getNumNodes(); i++){
        if (i == this->finishNode.getId()) {
            this->pQueueReversed.emplace(this->finishNode,0);
        } else {
            this->pQueueReversed.emplace(this->graph.getNodeById(i));
        }
    }
}

void DijkstraBiDir::updateReversedQueue() {
    pQueueReversed.erase(pQueueReversed.begin());
    checkedDNodesReversed.insert(this->topDNodeReversed);

    for (Edge e : this->reversedEdges.at(topDNodeReversed.getId())) {

        if (isReverseCheckedNode(e.destNodeId)) { // Already checked this node
            continue;
        }

        DNode currDNode = DNode(this->graph.getNodeById(e.destNodeId),
                                topDNodeReversed.getId(),
                                topDNodeReversed.getTotalWeight() + e.value);

        updateNodeOnQueue(currDNode, pQueueReversed);
    }
}

void DijkstraBiDir::updateReversedTopNode(){
    this->topDNodeReversed = *(pQueueReversed.begin());
}

void DijkstraBiDir::updateBestPoi(const DNode & commonNode) {
        double nodeTotalWeight = (*checkedDNodes.find(commonNode)).getTotalWeight() + (*checkedDNodesReversed.find(commonNode)).getTotalWeight();
        if(nodeTotalWeight < bestPOIWeight){
            bestPOIWeight = nodeTotalWeight;
            bestPOIId = commonNode.getId();
        }
}

// Check if the current node has been analised (if it has, it will be in checkedDNodes)
bool DijkstraBiDir::isReverseCheckedNode(u_int nodeId) const {
    return (checkedDNodesReversed.find(nodeId) != checkedDNodesReversed.end());
}

bool DijkstraBiDir::isNodePOI(const Node & node) const{
    return pois.find(node) != pois.end();
}

void DijkstraBiDir::buildPath() {

    lastSolution.clear();

    if(bestPOIId != UINT_MAX) { //if a solution was found
        this->solutionTotalCost = (*checkedDNodesReversed.find(bestPOIId)).getTotalWeight() +
                                  (*checkedDNodes.find(bestPOIId)).getTotalWeight();

        this->checkedDNodesReversed.insert(topDNodeReversed);
        this->checkedDNodes.insert(topDNode);

        u_int currDNodeId = this->bestPOIId;
        while (currDNodeId != UINT_MAX) {
            lastSolution.insert(lastSolution.begin(), currDNodeId);
            currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
        }

        currDNodeId = (*checkedDNodesReversed.find(bestPOIId)).getLastNodeId();
        while (currDNodeId != UINT_MAX) {
            lastSolution.push_back(currDNodeId);
            currDNodeId = (*checkedDNodesReversed.find(currDNodeId)).getLastNodeId();
        }
    }
}

bool DijkstraBiDir::isReversedTopNodeDeadEnd() const {
    return reversedEdges.at(topDNodeReversed.getId()).empty();
}

void DijkstraBiDir::removeReversedTopNodeFromQueue() {
    this->pQueueReversed.erase(topDNodeReversed);
}

Node DijkstraBiDir::getBestPOI(){
    return graph.getNodeById(bestPOIId);
}

bool DijkstraBiDir::foundSolution() const {
    return !(checkedDNodes.empty() || lastSolution.empty());
}