#include "TSPNearestNeighbor.h"

TSPNearestNeighbor::TSPNearestNeighbor(const Graph &graph) : graph(graph) , dfs(graph) {}

vector<u_int> TSPNearestNeighbor::calcPath(u_int startNodeId, u_int finishNodeId, const vector<u_int> & pointsOfInterest){

    initDataStructures();

    try {
        startNode = graph.getNodeById(startNodeId);
        finishNode = graph.getNodeById(finishNodeId);
        verifyValidNodes(pointsOfInterest);
    }
    catch(const InvalidNodeId & except) {
        throw except;
    }

    // When the visit order list is complete it should have the startNodeId + all the POIS ids in the correct order + finishNodeId
    visitOrderFinalSize = 2 + pois.size();

    findBestVisitOrder(startNode, finishNode);

    visitOrder.push_back(finishNodeId);

    // There was no possible path.
    if (visitOrder.size() != visitOrderFinalSize) {
        lastSolution.clear();
        return lastSolution;
    }
    else {
        buildSolution();
        return lastSolution;
    }
}

void TSPNearestNeighbor::printSolution() {
    cout << endl;
    if(lastSolution.empty()){
        cout << "No solution available. Run calcOptimalSolution before printing." << endl;
        return;
    }
    else {
        cout << "Successfully generated with a total weight of " << solutionTotalCost << ":" << endl;
        for(u_int nodeId : lastSolution){
            cout << nodeId << " ";
        }
        cout << endl;
    }
}

double TSPNearestNeighbor::getSolutionWeight() const {
    return solutionTotalCost;
}

void TSPNearestNeighbor::initDataStructures() {
    visitOrder.clear();
    lastSolution.clear();
    pois.clear();
}

void TSPNearestNeighbor::verifyValidNodes(const vector<u_int> & pointsOfInterest) {
    for (u_int id : pointsOfInterest) {
        if (id != startNode.getId() && id != finishNode.getId()) {
            try {
                pois.insert(graph.getNodeById(id));
            }
            catch (const InvalidNodeId & except) {
                throw except;
            }
        }
    }
}

void TSPNearestNeighbor::findBestVisitOrder(const Node & start, const Node & finish) {

    // Get reachable nodes
    NodeHashTable reachableNodes = dfs.performSearch(start.getId());

    // Verify if finish is reachable
    if (reachableNodes.find(finish) == reachableNodes.end()) {
        return;
    }

    // Verify if all pois are reachable
    for (Node n : pois) {
        if (reachableNodes.find(n) == reachableNodes.end()){
            return;
        }
    }

    // All are reachable from this node -> Add it to the visit order list and removed it from the POIs hash table
    addToVisitOrder(start);

    Node closestNode;
    NodeHashTable poisToVisit = pois;
    while(!poisToVisit.empty()) {
        closestNode = getClosestNode(startNode, poisToVisit);

        findBestVisitOrder(closestNode, finishNode);

        // If the list is not complete, the current order does not provide a possible path
        if (visitOrder.size() != visitOrderFinalSize-1) {
            poisToVisit.erase(closestNode);
        }
        else {
            return;
        }
    }

    // Perform back-tracking if solution wasn't achieved
    if (visitOrder.size() != visitOrderFinalSize-1) {
        removeFromVisitOrder(start);
    }

    return;
}

void TSPNearestNeighbor::addToVisitOrder(const Node & node) {
    visitOrder.push_back(node.getId());
    pois.erase(node);
}

void TSPNearestNeighbor::removeFromVisitOrder(const Node & node) {
    visitOrder.pop_back();
    pois.insert(node);
}

Node TSPNearestNeighbor::getClosestNode(const Node & node, const NodeHashTable otherNodes) const {
    Node closestNode = *(otherNodes.begin());
    double closestNodeDistance = node.getDistanceToOtherNode(closestNode);
    double dist;

    for (Node n : otherNodes){
        dist = node.getDistanceToOtherNode(n);
        if (dist < closestNodeDistance) {
            closestNode = n;
            closestNodeDistance = dist;
        }
    }

    return closestNode;
}

void TSPNearestNeighbor::buildSolution() {
    AStar astar(graph);
    solutionTotalCost = 0;

    for (u_int i=0 ; i<visitOrder.size()-1 ; i++) {
        append_vector(lastSolution,
                      astar.calcOptimalPath(visitOrder.at(i), visitOrder.at(i+1)));

        solutionTotalCost += astar.getSolutionWeight();

        if (i != visitOrder.size() - 2) {
            lastSolution.pop_back();
        }
    }
}


void TSPNearestNeighbor::append_vector(vector<u_int> & v1, const vector<u_int> & v2) {
    for (u_int i : v2){
        v1.push_back(i);
    }
}

vector<u_int> TSPNearestNeighbor::getVisitOrder() const {
    return this->visitOrder;
}