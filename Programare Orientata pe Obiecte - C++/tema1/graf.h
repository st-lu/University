#ifndef TEMA1_GRAF_H
#define TEMA1_GRAF_H

#include <iostream>
#include "nod.h"
#include "lista.h"
using namespace std;

class Graf{
    int nr_muchii;
    int nr_noduri;
    Lista *adiacenta;
    void extend(int size){
        auto *aux = new Lista[size+1];
        for(int i = 0; i < size-1; i++){
            unsigned int dim = adiacenta[i+1].length();
            for (int j = 0; j < adiacenta[i+1].length(); ++j) {
                int nod_adiacent = adiacenta[i+1].get(j);
                aux[i+1].inserare(nod_adiacent);
            }
        }
        auto *aux2 = new Lista[size+1];
        aux2 = adiacenta;
        adiacenta = aux;
        delete[] aux2;
    }
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
        this->adiacenta = new Lista[nr_noduri+1];
        for(int i = 0; i < g.nr_noduri; i++){
            for (int j = 0; j < g.adiacenta[i+1].length(); ++j) {
                int nod_adiacent = g.adiacenta[i+1].get(j);
                this->adiacenta[i+1].inserare(nod_adiacent);
            }
        }
        return *this;
    }

    int* operator[](const int nod) const{
        int *sol = new int[adiacenta[nod].length()+1];
        sol[0] = adiacenta[nod].length();
        for (int i = 0; i < adiacenta[nod].length(); ++i) {
            sol[i+1] = adiacenta[nod].get(i);
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
    adiacenta = new Lista[nr_noduri+1];
}

inline Graf::Graf(Graf &g){
    this->nr_noduri = g.nr_noduri;
    this->nr_muchii = g.nr_muchii;
    adiacenta = new Lista[nr_noduri+1];
    for(int i = 0; i < g.nr_noduri; i++){
        this->adiacenta[i+1] = g.adiacenta[i+1];
    }
}

inline Graf::Graf(int n, int v[]){
    nr_muchii = n-1;
    nr_noduri = n;
    adiacenta = new Lista[nr_noduri+1];
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

#endif //TEMA1_GRAF_H
