#include "directedGraph.h"

void directedGraph::addNode(int x) {
    noOfNodes++;
}

void directedGraph::addEdge(int x, int y) {
    L[x].push_back(y);
}

bool directedGraph::hasEdge(int x, int y) {
    for(auto i : L[x]){
        if(i == y)
            return true;
    }
    return false;
}

void directedGraph::BFS(int x){
    bool viz[10005] = {false};
    int q[10005] = {0};
    int l = 1; int r = 1;
    viz[x] = true;
    q[1] = x; cout << x << " ";
    while(l <= r){
        int crtNode = l;
        for(auto neighborNode : L[crtNode]){
            if(!viz[neighborNode]){
                viz[neighborNode] = true;
                q[++r] = neighborNode;
                cout << neighborNode << " ";
            }
        }
        ++l;
    }
}

bool viz[10001] = {false};
void directedGraph::DFS(int x){
    cout << x << " ";
    viz[x] = true;
    for(auto neighborNode : L[x]){
        if(!viz[neighborNode])
            DFS(neighborNode);
    }

}

int directedGraph::twoCycles() {
    int cycles = 0;
    for (int x = 1; x <= noOfNodes ; ++x) { //pt fiecare nod x
        for(auto y : L[x]){ //iau vecinii lui
            for(auto z : L[y]){ //iar in lista vecinilor lui il caut pe x
                if(z == x)
                    ++cycles;
            }
        }
    }
    return cycles / 2;
}