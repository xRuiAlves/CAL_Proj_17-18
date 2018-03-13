//
// Created by reeckset on 10-03-2018.
//

#ifndef CAL_DIJKSTRA_H
#define CAL_DIJKSTRA_H

#include "../Graph/Graph.h"
#include "../Graph/DNode.h"
#include <set>
#include <unordered_set>

using namespace std;


struct DNodeHash {
    bool operator()(const DNode &d1, const DNode &d2) const {
        return d1 == d2;
    }

    int operator()(const DNode &d) const {
        return d.getNodeId();
    }
};

typedef unordered_set<DNode, DNodeHash, DNodeHash> DNodeHashTable;


template<typename N>
class Dijkstra {

    const Graph<N> &graph;
    set<DNode> pQueue;
    DNodeHashTable checkedDNodes;

    //Variables for current calculation
    u_int finishNodeId = UINT_MAX;
    u_int startNodeId = UINT_MAX;
    double solutionTotalCost = DBL_MAX;
    DNode topDNode;
    Node<N> topNode;

    vector<u_int> lastSolution;

    //Sets all queue's elements to the nodes in the graph and then puts the first node on top
    void populateQueue() {
        for (u_int i = 0; i < graph.getNumNodes(); i++) {
            if(i == this->startNodeId){
                pQueue.emplace(i,0);
            }else {
                pQueue.emplace(i);
            }
        }
    }

    //Gets the node in the queue for a specified id
    DNode getDNodeInQueueById(u_int id) {
        for (DNode d : pQueue) {
            if (d.getNodeId() == id) {
                return d;
            }
        }
    }

    void updateDNodeOnQueue(const DNode &currDNode) {

        //check if the current node has been analised (if it has, it will be in checkedDNodes)
        auto dNodeIt = this->checkedDNodes.find(currDNode);
        if (dNodeIt != this->checkedDNodes.end()) { //Exists in checkedDNodes
            if (currDNode.getTotalWeight() < dNodeIt->getTotalWeight()) {
                this->pQueue.erase(*dNodeIt);
                this->pQueue.insert(currDNode);
                return;
            }
        }

        //if it has not been analised and the current path offers a better way, update it on the priority queue
        for (DNode d : pQueue) {
            if (d.getNodeId() == currDNode.getNodeId()) {
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
        u_int currDNodeId = this->finishNodeId;

        while (currDNodeId != UINT_MAX) {
            lastSolution.insert(lastSolution.begin(), currDNodeId);
            currDNodeId = (*(this->checkedDNodes.find(DNode(currDNodeId)))).getLastNodeId();
        }
    }

    //Goes through queue's top node's children and updates them in the queue
    void updateQueue(){
        for (Edge<N> e : this->topNode.edges) {
            DNode currDNode = getDNodeInQueueById(e.destNode->id); //get edge's destination
            currDNode.setTotalWeight(topDNode.getTotalWeight() + e.value); //update node's value
            currDNode.setLastNodeId(topDNode.getNodeId()); //set node's last node id (for path building later)
            updateDNodeOnQueue(currDNode); //
        }
    }

    //Sets values of topNode and topDNode based on the current pQueue
    void updateTopNode(){
        this->topDNode = *(pQueue.begin());
        this->topNode = graph.getNodeById(topDNode.getNodeId());
    }

    //Checks if the node on top of the queue is a dead end
    bool isTopNodeDeadEnd(){
        if (this->topNode.edges.empty() && this->topDNode.getNodeId() != this->finishNodeId) {
            this->pQueue.erase(this->pQueue.begin());
            return true;
        }
        return false;
    }

    //Checks if the optimal solution has been found (if final node is on top of the queue)
    bool foundOptimalSolution(){
        if (this->topDNode.getNodeId() == this->finishNodeId) {
            this->solutionTotalCost = this->pQueue.begin()->getTotalWeight();
            this->checkedDNodes.insert(topDNode);
            return true;
        }
        return false;
    }

    //Checks if a Node Id is valid within the graph
    bool isNodeIdValid(u_int nodeID){
        return (nodeID < graph.getNumNodes());
    }

public:

    Dijkstra(const Graph<N> &graph): graph(graph){}

    //CALCULATE OPTIMAL PATH
    vector<u_int> calcOptimalPath(u_int startNodeId, u_int finishNodeId) {
        if( !(isNodeIdValid(startNodeId) && isNodeIdValid(finishNodeId)) ){
            lastSolution.empty();
            return lastSolution;
        }

        this->finishNodeId = finishNodeId;
        this->startNodeId = startNodeId;
        populateQueue();
        updateTopNode();
        while (!pQueue.empty()) {
            //Analise the node on top of the priority queue

            //Check if node is a dead end
            if(isTopNodeDeadEnd()) {
                continue;
            }

            //Check if already reached the optimal solution (finish node will be on top of the queue)
            if(foundOptimalSolution()) {
                buildPath();    //Fills 'lastSolution' with the computed solution
                return lastSolution;
            }

            //Analise next nodes and updateQueue
            updateQueue();

            //Delete parent from pQueue and put it in the hash table
            pQueue.erase(this->topDNode);
            checkedDNodes.insert(this->topDNode);
            updateTopNode(); //set this->topNode and this->topDNode
        }

        //No solution found, return empty vector
        lastSolution.clear();
        return lastSolution;
    }

    void printSolution(){
        cout << endl;
        if(startNodeId == UINT_MAX){
            cout << "No solution available. Run calcOptimalSolution before printing" << endl;
            return;
        }
        cout << "Dijkstra optimal path between " << this->startNodeId << " and " << this->finishNodeId << endl;
        if(lastSolution.empty()){
            cout << "No path could be calculated. Could not print." << endl;
            return;
        }
        cout << "Successfully generated with a total weight of " << this->checkedDNodes.find(DNode(finishNodeId))->getTotalWeight() << ":" << endl;
        for(u_int nodeID : lastSolution){
            cout << nodeID << " - " << graph.getNodeById(nodeID).data << endl;
        }
    }
};

#endif //CAL_DIJKSTRA_H
