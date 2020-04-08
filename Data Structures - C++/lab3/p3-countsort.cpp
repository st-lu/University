#include <fstream>
using namespace std;
ifstream fin ("countsort.in");
ofstream fout ("countsort.out");
int n, v[100001],f[1000001], sol[100001], maxim;
int main() {
    fin>>n;
    for (int i = 1; i <= n; ++i) {
        fin>>v[i];
        f[v[i]]++;
        if(v[i] > maxim)
            maxim = v[i];
    }
    for (int i = 1; i <= maxim; ++i) {
        f[i] += f[i-1];
    }

    for (int i = 1; i <= n; ++i){
        sol[f[v[i]]] = v[i];
        --f[v[i]];
    }

    for (int i = 1; i <= n; ++i) {
        v[i] = sol[i];
        fout<<v[i]<<" ";
    }

    return 0;
}
