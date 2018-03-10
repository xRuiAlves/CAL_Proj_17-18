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



struct DNodeHash{
    bool operator()(const DNode &d1,const DNode &d2) const{
        return d1 == d2;
    }

    int operator()(const DNode &d) const{
        return d.getNodeId();
    }
};

typedef unordered_set<DNode, DNodeHash, DNodeHash> DNodeHashTable;

template <typename N>
void populateQueue(const Graph<N> &graph, set<DNode> &pQueue){
    for(u_int i = 0; i < graph.getNumNodes(); i++){
        pQueue.emplace(i);
    }
}

void setStartDNode(set<DNode> &pQueue, u_int startNodeId){
    for(DNode d : pQueue){
        if(d.getNodeId() == startNodeId){
            DNode d2 = d;
            pQueue.erase(d);
            d2.setTotalWeight(0);
            pQueue.insert(d2);
            return;
        }
    }
}

DNode getDNodeById(set<DNode> &pQueue, u_int id){
    for(DNode d : pQueue){
        if(d.getNodeId() == id){
            return d;
        }
    }
}

void updateQueue(set<DNode> &pQueue, const DNode &currDNode, DNodeHashTable &checkedDNodes){

    auto dNodeIt = checkedDNodes.find(currDNode);
    if(dNodeIt != checkedDNodes.end()){ //Exists in checkedDNodes
        if(currDNode.getTotalWeight() < dNodeIt->getTotalWeight()){
            pQueue.erase(*dNodeIt);
            pQueue.insert(currDNode);
            return;
        }
    }

    for(DNode d : pQueue){
        if(d.getNodeId() == currDNode.getNodeId()){
            if(currDNode.getTotalWeight() < d.getTotalWeight()){
                pQueue.erase(d);
                pQueue.insert(currDNode);
                return;
            }
        }
    }
}

template <typename N>
vector<Node<N> > buildPath(const Graph<N> &graph, DNode &finalDNode, DNodeHashTable &checkedDNodes){
    vector<Node<N> > result;
    DNode currDNode = finalDNode;
    while (true){
        result.insert(result.begin(), graph.getNodeById(currDNode.getNodeId()));
        currDNode = *(checkedDNodes.find(DNode(currDNode.getLastNodeId())));
        
        if(currDNode.getLastNodeId() == UINT_MAX){
            result.insert(result.begin(), graph.getNodeById(currDNode.getNodeId()));
            break;
        }
    }

    return result;
}

template <typename N>
vector<Node<N> > Dijkstra(const Graph<N> &graph, u_int startNodeId, u_int finishNodeId){
    set<DNode> pQueue;
    DNodeHashTable checkedDNodes;
    populateQueue(graph,pQueue);
    setStartDNode(pQueue, startNodeId);
    while(!pQueue.empty()){
        DNode topDNode = *(pQueue.begin());
        Node<N> topNode = graph.getNodeById(topDNode.getNodeId());

        if(topNode.edges.empty() && topDNode.getNodeId() != finishNodeId){
            pQueue.erase(pQueue.begin());
            continue;
        }

        if(topDNode.getNodeId() == finishNodeId){
            cout << "FOUND FINISH WITH DISTANCE " << pQueue.begin()->getTotalWeight() << endl;
            return buildPath(graph, topDNode, checkedDNodes);
        }

        for(Edge<N> e : topNode.edges){
            DNode currDNode = getDNodeById(pQueue, e.destNode->id);
            currDNode.setTotalWeight(topDNode.getTotalWeight() + e.value);
            currDNode.setLastNodeId(topDNode.getNodeId());
            updateQueue(pQueue, currDNode, checkedDNodes);
        }

        //Delete parent from pQueue and put it in the hash table
        pQueue.erase(topDNode);
        checkedDNodes.insert(topDNode);
    }
}

#endif //CAL_DIJKSTRA_H
