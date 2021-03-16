#ifndef LAB5_DIRECTEDGRAPH_H
#define LAB5_DIRECTEDGRAPH_H

#include <iostream>
#include <vector>
using namespace std;

class directedGraph {
        vector <int> L[10002];
        int noOfNodes;
    public:
        directedGraph(){
            noOfNodes = 0;
        }

        directedGraph(vector<int> L[10001], int noOfNodes){
            this->noOfNodes = noOfNodes;
            this->L[10001] = L[10001];
        }

        directedGraph(directedGraph &Graph){
            this->noOfNodes = Graph.noOfNodes;
            this->L[10001] = Graph.L[10001];
        }

        void addNode(int);
        void addEdge(int, int);
        bool hasEdge(int, int);

        void BFS(int startNode);
        void DFS(int startNode);
        int twoCycles();
};


#endif //LAB5_DIRECTEDGRAPH_H
