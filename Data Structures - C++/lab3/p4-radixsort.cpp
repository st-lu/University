#include <fstream>
using namespace std;
ifstream fin ("radixsort.in");
ofstream fout ("radixsort.out");
int n, v[100001], p, maxim;

void countsort(){
    int f[10];
    for (int i = 0; i < 10; ++i) {
        f[i] = 0;
    }
    int sol[100001];
    for (int i = 1; i <= n ; ++i) {
        f[(v[i] / p) % 10] ++;
    }

    for (int i = 1; i < 10; ++i) {
        f[i] += f[i - 1];
    }

    for (int i = n; i >= 1; --i) {
        sol[f[(v[i] / p) % 10]] = v[i];
        --f[(v[i] / p) % 10];
    }

    for (int i = 1; i <= n; ++i) {
        v[i] = sol[i];
    }

}

int main() {
    fin>>n;
    for (int i = 1; i <=n ; ++i) {
        fin>>v[i];
        maxim = max(v[i], maxim);
    }

    p = 1;
    while(p <= maxim){
        countsort();
        p *= 10;
    }

    for (int i = 1; i <= n; ++i) {
        fout<<v[i]<<" ";
    }
    return 0;
}
