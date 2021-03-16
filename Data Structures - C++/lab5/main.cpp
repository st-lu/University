#include <iostream>
#include "directedGraph.h"
using namespace std;

int main() {
    directedGraph Graf;
    Graf.addNode(1); Graf.addNode(2); Graf.addNode(3); Graf.addNode(4); Graf.addNode(5); Graf.addNode(6);
    Graf.addEdge(1, 2); Graf.addEdge(3, 5); Graf.addEdge(1, 3);
    Graf.addEdge(5, 3); Graf.addEdge(6, 1); Graf.addEdge(1, 6);
    Graf.addEdge(2, 4);
    cout << Graf.twoCycles() << "\n";
    Graf.BFS(1); cout << "\n";
    Graf.DFS(1);
    return 0;
}
