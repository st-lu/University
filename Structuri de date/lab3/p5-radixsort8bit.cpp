//p4 bonus cu shift pe 8 biti
//tl;dr - e la fel ca p4 dar am pus [v[i]>>(p*8) & 255] in loc de [(v[i] / p) % 10] cand am facut frecventa in count sort + am schimbat conditia de la while-ul din main
//input si output la fel ca la p4

#include <fstream>
#include <iostream>
using namespace std;
ifstream fin ("radixsortbiti.in");
ofstream fout ("radixsortbiti.out");
int n, v[100001], p, maxim;

void countsort(){
    int f[256];
    for (int i = 0; i < 256; ++i) {
        f[i] = 0;
    }
    int sol[100001];
    for (int i = 1; i <= n ; ++i) {
        f[v[i]>>(p*8) & 255] ++;
    }

    for (int i = 1; i < 256; ++i) {
        f[i] += f[i - 1];
    }

    for (int i = n; i >= 1; --i) {
        sol[f[v[i]>>(p*8) & 255]] = v[i];
        --f[v[i]>>(p*8) & 255];
    }

    for (int i = 1; i <= n; ++i) {
        v[i] = sol[i];
    }

}

int main() {
    fin>>n;

    for (int i = 1; i <=n ; ++i) {
        fin>>v[i];
        maxim = max(maxim, v[i]);
    }
    p = 0;
    while((maxim>>(p*8))){
        countsort();
        p++;
    }

    for (int i = 1; i <= n; ++i) {
        fout<<v[i]<<" ";
    }

    return 0;
}