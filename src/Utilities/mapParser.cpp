
#include "mapParser.h"
#include <cmath>




Graph parseMap(std::string filePathA, std::string filePathB, std::string filePathC){
    Graph returnGraph = Graph();


    /*
    O programa gera três ficheiros, cujos campos são separados por ";", a seguir descritos:

    Ficheiro A.txt (informação acerca dos nós)
        node_id;latitude_in_degrees;longitude_in_degrees;longitude_in_radians;latitude_in_radians

    Ficheiro B.txt (informação acerca das estradas)
        road_id;road_name;is_two_way{yes/no}

    Ficheiro C.txt (informação acerca das ligações entre os nós, isto é, dita o conjunto de vértices que define a geometria de uma estrada)
        road_id;node1_id;node2_id;
    */

    //Add Nodes
    std::ifstream fileA(filePathA);

    std::map<int, int> idMap; //fileId -> internalGraph id
    if(fileA.is_open()) {
        parseFileA(fileA, returnGraph, idMap);

    }

    fileA.close();

    //Store Edges details in a map
    std::ifstream fileB(filePathA);

    std::map<int, std::pair<std::string, bool> > edgeMap; //edgeId -> <edgeName, isBothWays>
    if(fileB.is_open()) {
        parseFileB(fileB, edgeMap);

    }

    fileB.close();

    //Add edges, complementing information with the one at edgeMap
    std::ifstream fileC(filePathC);

    if(fileC.is_open()) {
        parseFileC(fileC, returnGraph, idMap, edgeMap);

    }

    fileC.close();


}




void parseFileA(std::ifstream & fileA, Graph &graph, std::map<int, int> &idMap) {

    std::string currLine = "";

    int nodeCounter = 0;

    while(!fileA.eof()) {
        getline(fileA, currLine);
        int nodeID = stoi(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        float latRad = stof(currLine.substr(currLine.find_last_of(";") + 1));
        currLine = currLine.substr(0, currLine.find_last_of(";"));

        float longRad = stof(currLine.substr(currLine.find_last_of(";") + 1));

        idMap.insert(std::make_pair(nodeID, nodeCounter));

        double EARTH_RADIUS = 6371000;
        double nodeX = EARTH_RADIUS * longRad * cos(latRad);
        double nodeY = EARTH_RADIUS * latRad;

        std::string nodeName = "node" + std::to_string(nodeCounter);

        graph.addNode(nodeX, nodeY, nodeName);

        nodeCounter++;

    }

}



void parseFileB(std::ifstream &fileB, std::map<int, std::pair<std::string, bool> > &edgeMap) {
    std::string currLine = "";

    while(!fileB.eof()) {
        getline(fileB, currLine);

        int edgeID = stoi(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);
        std::string edgeLabel = (currLine[0] == ';') ?  "" : currLine.substr(0, currLine.find_first_of(";"));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);
        bool isTwoWay = (currLine == "True");

        edgeMap.insert(std::make_pair(edgeID, std::make_pair(edgeLabel, isTwoWay)));


    }
}

void parseFileC(std::ifstream & fileC, Graph graph, const std::map<int, int> & idMap, const std::map<int, std::pair<std::string, bool>>& edgeMap) {
    std::string currLine = "";

    int nodeCounter = 0;

    while(!fileC.eof()) {
        getline(fileC, currLine);
/*
        Ficheiro C.txt (informação acerca das ligações entre os nós, isto é, dita o conjunto de vértices que define a geometria de uma estrada)
        road_id;node1_id;node2_id;
*/

        int edgeID = stoi(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        int originNodeID = stoi(currLine.substr(0, currLine.find_first_of(";")));
        currLine = currLine.substr(currLine.find_first_of(";") + 1);

        int destinationNodeID = stoi(currLine);

        int graphOriginNodeID = idMap.at(originNodeID);
        int graphDestinationNodeID = idMap.at(destinationNodeID);

        double edgeWeight = graph.getNodeById(graphOriginNodeID)
                .getDistanceToOtherNode(graph.getNodeById(graphDestinationNodeID));

        std::string edgeLabel = edgeMap.at(edgeID).first;
        bool edgeIsBothWays = edgeMap.at(edgeID).second;

        //////////////////////////
        //missing label on edges//
        //////////////////////////
        /*
        graph.addEdge(graphOriginNodeID, graphDestinationNodeID, edgeWeight, edgeLabel);

        if(edgeIsBothWays) {
            graph.addEdge(graphDestinationNodeID, graphOriginNodeID, edgeWeight, edgeLabel);
        }
        */


    }
}