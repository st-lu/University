#ifndef TEMA1_GRAFFFF_H
#define TEMA1_GRAFFFF_H

#include <iostream>
#include "nod.h"
#include "lista.h"
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
    int get_muchii();
    void add(int, int); //mai modifica
    int* bfs(int);
    int* dfs(int);
    int distanta(int, int);
    bool is_tree();
    int componente_conexe();


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
