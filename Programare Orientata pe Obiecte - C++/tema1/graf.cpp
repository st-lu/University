#include "graf.h"


/// Metode
int Graf::get_noduri(){
    return nr_noduri;
}

int Graf::get_muchii(){
    return nr_muchii;
}

void Graf::add(int x, int y){
    if(nr_noduri < x){
        nr_noduri++;
        extend(nr_noduri);
    }
    adiacenta[x].inserare(y);
    if(nr_noduri < y){
        nr_noduri++;
        extend(nr_noduri);
    }
    adiacenta[y].inserare(x);
    nr_muchii++;
}

int* Graf::bfs(int x){
    bool *v = new bool[nr_noduri+1];
    int *c = new int[nr_noduri];
    int *sol = new int[nr_noduri+1];
    for(int i = 0; i < nr_noduri; i++){
        v[i+1] = false; c[i] = 0; sol[i+1] = 0;
    }
    int p, u;
    p = u = 0;
    int counter = 1;
    c[0] = x;
    v[x] = true;
    sol[1] = x;
    while(p <= u){
        int nod_curent = c[p];
        for(int i = 0; i < adiacenta[nod_curent].length(); i++){
            int nod_vecin = adiacenta[nod_curent].get(i);
            if(!v[nod_vecin]){
                v[nod_vecin] = true;
                c[++u] = nod_vecin;
                sol[++counter] = nod_vecin;
            }
        }
        p++;
    }
    delete[] v;
    delete[] c;
    sol[0] = counter;
    return sol;
}

int* Graf::dfs(int x) {
    bool *v = new bool[nr_noduri+1];
    int *s = new int[nr_noduri];
    int *sol = new int[nr_noduri];
    for(int i = 0; i < nr_noduri; i++){
        v[i+1] = false; s[i] = 0; sol[i+1] = 0;
    }
    int tos = 0;
    int counter = 1;
    s[0] = x;
    v[x] = true;
    sol[1] = x;
    while (tos != -1) {
        int nod_curent = s[tos];
        --tos;
        for (int i = 0; i < adiacenta[nod_curent].length(); ++i) {
            int nod_vecin = adiacenta[nod_curent].get(i);
            if (!v[nod_vecin]) {
                v[nod_vecin] = true;
                s[++tos] = nod_vecin;
                sol[++counter] = nod_vecin;
            }
        }
    }
    delete[] v;
    delete[] s;
    sol[0] = counter;
    return sol;
}

int Graf::distanta(int x, int y){
    int *v = new int[nr_noduri+1];
    int *c = new int[nr_noduri];
    for(int i = 0; i < nr_noduri; i++){
        v[i+1] = 0; c[i] = 0;
    }
    int p, u;
    p = u = 0;
    int counter = 0;
    c[0] = x;
    v[x] = 1;
    while(p <= u){
        int nod_curent = c[p];
        for(int i = 0; i < adiacenta[nod_curent].length(); i++){
            int nod_vecin = adiacenta[nod_curent].get(i);
            if(!v[nod_vecin]){
                v[nod_vecin] = v[nod_curent] + 1;
                c[++u] = nod_vecin;
            }
        }
        p++;
    }
    int sol = v[y];
    delete[] v;
    delete[] c;
    if(sol != 0)
        return sol-1;
    else
        return -1; ///exception?
}

bool Graf::is_tree(){
    if((componente_conexe() != 1) or (nr_muchii != nr_noduri-1))
        return false;
    return true;
}

int Graf::componente_conexe(){
    bool viz[nr_noduri+1];
    for(int i = 0; i < nr_noduri+1; i++){
        viz[i] = false;
    }
    int nr_componente = 0;
    for(int i = 0; i < nr_noduri; i++){
        if(!viz[i+1]) {
            nr_componente++;
            int *v = bfs(i + 1);
            for(int j = 1; j <= v[0]; j++){
                viz[v[j]] = true;
            }
        }
    }
    return nr_componente;
}


/// Operatori friend
istream& operator>>(istream& in, Graf& g){
    int noduri, muchii;
    in >> noduri;
    in >> muchii;
    g.adiacenta = new Lista[noduri+1];
    for (int i = 0; i < muchii; ++i) {
        int x, y;
        in >> x >> y;
        g.add(x, y);
    }
    return in;
}

ostream& operator<<(ostream& out, Graf& g){
    for (int i = 0; i < g.nr_noduri; ++i) {
        out << i + 1 << ": ";
        for (int j = 0; j < g.adiacenta[i+1].length(); ++j) {
            int nodfiu = g.adiacenta[i+1].get(j);
            out << nodfiu << " ";
        }
        out << "\n";
    }

    return out;
}
