#include <iostream>
#include <fstream>
#include <assert.h>
#include "graf.h"
using namespace std;

int main(){
    ifstream fin("graf.in");
    ofstream fout("graf.out");
    Graf graf, gcopy;
    fin>>graf;
    Graf gcopy1(graf);
    gcopy = graf;
    for(int i = 1; i<= graf.get_noduri(); i++){
        for(int j = 1; j <= graf[i][0]; j++){
            assert(graf[i][j] == gcopy[i][j] && graf[i][j] == gcopy1[i][j]);
        }
    }
    int componente = graf.componente_conexe();
    assert(componente == 2);
    graf.add(6, 7);
    graf.add(1, 3);
    assert((graf.get_noduri() == 7) && (graf.get_muchii() == 7) && (graf[1][2] == 3) && (graf[3][3] == 1) && (graf[6][2] == 7) && (graf[7][2] == 6));
    bool ok = graf < gcopy;
    assert(!ok);
    bool ok2 = graf > gcopy;
    assert(ok2);
    int noduri = gcopy.get_noduri();
    assert(noduri == 7);
    int muchii = gcopy.get_muchii();
    assert(muchii == 5);
    int*v = graf[1];
    assert((v[0] == 2) && (v[1] == 2) && (v[2] == 3));
    int*df = graf.dfs(1);
    assert((df[1] == 1) && (df[2] == 2) && (df[3] == 3) && (df[4] == 4) && (df[5] == 5) && (df[6] == 6) && (df[7] == 7) && (df[0] == 7));
    int*bf = graf.bfs(1);
    assert((bf[0] == 7) && (bf[1] == 1) && (bf[2] == 2) && (bf[3] == 3) && (bf[4] == 4) && (bf[5] == 5) && (bf[6] == 7) && (bf[7] == 6));
    int dist = graf.distanta(1,5);
    assert(dist == 2);
    gcopy.add(1,3);
    bool tree = gcopy.is_tree();
    assert(tree);
    int vec[] = {0, 0, 1, 1, 3, 3, 5, 4};
    Graf g(7, vec);
    assert(g.is_tree());
    fout<<graf;
    return 0;
}