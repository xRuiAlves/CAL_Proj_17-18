//
// Created by reeckset on 10-03-2018.
//

#ifndef CAL_DIJKSTRA_H
#define CAL_DIJKSTRA_H

#include "../Graph/Graph.h"
#include "../Graph/DNode.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include <set>
#include <unordered_set>

using namespace std;


struct DNodeHash {
    bool operator()(const DNode &d1, const DNode &d2) const {
        return d1 == d2;
    }

    int operator()(const DNode &d) const {
        return d.getId();
    }
};


class Dijkstra {

    const Graph &graph;
    set<DNode > pQueue;
    unordered_set<DNode, DNodeHash, DNodeHash> checkedDNodes;

    //Variables for current calculation
    const Node &finishNode;
    const Node &startNode;
    double solutionTotalCost = DBL_MAX;
    DNode topDNode;

    vector<u_int> lastSolution;

    //Sets all queue's elements to the nodes in the graph and then puts the first node on top
    void populateQueue() {
        for (u_int i = 0; i < graph.getNumNodes(); i++) {
            if(i == this->startNode.getId()){
                pQueue.emplace(graph.getNodeById(i),0);
            }else {
                pQueue.emplace(graph.getNodeById(i));
            }
        }
    }

    bool isCheckedNode(const DNode &currDNode){
        //check if the current node has been analised (if it has, it will be in checkedDNodes)
        return this->checkedDNodes.find(currDNode) != this->checkedDNodes.end();
    }

    //Gets the node in the queue for a specified id (returns node with weight -1 if it cant find it)
    DNode getDNodeInQueueById(u_int id) {
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

    void updateDNodeOnQueue(DNode currDNode) {

        if(isCheckedNode(currDNode)) return;

        //if it has not been analised and the current path offers a better way, update it on the priority queue
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

    //Takes the finish node that should be on top of the queue and creates a path from recurrent previous nodes
    void buildPath() {
        lastSolution.clear();
        u_int currDNodeId = this->finishNode.getId();
        while (currDNodeId != UINT_MAX) {
            lastSolution.insert(lastSolution.begin(), currDNodeId);
            currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
        }
    }

    //Goes through queue's top node's children and updates them in the queue
    void updateQueue(){
        for (Edge e : this->topDNode.getEdges()) {
            DNode currDNode = getDNodeInQueueById(e.destNodeId); //get edge's destination
            if(currDNode.getTotalWeight() >= 0) {
                currDNode.setTotalWeight(topDNode.getTotalWeight() + e.value); //update node's value
                currDNode.setLastNodeId(topDNode.getId()); //set node's last node id (for path building later)
                updateDNodeOnQueue(currDNode); //
            }
        }
    }

    //Sets values of topDNode based on the current pQueue
    void updateTopDNode(){
        this->topDNode = *(pQueue.begin());
    }

    //Checks if the node on top of the queue is a dead end
    bool isTopDNodeDeadEnd(){
        if (this->topDNode.getEdges().empty()) {
            return true;
        }
        return false;
    }

    //Checks if the optimal solution has been found (if final node is on top of the queue)
    bool foundOptimalSolution(){
        if (this->topDNode == this->finishNode) {
            this->solutionTotalCost = this->pQueue.begin()->getTotalWeight();
            this->checkedDNodes.insert(topDNode);
            return true;
        }
        return false;
    }

    //retrived a node in checkedNodes by its id
    DNode getCheckedNode(u_int id){
        return *(this->checkedDNodes.find(DNode(id)));
    }

    //Checks if a Node Id is valid within the graph
    bool isNodeIdValid(u_int nodeID){
        return (nodeID < graph.getNumNodes());
    }

public:

    Dijkstra(const Graph &graph, const Node &startNode, const Node &finishNode): graph(graph), startNode(startNode), finishNode(finishNode){
        if( !(isNodeIdValid(startNode.getId()) && isNodeIdValid(finishNode.getId())) ){
            // Invalid Node Found
            throw InvalidNodeId();
        }

    }

    //CALCULATE OPTIMAL PATH
    vector<u_int> calcOptimalPath() {
        checkedDNodes.clear();
        populateQueue();
        updateTopDNode();
        while (!pQueue.empty()) {
            //Analise the node on top of the priority queue

            //Check if already reached the optimal solution (finish node will be on top of the queue)
            if(foundOptimalSolution()) {
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

    void printSolution(){
        cout << endl;
        if(checkedDNodes.empty()){
            cout << "No solution available. Run calcOptimalSolution before printing" << endl;
            return;
        }
        cout << "Dijkstra optimal path between " << this->startNode.getId() << " and " << this->finishNode.getId() << endl;
        if(getCheckedNode(finishNode.getId()).getTotalWeight() == DBL_MAX){
            cout << "No path could be calculated. Could not print." << endl;
            return;
        }
        cout << "Successfully generated with a total weight of " << getCheckedNode(finishNode.getId()).getTotalWeight() << ":" << endl;
        for(u_int nodeId : lastSolution){
            cout << nodeId << endl;
        }
    }
};

#endif //CAL_DIJKSTRA_H
