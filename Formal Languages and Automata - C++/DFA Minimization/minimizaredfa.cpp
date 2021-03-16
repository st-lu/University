#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;

class DFA{
    set<int> Q, F;
    set<char> Sigma;
    int q0;
    map<pair<int, char>, int> delta;

public:
    DFA() { this->q0 = 0;}
    DFA(set<int> Q, set<char> Sigma, map<pair<int, char>, int> delta, int q0, set<int> F){
        this->Q = Q;
        this->Sigma = Sigma;
        this->delta = delta;
        this->q0 = q0;
        this->F = F;
    }

    set<int> getQ() const { return this->Q; }
    set<int> getF() const { return this->F; }
    set<char> getSigma() const { return this->Sigma; }
    int getInitialState() const { return this->q0; }
    map<pair<int, char>, int> getDelta() const { return this->delta; }

    friend istream& operator >> (istream&, DFA&);
    friend ostream& operator << (ostream&, DFA&);
    int minimize();
};

int DFA::minimize(){
    ///partitionarea
    set<int> L[1000]; //lista de partitii
    int partition[1001] = {0}; // in partition[stare] retinem partitia in care se afla starea
    for(auto i : Q){ //luam starile din Q si le impartim in doua partitii: partitia 0 este partitia starilor finale, partitia 1 este partitia starilor nefinale
        if(F.find(i) != F.end()){
            L[0].insert(i); //adaugam starile finale in partitia 0
            partition[i] = 0;
        } else{
            L[1].insert(i); //adaugam starile nefinale in partitia 1
            partition[i] = 1;
        }
    }
    int NoP = 2; //Number of Partitions
    bool ok = true;
    while(ok){
        ok = false; // daca nu se produce nicio modificare i.e. ok ramane false la finalul operatiilor efectuate mai jos, atunci nu mai continuam algoritmul de partitionare
        int initNoP = NoP;
        for (int i = 0; i < initNoP; ++i) { //partitia curenta = L[i]
            for(auto ch : Sigma){ //caracterul curent = ch. separam starile in functie de partitiile in care se duc cu caracterul ch
                pair<int,int> v[1000];
                int len = 0;
                for(auto q : L[i]){ //pt fiecare stare q vedem in ce partitie se duce cu caracterul ch
                    if(delta[{q, ch}] != -1){ //daca exista tranzitie de la q cu caracterul ch
                        int qDest = delta[{q, ch}]; // partitia in care ajungem in urma tranzitarii
                        v[++len].first = partition[qDest]; // in v.first tinem partitia in care se duce q
                        v[len].second = q; // in v.second il tinem pe q
                    }
                }
                sort(v+1, v+len+1); //sortam in functie de partitii. astfel o sa avem starile care se duc in aceleasi partitii unele langa altele
                int origin = v[1].first; //starile care o au ca partitie destinatie pe origin raman in partitia curenta
                for (int j = 2; j <= len; ++j) {
                    if(v[j].first != v[j-1].first){ //daca gasim stari care se duc in partitii diferite fata de starile de dinaintea lor, le punem intr-o partitie noua
                        ok = true; //s-a produs o modificare deci trebuie sa continuam algoritmul de partitionare (conditia de la while)
                        L[NoP].insert(v[j].second); //NoP va fi noua partitie
                        L[i].erase(v[j].second); //scoatem din partitia curenta starea j pe care am pus-o in partitia NoP
                        partition[v[j].second] = NoP;
                        ++NoP; // se mareste numarul de partitii
                    } else if(v[j].first != origin){ //daca starea curenta se duce in aceeasi partitie ca starile de dinaintea ei inseamna ca a fost deja creata o partitie noua iar starea j trebuie doar adaugata la aceasta noua partitie
                        L[NoP-1].insert(v[j].second);
                        L[i].erase(v[j].second);
                        partition[v[j].second] = NoP-1;
                    }
                }
                if(ok)
                    break;
            }
        }
    }



    ///minimizarea efectiva
    Q.clear();
    for (int i = 0; i < NoP; ++i) {
        Q.insert(i); //inseram noile tranzitii i.e. partitiile
    }
    set<int> newF;
    for(auto i : F){
        newF.insert(partition[i]); //starile finale ale automatului minimizat vor fi partitiile care contin stari finale ale automatului initial
    }
    F.clear(); F = newF;
    q0 = partition[q0]; //noua stare initiala va fi partitia care contine starea initiala
    map<pair<int, char>, int> newDelta; //refacem delta
    for(auto i : Q){
        for(auto ch : Sigma){
            int q = *L[i].begin(); //luam o stare din partitia i
            int qDest = delta[{q, ch}]; // vedem in ce stare se duce cu caracterul ch
            int dest = partition[qDest]; //vedem in ce partitie este qdest
            newDelta[{i, ch}] = dest; //facem tranzitie intre i si dest cu caracterul ch
        }
    }
    delta = newDelta;
}

istream& operator >> (istream& f, DFA& M){
    int noOfStates;
    f >> noOfStates;
    for (int i = 0; i < noOfStates; ++i){
        int q;
        f >> q;
        M.Q.insert(q);
    }

    int noOfLetters;
    f >> noOfLetters;
    for (int i = 0; i < noOfLetters; ++i){
        char ch;
        f >> ch;
        M.Sigma.insert(ch);
    }

    int noOfTransitions;
    f >> noOfTransitions;
    for(auto q : M.Q){
        for(auto ch : M.Sigma){
            M.delta[{q, ch}] = -1; //initializam toate delta cu -1 pentru ca atunci cand facem querry ul delta(q,ch) sa dea rezultat -1 daca nu exista (by default e 0)
        }
    }
    for (int i = 0; i < noOfTransitions; ++i){
        int s, d;
        char ch;
        f >> s >> ch >> d;
        M.delta[{s, ch}] = d;
    }

    f >> M.q0;

    int noOfFinalStates;
    f >> noOfFinalStates;
    for (int i = 0; i < noOfFinalStates; ++i){
        int q;
        f >> q;
        M.F.insert(q);
    }

    return f;
}

ostream& operator << (ostream& f, DFA& M){
    f << "Q: ";
    for(auto i : M.Q){
        f << i << " ";
    }

    f << "\nSigma: ";
    for(auto ch : M.Sigma){
        f << ch;
    }

    f << "\nq0: " << M.q0;

    f << "\nF: ";
    for(auto i : M.F){
        f << i << " ";
    }

    f << "\ndelta:\n";
    for(auto q : M.Q){
        for(auto ch : M.Sigma){
            f << q << " " << ch << " " << M.delta[{q, ch}] << "\n";
        }
    }
}

int main(){
    ifstream fin("dfa.in");
    ofstream fout("dfa.out");
    DFA M;
    fin >> M;
    fin.close();

    M.minimize();
    fout << M;

    return 0;
}