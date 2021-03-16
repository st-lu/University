#ifndef TEMA1_GRAF_H
#define TEMA1_GRAF_H

#include <iostream>
#include "nod.h"
#include "lista.h"
using namespace std;
class Graf{
private:
    int nr_muchii;
    int nr_noduri;
    Lista *adiacenta; // lista cu listele de adiacenta

    // in metoda extend, marim capacitatea grafului i.e. alocam mai multa memorie in adiacenta atunci cand adaugam un nou nod la graf
    void extend(int oldsize, int newsize){
        auto *aux = new Lista[newsize+1]; // in aux avem lista de adiacenta extinsa in care o sa copiem adiacenta curenta
        for(int i = 0; i < oldsize; i++){
            int *aux1 = adiacenta[i+1].getlist(); //getlist() intoarce un vector cu nodurile din lista de vecini a lui i+1
            for (int j = 0; j < adiacenta[i+1].length(); ++j) {
                int nod_adiacent = aux1[j];
                aux[i+1].inserare(nod_adiacent);
            }
            delete[] aux1;
        }
        Lista *aux2;
        aux2 = adiacenta; //stergem adiacenta veche si o inlocuim cu cea noua
        adiacenta = aux;
        delete[] aux2;
    }

    //prin metoda check verificam daca nodul y se afla deja in lista de adiacenta a nodului x si in caz afirmativ returnam true
    bool check(int x, int y){
        if(x > nr_noduri)
            return false;
        int *aux = adiacenta[x].getlist(); //parcurgem lista lui x si verificam daca se afla y in ea sau nu
        for (int i = 0; i < adiacenta[x].length(); ++i) {
            if(aux[i] == y)
                return true;
        }
        delete[] aux;
        return false;
    }

public:
    //constructori & destructor
    Graf();
    Graf(int, int*);
    Graf(Graf&);
    ~Graf();

    //metode
    //Graf a;
    // nr_noduri = a.get_noduri();
    int get_noduri() const; //metoda prin care obtine nr de noduri
    int get_muchii() const; //metoda prin care obtinem nr de muchii
    void add(int, int); //metoda prin care adaugam o muchie la graf
    int* bfs(int); //metoda prin care parcurgem in latime pronind de la un nod dat
    int* dfs(int); //metoda prin care parcurgem in lungime pornind de la un nod dat
    int distanta(int, int); //metoda prin care aflam distanta dintre doua noduri
    bool is_tree(); //metoda prin care verificam daca un graf este arbor
    int componente_conexe(); //metoda prin care aflam cate componente conexe are graful


    //operatori
    Graf& operator=(const Graf& g);
    int* operator[](const int nod) const;
    bool operator>(const Graf& g) const;
    bool operator<(const Graf& g) const;
    friend istream&operator>>(istream&, Graf&);
    friend ostream&operator<<(ostream&, Graf&);
};
// Graf a;
Graf::Graf(){
    nr_noduri = nr_muchii = 0;
    adiacenta = nullptr;
}
//Graf a;
// a = ...
// Graf b(a);
inline Graf::Graf(Graf &g){
    this->nr_noduri = g.nr_noduri;
    this->nr_muchii = g.nr_muchii;
    this->adiacenta = new Lista[nr_noduri+1];
    for(int i = 0; i < g.nr_noduri; i++){
        int *aux = g.adiacenta[i+1].getlist();
        for (int j = 0; j < g.adiacenta[i+1].length(); ++j) { //copiem adiacenta lui g in cea a grafului in care se face atribuirea
            int nod_adiacent = aux[j];
            this->adiacenta[i+1].inserare(nod_adiacent);
        }
        delete[] aux;
    }
}
// int v[1000] - lista tati
// int 14
// Graf a(14, v);
inline Graf::Graf(int n, int v[]){
    nr_muchii = 0;
    nr_noduri = 0;
    adiacenta = new Lista[n+1];
    // constructorul cu parametri primeste un vector de tati si ii creeaza graful/arborele corespunzator
    for(int i = 0; i < n; i++){
        if(v[i+1] != 0)
            add(i+1, v[i+1]);
    }
}

inline Graf::~Graf(){
    delete[] adiacenta;
    nr_noduri = 0;
    nr_muchii = 0;
}

#endif //TEMA1_GRAF_H
