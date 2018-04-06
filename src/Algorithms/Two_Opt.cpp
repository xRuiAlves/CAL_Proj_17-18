//
// Created by rui on 06-04-2018.
//

#include "Two_Opt.h"

Two_Opt::Two_Opt(const Graph & graph) : graph(graph), dfs(graph), astar(graph) { }

// Performs 'numIterations' iterations in attempt to improve current solution (stops if no improvement found)
vector<u_int> Two_Opt::performImprovement(vector<u_int> visitOrder, double visitOrderWeight, u_int numIterations) {
    double bestWeight = visitOrderWeight;
    vector<u_int> bestVisitOrder = visitOrder;

    u_int startNodeId = visitOrder.at(0);
    u_int finishNodeId = visitOrder.at(visitOrder.size()-1);

    // Start and Finish node can't be included, since they have fixed positions in the visit order
    u_int numNodesForSwap = visitOrder.size() - 2;
    u_int t = 0;

    double lastBestWeight = -1;
    while (true) {
        start_again:

        // Check if no improvement was made ; if so, stop
        if (t == numIterations  ||  lastBestWeight == bestWeight) {
            break;
        }

        lastBestWeight = bestWeight;

        for (u_int i=1 ; i<=numNodesForSwap-1 ; i++){
            for (u_int k=i+1 ; k<=numNodesForSwap ; k++) {
                visitOrder = twoOptSwap(bestVisitOrder, i, k);

                if (!isVisitOrderValid(visitOrder)) {
                    continue;
                }

                visitOrderWeight = calcPathWeight(visitOrder);

                if (visitOrderWeight < bestWeight) {
                    bestVisitOrder = visitOrder;
                    bestWeight = visitOrderWeight;
                    t++;
                    goto start_again;
                }
            }
        }
    }

    return bestVisitOrder;
}

// Performs  iterations in attempt to improve current solution until no improvement is found
vector<u_int> Two_Opt::performImprovement(vector<u_int> visitOrder, double visitOrderWeight) {
    double bestWeight = visitOrderWeight;
    vector<u_int> bestVisitOrder = visitOrder;

    u_int startNodeId = visitOrder.at(0);
    u_int finishNodeId = visitOrder.at(visitOrder.size()-1);

    // Start and Finish node can't be included, since they have fixed positions in the visit order
    u_int numNodesForSwap = visitOrder.size() - 2;

    double lastBestWeight = -1;

    // Repeat until no improvement
    while (lastBestWeight != bestWeight) {

        lastBestWeight = bestWeight;

        for (u_int i=1 ; i<=numNodesForSwap-1 ; i++){
            for (u_int k=i+1 ; k<=numNodesForSwap ; k++) {
                visitOrder = twoOptSwap(bestVisitOrder, i, k);

                if (!isVisitOrderValid(visitOrder)) {
                    continue;
                }

                visitOrderWeight = calcPathWeight(visitOrder);

                if (visitOrderWeight < bestWeight) {
                    bestVisitOrder = visitOrder;
                    bestWeight = visitOrderWeight;
                }
            }
        }
    }

    return bestVisitOrder;
}

vector<u_int> Two_Opt::twoOptSwap(vector<u_int> visitOrder, u_int i, u_int k) const {
    // Swap the vector elements between the range [i,k]
    while (i<k) {
        visitOrder.at(i) ^= visitOrder.at(k);
        visitOrder.at(k) ^= visitOrder.at(i);
        visitOrder.at(i) ^= visitOrder.at(k);
        i++;
        k--;
    }

    return visitOrder;
}

bool Two_Opt::isVisitOrderValid(const vector<u_int> & visitOrder) {
    for (u_int i=0 ; i<visitOrder.size()-1 ; i++) {
        if (!dfs.isPathPossible(visitOrder.at(i), visitOrder.at(i+1))) {
            return false;
        }
    }

    return true;
}

double Two_Opt::calcPathWeight(const vector<u_int> & visitOrder) {
    double pathWeight = 0;

    for (u_int i=0 ; i<visitOrder.size()-1 ; i++){
        astar.calcOptimalPath(visitOrder.at(i), visitOrder.at(i+1));
        pathWeight += astar.getSolutionWeight();
    }

    return pathWeight;
}

vector<u_int> Two_Opt::buildSolution(const vector<u_int> & visitOrder, double & solutionWeight) {
    solutionWeight = 0;
    vector<u_int> solution;

    for (u_int i=0 ; i<visitOrder.size()-1 ; i++) {
        append_vector(solution,
                      astar.calcOptimalPath(visitOrder.at(i), visitOrder.at(i+1)));

        solutionWeight += astar.getSolutionWeight();

        if (i != visitOrder.size() - 2) {
            solution.pop_back();
        }
    }

    return solution;
}

void Two_Opt::append_vector(vector<u_int> & v1, const vector<u_int> & v2) {
    for (u_int i : v2){
        v1.push_back(i);
    }
}