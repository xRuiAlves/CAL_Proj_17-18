
#include "mapParser.h"
#include <cmath>

static void parseFileA(std::ifstream & fileA, Graph & graph, std::map<u_long, u_int> & idMap);
static void parseFileB(std::ifstream & fileB, std::map<u_long, std::pair<std::string, bool> > & edgeMap);
static void parseFileC(std::ifstream & fileC, Graph & graph, const std::map<u_long, u_int> & idMap, const std::map<u_long, std::pair<std::string, bool>>& edgeMap);




Graph parseMap(std::string filePathA, std::string filePathB, std::string filePathC){
    Graph returnGraph = Graph();

    //Add Nodes
    std::ifstream fileA(filePathA);
    std::ifstream fileB(filePathB);
    std::ifstream fileC(filePathC);

    if(!fileA.is_open()) {
        throw GraphLoadFailed(filePathA);
    } else if (!fileB.is_open()) {
        throw GraphLoadFailed(filePathB);
    } else if (!fileC.is_open()) {
        throw GraphLoadFailed(filePathC);
    }

    // Store Graph nodes
    std::map<u_long, u_int> idMap; //fileId -> internalGraph id
    parseFileA(fileA, returnGraph, idMap);
    fileA.close();

    //Store Edges details in a map
    std::map<u_long, std::pair<std::string, bool> > edgeMap; //edgeId -> <edgeName, isBothWays>
    parseFileB(fileB, edgeMap);
    fileB.close();

    //Add edges, complementing information with the one at edgeMap
    parseFileC(fileC, returnGraph, idMap, edgeMap);
    fileC.close();

    return returnGraph;
}




static void parseFileA(std::ifstream & fileA, Graph &graph, std::map<u_long, u_int> &idMap) {

    std::string currLine = "";

    u_int nodeCounter = 0;

    while(!fileA.eof()) {
        getline(fileA, currLine);
        u_long nodeID = stoul(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        double latRad = stod(currLine.substr(currLine.find_last_of(";") + 1));
        currLine = currLine.substr(0, currLine.find_last_of(";"));

        double longRad = stod(currLine.substr(currLine.find_last_of(";") + 1));

        idMap.insert(std::make_pair(nodeID, nodeCounter));

        double EARTH_RADIUS = 6371000;
        double nodeX = EARTH_RADIUS * longRad * cos(latRad);
        double nodeY = EARTH_RADIUS * latRad;

        std::string nodeName = "node" + std::to_string(nodeCounter);

        graph.addNode(nodeX, nodeY, nodeName);

        nodeCounter++;

    }

}



static void parseFileB(std::ifstream &fileB, std::map<u_long, std::pair<std::string, bool> > &edgeMap) {
    std::string currLine = "";

    while(!fileB.eof()) {
        getline(fileB, currLine);

        u_long edgeID = stoul(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);
        std::string edgeLabel = (currLine[0] == ';') ?  "" : currLine.substr(0, currLine.find_first_of(";"));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);
        bool isTwoWay = (currLine == "True");

        edgeMap.insert(std::make_pair(edgeID, std::make_pair(edgeLabel, isTwoWay)));


    }
}

static void parseFileC(std::ifstream & fileC, Graph & graph, const std::map<u_long, u_int> & idMap, const std::map<u_long, std::pair<std::string, bool>>& edgeMap) {
    std::string currLine = "";

    while(!fileC.eof()) {
        getline(fileC, currLine);
/*
        Ficheiro C.txt (informação acerca das ligações entre os nós, isto é, dita o conjunto de vértices que define a geometria de uma estrada)
        road_id;node1_id;node2_id;
*/

        u_long edgeID = stoul(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        u_long originNodeID = stoul(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        u_long destinationNodeID = stoul(currLine);

        u_int graphOriginNodeID = idMap.at(originNodeID);
        u_int graphDestinationNodeID = idMap.at(destinationNodeID);

        double edgeWeight = graph.getNodeById(graphOriginNodeID)
                .getDistanceToOtherNode(graph.getNodeById(graphDestinationNodeID));

        std::string edgeLabel = edgeMap.at(edgeID).first;
        bool edgeIsBothWays = edgeMap.at(edgeID).second;

        //////////////////////////
        //missing label on edges//
        //////////////////////////

        graph.addEdge(graphOriginNodeID, graphDestinationNodeID, edgeWeight, edgeLabel);

        if(edgeIsBothWays) {
            graph.addEdge(graphDestinationNodeID, graphOriginNodeID, edgeWeight, edgeLabel);
        }



    }
}