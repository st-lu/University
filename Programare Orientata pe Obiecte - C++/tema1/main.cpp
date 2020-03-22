#include <iostream>

class Nod{
    int info;
    Nod *next;
public:
    Nod(){
        info = 0;
        next = nullptr;
    }
    Nod(int x, Nod *n){
        info = x;
        next = n;
    }
    Nod(Nod &p){
        info = p.info;
        next = p.next;
    }
    void setInfo(int x){
        info = x;
    }
    int getInfo(){
        return info;
    }
    void setNext(Nod *n){
        next = n;
    }
    Nod* getNext(){
        return next;
    }
};

class Lista {
    Nod *start;
    Nod *end;
    unsigned int size;
public:
    Lista() {
        size = 0;
        start = end = nullptr;
    }

    void inserare(int x) {
        if (size == 0) {
            start = end = new Nod(x, nullptr);
            size = 1;
        } else {
            end->setNext(new Nod(x, nullptr));
            size++;
            end = end->getNext();
        }
    }

    Lista(int x, int y) {
        size = 0;
        start = end = nullptr;
        for (int i = 0; i < x; i++) {
            inserare(y);
        }
    }

    Lista(Lista &l) {
        size = 0;
        start = end = nullptr;
        for (int i = 0; i < l.length() - 1; i++) {
            inserare(l.get(i));
        }
    }

    int get(int i) {
        if (i > size)
            return INT_MAX;
        Nod *q = start;
        int j = 0;
        while (j < i) {
            q = q->getNext();
            j++;
        }
        return q->getInfo();
    }

    unsigned int length() {
        return size;
    }

    ~Lista() {
        Nod *q = start;
        while (q != nullptr) {
            Nod *p = q->getNext();
            delete q;
            q = p;
        }
    }
};

class Graf{
    int nr_muchii;
    int nr_noduri;
    Lista *adiacenta;
public:
    Graf(){
        nr_noduri = nr_muchii = 0;
        adiacenta = new Lista[1000];
    }

    Graf(Graf &g){
        this->nr_noduri = g.nr_noduri;
        this->nr_muchii = g.nr_muchii;
        adiacenta = new Lista[1000];
        for(int i = 0; i < g.nr_noduri; i++){
            this->adiacenta[i] = g.adiacenta[i];
        }
    }

    Graf(int n, int v[]){
        nr_muchii = n-1;
        nr_noduri = n;
        adiacenta = new Lista[1000];
        // constructorul cu parametri primeste un vector de tati si ii creeaza graful corespunzator
        for(int i = 0; i < n; i++){
            if(v[i] != 0)
                add(i,v[i]);
        }
    }

    int get_noduri(){
        return nr_noduri;
    }

    int get_muchii(){
        return nr_muchii;
    }

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
        bool v[1000]; int c[1000], sol[1000];
        for(int i = 0; i < 1000; i++){
            v[i] = false; c[0] = 0; sol[0] = 0;
        }
        int p, u;
        p = u = 0;
        int counter = 0;
        c[0] = x;
        v[x] = true;
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
        bool v[1000]; int s[1000], sol[1000];
        for(int i = 0; i < 1000; i++){
            v[i] = false; s[0] = 0; sol[0] = 0;
        }
        int tos = 0;
        int counter = 0;
        s[0] = x;
        v[x] = true;

        while(tos != -1) {
            int nod_curent = s[tos];
            for (int i = 0; i < adiacenta[nod_curent].length(); ++i) {
                int nod_vecin = adiacenta[nod_curent].get(i);
                if(!v[nod_vecin]){
                    v[nod_vecin] = true;
                    s[++tos] = nod_vecin;
                    sol[++counter] = nod_vecin;
                }
            }
            --tos;
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
                    v[nod_vecin] = v[nod_vecin] + 1;
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
            if(!viz[i]) {
                nr_componente++;
                int *v = bfs(i + 1);
                for(int j = 0; v[j] != 0; j++){
                    viz[v[j]] = true;
                }
            }
        }
        return nr_componente;
    }


};


int main(){
    return 0;
}