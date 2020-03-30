#ifndef TEMA1_GRAFFFF_H
#define TEMA1_GRAFFFF_H

#include <iostream>
#include "nodddd.h"
#include "listaaaaa.h"
using namespace std;

class Graf{
    int nr_muchii;
    int nr_noduri;
    Lista *adiacenta;

public:
    //constructori & destructori
    Graf();
    Graf(int, int*);
    Graf(Graf&);
    ~Graf();

    //metode
    int get_noduri();

    int get_muchii(){
        return nr_muchii;
    }

    //mai modifica
    void add(int x, int y){
        if(adiacenta[x].length() == 0)
            nr_noduri++;
        if(adiacenta[y].length() == 0)
            nr_noduri++;
        adiacenta[x].inserare(y);
        adiacenta[y].inserare(x);
        nr_muchii++;
    }


    int* bfs(int x){
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

    int* dfs(int x){
        bool v[1000]; int s[1000];
        static int sol[1000];
        for(int i = 0; i < 1000; i++){
            v[i] = false; s[0] = 0; sol[0] = 0;
        }
        int tos = 0;
        int counter = 0;
        s[0] = x;
        v[x] = true;
        sol[0] = x;
        while(tos != -1) {
            int nod_curent = s[tos];
            --tos;
            for (int i = 0; i < adiacenta[nod_curent].length(); ++i) {
                int nod_vecin = adiacenta[nod_curent].get(i);
                if(!v[nod_vecin]){
                    v[nod_vecin] = true;
                    s[++tos] = nod_vecin;
                    sol[++counter] = nod_vecin;
                }
            }
        }

        return sol;
    }

    int distanta(int x, int y){
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

    bool is_tree(){
        if((componente_conexe() != 1) or (nr_muchii != nr_noduri-1))
            return false;
        return true;
    }

    int componente_conexe(){
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




    //operatori

    Graf& operator=(const Graf& g) {
        this->nr_noduri = g.nr_noduri;
        this->nr_muchii = g.nr_muchii;
        this->adiacenta = new Lista[1000];
        for(int i = 0; i < g.nr_noduri; i++){
            for (int j = 0; j < g.adiacenta[i+1].length(); ++j) {
                int nod_adiacent = g.adiacenta[i+1].get(j);
                this->adiacenta[i+1].inserare(nod_adiacent);
            }
        }
        return *this;
    }

    int* operator[](const int nod) const{
        static int sol[1000];
        for (int i = 0; i < adiacenta[nod].length(); ++i) {
            sol[i] = adiacenta[nod].get(i);
        }
        return sol;
    }

    bool operator>(const Graf& g) const {
        if(this->nr_noduri > g.nr_noduri || (this->nr_muchii > g.nr_muchii && this->nr_noduri == g.nr_noduri))
            return true;
        return false;
    }

    bool operator<(const Graf& g) const{
        if(this->nr_noduri < g.nr_noduri || (this->nr_muchii < g.nr_muchii && this->nr_noduri == g.nr_noduri))
            return true;
        return false;
    }



    //friend
    friend istream&operator>>(istream&, Graf&);
    friend ostream&operator<<(ostream&, Graf&);
};

inline Graf::Graf(){
    nr_noduri = nr_muchii = 0;
    adiacenta = new Lista[1000];
}

inline Graf::Graf(Graf &g){
this->nr_noduri = g.nr_noduri;
this->nr_muchii = g.nr_muchii;
adiacenta = new Lista[1000];
for(int i = 0; i < g.nr_noduri; i++){
this->adiacenta[i+1] = g.adiacenta[i+1];
}
}

inline Graf::Graf(int n, int v[]){
    nr_muchii = n-1;
    nr_noduri = n;
    adiacenta = new Lista[1000];
    // constructorul cu parametri primeste un vector de tati si ii creeaza graful corespunzator
    for(int i = 0; i < n; i++){
        if(v[i] != 0)
            add(i,v[i]);
    }
}

inline Graf::~Graf(){
    delete[] adiacenta;
    nr_noduri = 0;
    nr_muchii = 0;
}

#endif //TEMA1_GRAFFFF_H
