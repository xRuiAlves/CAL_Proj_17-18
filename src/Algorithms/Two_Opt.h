#ifndef CAL_TWO_OPT_H
#define CAL_TWO_OPT_H

#include "../Graph/Graph.h"
#include "../Graph/Graph.h"
#include "../Utilities/defs.h"
#include "../Utilities/exceptions.h"
#include "DFS.h"
#include "AStar.h"

using namespace std;


class Two_Opt {
private:
    // Data Structures
    const Graph &graph;
    DFS dfs;        // To verify nodes accessibility within the graph
    AStar astar;    // To calculate paths size within the graph


    // Performs a 2-opt swap in the visitOrder vector, using the 'i' and 'k' indexes as reference
    vector<u_int> twoOptSwap(vector<u_int> visitOrder, u_int i, u_int k) const;

    // Verifies if the visit order is valid
    bool isVisitOrderValid(const vector<u_int> & visitOrder);

    // Calculates the weight of the path through the nodes in visitOrder
    double calcPathWeight(const vector<u_int> & visitOrder);

    // Appends two vectors
    void append_vector(vector<u_int> & v1, const vector<u_int> & v2);

public:
    Two_Opt(const Graph & graph);

    // Performs 'numIterations' iterations in attempt to improve current solution (stops if no improvement found)
    vector<u_int> performImprovement(vector<u_int> visitOrder, double visitOrderWeight, u_int numIterations);

    // Performs  iterations in attempt to improve current solution until no improvement is found
    vector<u_int> performImprovement(vector<u_int> visitOrder, double visitOrderWeight);

    // Builds the path by performing A-Star algorithm between the nodes in the visitOrder, in the correct order
    vector<u_int> buildSolution(const vector<u_int> & visitOrder, double & solutionWeight);
};


#endif //CAL_TWO_OPT_H
