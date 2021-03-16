#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class DFA{
    set<int> Q, F;
    set<string> Sigma;
    int q0;
    string delta[101][101];

public:
    DFA() {
        this->q0 = 0;
        for (int i = 1; i <= Q.size(); ++i) {
            for (int j = 1; j <= Q.size() ; ++j) {
                this->delta[i][j] = "null";
            }
        }
    }
    DFA(set<int> Q, set<string> Sigma, string delta[101][101], int q0, set<int> F){
        this->Q = Q;
        this->Sigma = Sigma;
        for (int i = 1; i <= Q.size(); ++i) {
            for (int j = 1; j <= Q.size() ; ++j) {
                this->delta[i][j] = delta[i][j];
            }
        }
        this->q0 = q0;
        this->F = F;
    }

    set<int> getQ() const { return this->Q; }
    set<int> getF() const { return this->F; }
    set<string> getSigma() const { return this->Sigma; }
    int getInitialState() const { return this->q0; }
    string getDelta() const { return this->delta[101][101]; }

    friend istream& operator >> (istream&, DFA&);

    bool isFinalState(int);
    string toRegex();

};

bool DFA::isFinalState(int q)
{
    return F.find(q) != F.end();
}

string DFA::toRegex(){
    DFA R; R.Q = Q; R.Sigma = Sigma; R.q0 = q0; R.F = F; //imi creez un automat de lucru
    bool ok = false;
    bool scos[10001] = {false};
    for (int i = 0; i <= Q.size(); ++i) {
        for (int j = 0; j <= Q.size(); ++j) {
            R.delta[i][j] = delta[i][j];
            if(j == q0 && R.delta[i][j] != "null") // inseamna ca avem stari care intra in q0
                ok = true;
        }
    }
    int NoT = Q.size();
    if(ok){ //daca avem stari care intra in q0
        R.delta[0][q0] = "."; //cream o stare noua, 0, si facem tranzitie cu lambda la starea initiala
        R.Sigma.insert(".");
        R.q0 = 0;
        R.Q.insert(0);
    }
    ok = false;
    for( auto q : F){
        for (int j = 0; j <= Q.size(); ++j) {
            if(delta[q][j] != "null") //daca avem o stare care iese din starea finala q inseamna ca trebuie sa facem o stare finala noua
                ok = true;
        }
    }

    if(ok || F.size() != 1){
        int newF = NoT+1; //facem o stare finala noua
        R.Q.insert(newF);
        for(auto q : R.F){
            R.delta[q][newF] = "."; //facem lambda tranzitie de la starile finale initiale la cea noua
        }
        R.F.clear(); R.F.insert(newF); //noua stare finala devine unica stare finala
    }

    for (int out = 1; out <= NoT ; ++out) { //luam fiecare tranzitie pe rand (trebuie sa fie date din input in ordine de la 1 la nr de tranzitii)
        for (int i = 0; i <= R.Q.size() ; ++i) { //luam fiecare tranzitie si vedem daca merge in out
            if(scos[i])
                continue;
            for (int j = 0; j <= R.Q.size() ; ++j) {
                if(scos[j])
                    continue;
                if(j == out && R.delta[i][out] != "null"){ //daca tranzitia i merge in out
                    for (int k = 1; k <= R.Q.size() ; ++k) { //luam toate tranzitiile care ies din out
                        if(scos[k])
                            continue;
                        if(R.delta[out][k] != "null"){
                            if(out == k ){ //daca avem tranzitie de la out la k o facem nebunie din aia cu *
                                R.delta[out][k] = "(" + R.delta[out][k] + ")*";
                                R.Sigma.insert(R.delta[out][k]);
                            }
                            if(R.delta[i][k] == "null"){ //daca nu avem tranzitie de la starea i la starea k atunci concatema delta urile direct
                                R.delta[i][k] = "(" + R.delta[i][out] + ")" + "(" + R.delta[out][k] + ")";
                            }
                            else{ //daca avem tranzitie de la starea i la starea k atunci facem string ul initial din delta[i][k] + stringul de pe drumul care il contine pe out de la i la k
                                R.delta[i][k] += "+(" + R.delta[i][out] + ")" + "(" + R.delta[out][k] + ")";
                            }
                            Sigma.insert(R.delta[i][k]);
                        }
                    }
                }
            }
        }
        R.Q.erase(out); //il stergem pe out
        scos[out] = true;
    }


    return R.delta[R.q0][*R.F.begin()];
}


istream& operator >> (istream& f, DFA& M)
{
    int noOfStates;
    f >> noOfStates;
    for (int i = 0; i < noOfStates; ++i)
    {
        int q;
        f >> q;
        M.Q.insert(q);
    }

    int noOfLetters;
    f >> noOfLetters;
    for (int i = 0; i < noOfLetters; ++i){
        string ch;
        f >> ch;
        M.Sigma.insert(ch);
    }

    int noOfTransitions;
    f >> noOfTransitions;
    for (int i = 0; i <= M.Q.size()+1; ++i) {
        for (int j = 0; j <= M.Q.size()+1 ; ++j) {
            M.delta[i][j] = "null";
        }
    }
    for (int i = 0; i < noOfTransitions; ++i)
    {
        int s, d;
        string ch;
        f >> s >> ch >> d;
        M.delta[s][d] = ch;
    }

    f >> M.q0;

    int noOfFinalStates;
    f >> noOfFinalStates;
    for (int i = 0; i < noOfFinalStates; ++i)
    {
        int q;
        f >> q;
        M.F.insert(q);
    }

    return f;
}

int main()
{
    DFA M;

    ifstream fin("dfa.in");
    ofstream fout("dfa.out");
    fin >> M; //starile care sunt date la citire trebuie sa fie mai mari ca 0
    fin.close();

    fout << M.toRegex();

    return 0;
}