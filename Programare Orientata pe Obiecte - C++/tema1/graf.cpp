#include "graf.h"


/// Metode
int Graf::get_noduri() const{
    return nr_noduri;
}

int Graf::get_muchii() const{
    return nr_muchii;
}

void Graf::add(int x, int y){
    if(nr_noduri < max(x,y)){ //daca nr de noduri este mai mic decat x sau y, atunci trebuie sa extindem lista de adiacenta pana la valoarea mai mare
        extend(nr_noduri, max(x,y));
        nr_noduri = max(x,y);
    }
    adiacenta[x].inserare(y); // il adaugam pe y la lista de adiacenta a lui x;
    adiacenta[y].inserare(x); //graful este neorientat deci il inseram si pe y in lista lui x
    nr_muchii++;
}

int* Graf::bfs(int x){
    bool *v = new bool[nr_noduri+1]; //tinem un vector de vizitati
    int *c = new int[nr_noduri]; //tinem o coada
    int *sol = new int[nr_noduri+1]; //tinem un vector de solutii
    for(int i = 0; i < nr_noduri; i++){
        v[i+1] = false; c[i] = 0; sol[i+1] = 0; //initializari
    }
    int p, u; //capetele cozii
    p = u = 0;
    int counter = 1; //size-ul solutiei
    c[0] = x;
    v[x] = true;
    sol[1] = x; //am indexat solutia de la 1 pentru ca pe poz 0 o sa am size
    while(p <= u){
        int nod_curent = c[p]; //nodul curent va fi primul din coada
        int *aux = adiacenta[nod_curent].getlist(); //ii aflam lista de vecini
        for(int i = 0; i < adiacenta[nod_curent].length(); i++){ //vizitam fiecare vecin si il punem in coada daca nu era deja vizitat
            int nod_vecin = aux[i];
            if(!v[nod_vecin]){
                v[nod_vecin] = true;
                c[++u] = nod_vecin;
                sol[++counter] = nod_vecin;
            }
        }
        delete[] aux;
        p++; //eliminam din coada nodul curent
    }
    delete[] v;
    delete[] c;
    sol[0] = counter;
    return sol;
}

int* Graf::dfs(int x) {
    bool *v = new bool[nr_noduri+1];
    int *s = new int[nr_noduri]; //tinem o stiva
    int *sol = new int[nr_noduri];
    for(int i = 0; i < nr_noduri; i++){
        v[i+1] = false; s[i] = 0; sol[i+1] = 0; //idem bfs pana aici
    }
    int tos = 0; //tinem un top of stack
    int counter = 1;
    s[0] = x;
    v[x] = true;
    sol[1] = x;
    while (tos != -1) {
        int nod_curent = s[tos];
        --tos; //eliminam din stiva nodul curent
        int *aux = adiacenta[nod_curent].getlist();
        for (int i = 0; i < adiacenta[nod_curent].length(); ++i) { //idem bfs
            int nod_vecin = aux[i];
            if (!v[nod_vecin]) {
                v[nod_vecin] = true;
                s[++tos] = nod_vecin;
                sol[++counter] = nod_vecin;
            }
        }
        delete[] aux;
    }
    delete[] v;
    delete[] s;
    sol[0] = counter;
    return sol;
}

int Graf::distanta(int x, int y){ //ca sa aflam distanta de la x la y facem un bfs pronind din nodul x ca sa ajungem pe drumul cel mai scurt la y si numaram "nivelele"
                                  // i.e. numaram prin cate alte noduri am trecut ca sa ajungem de la x la y
                                  // avand in vedere ca este un bfs mai tweaked in care a trebuit sa modific putin vectorul de vizitati ca sa retina la ce distanta
                                  // se afla nodul k fata de x, am rescris tot algoritmul in loc sa apelez metoda bfs()
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
        int *aux = adiacenta[nod_curent].getlist();
        for(int i = 0; i < adiacenta[nod_curent].length(); i++){
            int nod_vecin = aux[i];
            if(!v[nod_vecin]){
                v[nod_vecin] = v[nod_curent] + 1; //nod_vecin se afla pe nivelul urmator tatalui lui(nod_curent)
                c[++u] = nod_vecin;
            }

            if(nod_vecin == y) { //daca am gasit nodul y iesim din bfs
                u = p;
                break;
            }
        }
        delete[] aux;
        p++;
    }
    int sol = v[y]; //distanta de la x la y se va afla in v[y]
    delete[] v;
    delete[] c;
    if(sol != 0)
        return sol-1; //punem 1 in v[x] ca sa il marcam ca vizitat. acest 1 trebuie scazut la final
                      //totodata am gandit solutia asa: functia returneaza 0 daca ii dam drum de la x la el insusi
                      //                                                   1 daca ii dam drum de la x la un fiu direct
                      //                                                   2 drum de la x la un fiu al fiului etc.
    else
        return -1; //daca nu putem ajunge de la x la y i.e. sunt in componente conexe diferite, atunci returnam -1
}

bool Graf::is_tree(){
    if((componente_conexe() != 1) or (nr_muchii != nr_noduri-1))
        return false;
    return true; //un graf este arbore daca are o singura componenta conexa iar nr_muchii == nr_noduri-1
}

int Graf::componente_conexe(){
    bool *viz = new bool[nr_noduri+1];
    for(int i = 0; i < nr_noduri+1; i++){
        viz[i] = false;
    }
    int nr_componente = 0;
    for(int i = 0; i < nr_noduri; i++){
        if(!viz[i+1]) { // intram intr-un nod, facem bfs sa aflam toate celelalte noduri in care putem ajunge din nodul curent
            nr_componente++; //marim nr de comp conexe
            int *v = bfs(i + 1);
            for(int j = 1; j <= v[0]; j++){
                viz[v[j]] = true; //marcam nodurile in care se poate ajunge din nodul curent caci ele formeaza o comp conexa
            }
        }
    }
    delete[] viz;
    return nr_componente;
}


/// Operatori

Graf& Graf::operator=(const Graf& g) {
    if(this == &g){
        return *this;
    }
    this->nr_noduri = g.nr_noduri; //actualizam nr noduri/muchii
    this->nr_muchii = g.nr_muchii;
    auto *aux1 = this->adiacenta;
    this->adiacenta = new Lista[nr_noduri+1]; // stergem adiacenta veche si facem una noua
    delete[] aux1;
    for(int i = 0; i < g.nr_noduri; i++){
        int *aux = g.adiacenta[i+1].getlist();
        for (int j = 0; j < g.adiacenta[i+1].length(); ++j) { //copiem adiacenta lui g in cea a grafului in care se face atribuirea
            int nod_adiacent = aux[j];
            this->adiacenta[i+1].inserare(nod_adiacent);
        }
        delete[] aux;
    }
    return *this;
}

int* Graf::operator[](const int nod) const{
    int *sol = new int[adiacenta[nod].length()+1];
    sol[0] = adiacenta[nod].length();
    int *aux = adiacenta[nod].getlist(); //motivul pt care nu returnez direct aux este ca vreau sa pun size-ul listei pe pozitia 0
    for (int i = 0; i < adiacenta[nod].length(); ++i) { //copiez aux in sol
        sol[i+1] = aux[i];
    }
    delete[] aux;
    return sol;
}

bool Graf::operator>(const Graf& g) const {
    if(this->nr_noduri > g.nr_noduri || (this->nr_muchii > g.nr_muchii && this->nr_noduri == g.nr_noduri))
        return true;
    return false;
}

bool Graf::operator<(const Graf& g) const{
    if(this->nr_noduri < g.nr_noduri || (this->nr_muchii < g.nr_muchii && this->nr_noduri == g.nr_noduri))
        return true;
    return false;
}

istream& operator>>(istream& in, Graf& g){
    int noduri, muchii;
    in >> noduri;
    in >> muchii;
    g.nr_muchii = 0; //pornim cu graful de la 0
    g.nr_noduri = 0;
    auto *aux = g.adiacenta;
    g.adiacenta = new Lista[noduri+1]; //stergem lista veche daca exista sa facem una noua
    delete[] aux;
    for (int i = 0; i < muchii; ++i) {
        int x, y;
        in >> x >> y;
        g.add(x, y);
    }
    return in;
}

ostream& operator<<(ostream& out, Graf& g){
    //formatul out va fi:
    //nodk: nodvecink1, nodvecink2,... endl
    for (int i = 0; i < g.nr_noduri; ++i) {
        out << i + 1 << ": ";
        int *aux = g.adiacenta[i+1].getlist();
        for (int j = 0; j < g.adiacenta[i+1].length(); ++j) {
            int nodfiu = aux[j];
            out << nodfiu << " ";
        }
        delete[] aux;
        out << "\n";
    }

    return out;
}
