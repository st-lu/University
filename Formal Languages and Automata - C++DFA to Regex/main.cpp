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
    map<pair<int, string>, set<int>> delta;

public:
    DFA() { this->q0 = 0; }
    DFA(set<int> Q, set<string> Sigma, map<pair<int, string>, set<int>> delta, int q0, set<int> F){
        this->Q = Q;
        this->Sigma = Sigma;
        this->delta = delta;
        this->q0 = q0;
        this->F = F;
    }

    set<int> getQ() const { return this->Q; }
    set<int> getF() const { return this->F; }
    set<string> getSigma() const { return this->Sigma; }
    int getInitialState() const { return this->q0; }
    map<pair<int, string>, set<int>> getDelta() const { return this->delta; }

    friend istream& operator >> (istream&, DFA&);

    bool isFinalState(int);
//    int deltaStar(int, string);
    string toRegex();
};

bool DFA::isFinalState(int q)
{
    return F.find(q) != F.end();
}

//int DFA::deltaStar(int q, string w)
//{
//    if (w.length() == 1)
//    {
//        return delta[{q, (char)w[0]}];
//    }
//
//    int new_q = delta[{q, (char)w[0]}];
//    return deltaStar(new_q, w.substr(1, w.length() - 1));
//}

string DFA::toRegex(){
//    DFA R(Q, Sigma, delta, q0, F);
//    bool ok = false;
//    int maxim = 0;
//    int len = Q.size();
//    for(auto q : R.Q){
//        for(auto ch : R.Sigma){
//            if(*delta[{q, ch}].begin() == R.q0){
//                ok = true;
//            }
//        }
//        if(q > maxim)
//            maxim = q;
//    }
//
//    if(ok){
//        //lambda == ""
//        maxim ++;
//        R.delta[{maxim, ""}].insert(q0);
//        R.q0 = maxim;
//        R.Q.insert(maxim);
//        maxim ++;
//    }
//
//    if(R.F.size() == 1) {
//        ok = true;
//        for (auto ch : R.Sigma) {
//            if (!R.delta[{*R.F.begin(), ch}].empty()) {
//                R.delta[{*R.F.begin(), ""}].insert(maxim);
//                ok = false;
//                break;
//            }
//        }
//        if(!ok){
//            R.Q.insert(maxim);
//            R.F.clear();
//            R.F.insert(maxim);
//        }
//    } else{
//        for(auto q : R.F){
//            R.delta[{q, ""}].insert(maxim);
//            R.Sigma.insert("");
//        }
//        R.F.clear(); R.F.insert(maxim); R.Q.insert(maxim);
//    }
//
//    int l = 0; int r = 0;
//    int out = *R.delta[{q0, ""}].begin(); //starea pe care vrem sa o eliminam
//    int qf = *R.F.begin();
//    while(Q.size() > 2){
//        int newout = out;
//        for(auto q : R.Q){ //luam starea q
//            for(auto ch : R.Sigma) { //luam fiecare tranzitie a lui q
//                for(auto qexit : R.delta[{q, ch}])
//                    if (qexit == out){ //daca q are tranzitie catre starea pe care vrem sa o eliminam
//                        for(auto chr : R.Sigma){
//                            for( auto qexitnew : R.delta[{out, chr}]){// luam toate tranzitiile lui out
//                                bool ok = false;
//                                for(auto chrr : R.Sigma){ //verificam daca q are tranzitie catre starile in care se duce out
//                                    for(auto qq : R.delta[{q, chrr}])
//                                        if(qq == qexitnew) {
//                                            ok = true;
//                                            string newtrans = ch; newtrans += chr; newtrans += chrr;
//                                            delta[{q, newtrans}].insert(qexitnew);
//                                            R.delta[{q, chrr}].erase(qq);
//                                            if(newout == out && newout != qf)
//                                                newout = qexitnew;
//                                            R.Sigma.insert(newtrans);
//                                        }
//
//                                }
//                                if(!ok && delta[{q, ch + chr}].empty()) {
//                                    if(newout == out && newout != qf)
//                                        newout = qexitnew;
//                                    delta[{q, ch + chr}].insert(*R.delta[{out, chr}].begin());
//                                    R.Sigma.insert(ch + chr);
//                                }
//                            }
//                        }
//                        R.delta[{q, ch}].erase(out);
//                    }
//            }
//        }
//        Q.erase(out);
//        out = newout;
//    }
//    for(auto ch : R.Sigma){
//        return ch;
//    }

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
        string ch;
        f >> ch;
        M.Sigma.insert(ch);
    }

    int noOfTransitions;
    f >> noOfTransitions;
    for (int i = 0; i < noOfTransitions; ++i){
        int s, d;
        string ch;
        f >> s >> ch >> d;
        M.delta[{s, ch}].insert(d);
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

int main()
{
    DFA M;

    ifstream fin("dfa.txt");
    ofstream fout("valeleu.txt");
    fin >> M;
    fin.close();

    fout << M.toRegex();
//    int lastState = M.deltaStar(M.getInitialState(), "ab");
//
//    if (M.isFinalState(lastState))
//    {
//        cout << "Cuvant acceptat";
//    }
//    else
//    {
//        cout << "Cuvant respins";
//    }

    return 0;
}