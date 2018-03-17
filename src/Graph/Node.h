#ifndef CAL_NODE_H
#define CAL_NODE_H

#include "../Utilities/defs.h"
#include "Edge.h"


// Node class, used by graph class
// Every node has its own unique ID, which makes the node Unique and "locatable"
class Node{
protected:
    u_int id;
    double x;
    double y;
    std::string name;
    std::vector< Edge > edges;

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

public:

    // Empty Constructor
    Node();

    // Id Constructor
    Node(u_int id);

    // Construct node with its value
    Node(u_int id, double x, double y, const std::string &name);

    // Returns all the edges in the node
    const std::vector<Edge>& getEdges() const;

    // Add a connection
    bool addNodeConnection(u_int destNodeId, const double & weight);

    // Returns a pair with the Edge value and a boolean that says if the connection with the other node exists or not ;
    // if the boolean is false, value makes no sense
    std::pair<double , bool> getEdgeVal(u_int otherNodeId) const;

    // Returns success / failure (failure is when the connection with the other node does not exist)
    bool setEdgeVal(u_int otherNodeId , const double & newWeight);

    // Returns the node ID
    u_int getId() const;

    // Returns the number of edges in the Node
    u_int getNumEdges() const;
};

#endif //CAL_NODE_H
