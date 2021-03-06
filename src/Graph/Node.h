#ifndef CAL_NODE_H
#define CAL_NODE_H

#include "../Utilities/defs.h"
#include "Edge.h"
#include <cmath>
#include <unordered_set>

using namespace std;

// Node class, used by graph class
// Every node has its own unique ID, which makes the node Unique and "locatable"
class Node{
private:
    // Gets the connection with the Node (with id) passed in as parameter index , -1 if not found
    int getConnectionIndex(u_int destNodeId) const{
        // Search for the connection
        for (int i=0 ; i<edges.size() ; i++){
            if (edges.at(i).destNodeId == destNodeId){
                return i;
            }
        }

        // Connection not found
        return -1;
    }

protected:
    u_int id;
    double x;
    double y;
    string name;
    std::vector< Edge > edges;

public:

    // Empty Constructor
    Node();

    // Id Constructor
    Node(u_int id);

    // Construct node with its value
    Node(u_int id, double x, double y, const std::string &name);

    // Returns node x position
    double getX() const;

    // Returns node y position
    double getY() const;

    // Returns node string identifier
    string getName() const;

    // Returns all the edges in the node
    const std::vector<Edge>& getEdges() const;

    // Add a connection
    bool addNodeConnection(u_int destNodeId, const double & weight, const std::string & name);

    // Get Euclidian Distance to other node
    double getDistanceToOtherNode(const Node & otherNode) const;

    // Returns a pair with the Edge value and a boolean that says if the connection with the other node exists or not ;
    // if the boolean is false, value makes no sense
    std::pair<double , bool> getEdgeVal(u_int otherNodeId) const;

    // Returns the node ID
    u_int getId() const;

    // Returns the number of edges in the Node
    u_int getNumEdges() const;

    // Verifies if the node has no edge connections starting in itself
    bool isDeadEnd() const;

    // Node equality Operator
    bool operator==(const Node & other) const;
};



/////////////////////////////////////
//////     NODE HASH TABLE     //////
/////////////////////////////////////

struct NodeHash {
    bool operator()(const Node &d1, const Node &d2) const {
        return d1.getId() == d2.getId();
    }

    int operator()(const Node &d) const {
        return d.getId();
    }
};

typedef std::unordered_set<Node, NodeHash, NodeHash> NodeHashTable;


#endif //CAL_NODE_H
