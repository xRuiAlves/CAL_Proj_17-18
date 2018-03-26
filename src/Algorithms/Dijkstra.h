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


typedef unordered_set<DNode, DNodeHash, DNodeHash> DNodeHashTable;


class Dijkstra {
private:
    // Data Structures
    const Graph &graph;
    set<DNode > pQueue;
    DNodeHashTable checkedDNodes;

    // Variables for current calculation
    Node finishNode;
    Node startNode;
    double solutionTotalCost = DBL_MAX;
    DNode topDNode;     // TODO: Not necessary, should be removed later !!!

    vector<u_int> lastSolution;

    // Sets all queue's elements to the nodes in the graph and then puts the first node on top
    void populateQueue() {
        for (u_int i = 0; i < graph.getNumNodes(); i++) {
            if(i == this->startNode.getId()){
                pQueue.emplace(graph.getNodeById(i),0);
            }else {
                pQueue.emplace(graph.getNodeById(i));
            }
        }
    }

    // Check if the current node has been analised (if it has, it will be in checkedDNodes)
    bool isCheckedNode(const DNode &currDNode) const {
        return (checkedDNodes.find(currDNode) != checkedDNodes.end());
    }

    // Gets the node in the queue for a specified id (returns node with weight -1 if it cant find it)
    DNode getDNodeInQueueById(u_int id) const {
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

    double calcTotalWeight(const DNode & d) const {
        return d.getTotalWeight();
    }

    void updateDNodeOnQueue(const DNode & currDNode) {

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
    void buildPath() {
        u_int currDNodeId = this->finishNode.getId();
        while (currDNodeId != UINT_MAX) {
            lastSolution.insert(lastSolution.begin(), currDNodeId);
            currDNodeId = getCheckedNode(currDNodeId).getLastNodeId();
        }
    }

    // Goes through queue's top node's children and updates them in the queue
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

    // Sets values of topDNode based on the current pQueue
    void updateTopDNode(){
        this->topDNode = *(pQueue.begin());
    }

    // Checks if the node on top of the queue is a dead end
    bool isTopDNodeDeadEnd() const {
        return (this->topDNode.getEdges().empty());
    }

    // Checks if the optimal solution has been found (if final node is on top of the queue)
    bool foundOptimalSolution() const{
        return (this->topDNode == this->finishNode);
    }

    // Retrived a node in checkedNodes by its id
    DNode getCheckedNode(u_int id) const{
        return *(this->checkedDNodes.find(DNode(id)));
    }

    // Checks if a Node Id is valid within the graph
    bool isNodeIdValid(u_int nodeID) const{
        return (nodeID < graph.getNumNodes());
    }

    // Clears the data structures for new calculation and populates DNodes pQueue
    void initDataStructures() {
        pQueue.clear();
        checkedDNodes.clear();
        lastSolution.clear();
        populateQueue();
        updateTopDNode();
    }

public:

    Dijkstra(const Graph &graph): graph(graph) {}

    // CALCULATE OPTIMAL PATH
    vector<u_int> calcOptimalPath(const Node &startNode, const Node &finishNode) {
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
