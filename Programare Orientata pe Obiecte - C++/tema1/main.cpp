#include <iostream>
#include <fstream>
#include "graf.h"
using namespace std;

int main(){
    ifstream fin("graf.in");
    ofstream fout("graf.out");
    Graf graf;
    fin>>graf;
    Graf gcopy;
    gcopy = graf;
    int componente = graf.componente_conexe();
    int*v = graf[3];
    graf.add(6, 7);
    bool ok = graf < gcopy;
    bool ok2 = graf > gcopy;
    graf.add(1,3);
    int noduri = gcopy.get_noduri();
    int muchii = gcopy.get_muchii();
    v = graf[1];
    int*df = graf.dfs(1);
    int nod;
    for (int i = 0; i < graf.get_noduri(); ++i) {
        nod = df[i];
    }
    int dist = graf.distanta(1,5);
    gcopy.add(1,3);
    bool tree = gcopy.is_tree();
    fout<<graf;
    return 0;
}