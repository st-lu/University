#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;
// '.' o sa fie lambda
class LNFA{
    set<int> Q, F;
    set<char> Sigma;
    set<int> q0;
    map < pair < int, char >, set < int > > delta;

public:
    LNFA() { this->q0.insert(0); }
    LNFA(set<int> Q, set<char> Sigma, map < pair < int, char >, set < int > > delta, set<int> q0, set<int> F){
        this->Q = Q;
        this->Sigma = Sigma;
        this->delta = delta;
        this->q0 = q0;
        this->F = F;
    }

    set<int> getQ() const { return this->Q; }
    set<int> getF() const { return this->F; }
    set<char> getSigma() const { return this->Sigma; }
    set<int> getInitialState() const { return this->q0; }
    map < pair < int, char >, set < int > > getDelta() const { return this->delta; }

    friend istream& operator >> (istream&, LNFA&);

    bool isFinalState(set<int>);
    set<int> deltaStar(set<int>, string);
    void lambdaTransitions(set<int>&);
};

bool LNFA::isFinalState(set<int> q){
    for(int i : q)
        for(int j : F)
            if(i == j)
                return true;
    return false;
}

void LNFA::lambdaTransitions(set<int> &s){
    set<int> queue;
    for(int i : s)
        queue.insert(i);

    set<int> eraseTransFromQ;
    while(!queue.empty()){
        for(int i : queue){
            for(int j : delta[{i, '.'}]){
                queue.insert(j);
                s.insert(j);
            }
            eraseTransFromQ.insert(i);
        }
        for(int i : eraseTransFromQ)
            queue.erase(i);
    }
}

set<int> LNFA::deltaStar(set<int> s, string w){
    int n = w.length() ;
    set<int> localFinalStates;
    lambdaTransitions(s);
    for(int i : s) {
        localFinalStates.insert(i);
    }
    if(n == 0)
        return localFinalStates;

    int contor = 0;

    while(n){
        set<int> auxiliar;

        for(int i : localFinalStates){
            for(int j : delta[{i, w[contor]}])
                auxiliar.insert(j);
        }

        n--;
        contor++;
        localFinalStates.clear();

        for(int i : auxiliar)
            localFinalStates.insert(i) ;

        auxiliar.clear() ;
        lambdaTransitions(localFinalStates);
    }
    return localFinalStates ;
}

istream& operator >> (istream& f, LNFA& M){
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
    for (int i = 0; i < noOfTransitions; ++i){
        int s, d, noOfTransStates;
        char ch;
        f >> s >> ch >> noOfTransStates;
        for(int j = 0; j < noOfTransStates; j++){
            f >> d;
            M.delta[{s, ch}].insert(d);
        }
    }

    int q0_;
    f >> q0_;
    M.q0.insert(q0_);

    int noOfFinalStates;
    f >> noOfFinalStates;
    for (int i = 0; i < noOfFinalStates; ++i){
        int q;
        f >> q;
        M.F.insert(q);
    }

    return f;
}

int main(){
    LNFA M;

    ifstream fin("lnfa.txt");
    fin >> M;
    fin.close();

    set<int> lastState = M.deltaStar(M.getInitialState(), "aaaaaaaaabbb");

    if (M.isFinalState(lastState))
        cout << "Cuvant acceptat";
    else
        cout << "Cuvant respins";

    return 0;
}
