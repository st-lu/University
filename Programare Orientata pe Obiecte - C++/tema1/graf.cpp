#include "graf.h"


/// Metode
int Graf::get_noduri(){
    return nr_noduri;
}

int Graf::get_muchii(){
    return nr_muchii;
}

void Graf::add(int x, int y){
    if(adiacenta[x].length() == 0){
        nr_noduri++;

    }
    if(adiacenta[y].length() == 0){
        nr_noduri++;

    }
    adiacenta[x].inserare(y);
    adiacenta[y].inserare(x);
    nr_muchii++;
}

int* Graf::bfs(int x){
    bool v[1000]; int c[1000]; static int sol[1000];
    for(int i = 0; i < 1000; i++){
        v[i] = false; c[0] = 0; sol[0] = 0;
    }
    int p, u;
    p = u = 0;
    int counter = 0;
    c[0] = x;
    v[x] = true;
    sol[0] = x;
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
    return sol;
}

int* Graf::dfs(int x) {
    bool v[1000];
    int s[1000];
    static int sol[1000];
    for (int i = 0; i < 1000; i++) {
        v[i] = false;
        s[0] = 0;
        sol[0] = 0;
    }
    int tos = 0;
    int counter = 0;
    s[0] = x;
    v[x] = true;
    sol[0] = x;
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

    return sol;
}

int Graf::distanta(int x, int y){
    int v[1000]; int c[1000], sol[1000];
    for(int i = 0; i < 1000; i++){
        v[i] = 0; c[0] = 0; sol[0] = 0;
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
                sol[++counter] = nod_vecin;
            }
        }
        p++;
    }
    if(v[y] != 0)
        return v[y];
    else
        return -1; ///exception?
}

bool Graf::is_tree(){
    if((componente_conexe() != 1) or (nr_muchii != nr_noduri-1))
        return false;
    return true;
}

int Graf::componente_conexe(){
    bool viz[1000];
    for(int i = 0; i < 1000; i++){
        viz[i] = false;
    }
    int nr_componente = 0;
    for(int i = 0; i < nr_noduri; i++){
        if(!viz[i+1]) {
            nr_componente++;
            int *v = bfs(i + 1);
            for(int j = 0; v[j] != 0; j++){
                viz[v[j]] = true;
            }
        }
    }
    return nr_componente;
}


/// Operatori friend
istream& operator>>(istream& in, Graf& g){
    int xx, yy;
    in >> xx;
    in >> yy;
    for (int i = 0; i < yy; ++i) {
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
