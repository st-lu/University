#include <fstream>
using namespace std;
ifstream fin("heapsort.in");
ofstream fout ("heapsort.out");
int n, nr, t, ad, k, h[200002], v[200002], cnt;
string op;

void percolate(int k){
    while(h[k] < h[k/2] && k != 1){
        swap(h[k], h[k/2]);
        k /= 2;
    }
}

void sift(int k){
    while((2*k) <= n){
        if(2*k + 1 <= n){
            if(h[k] < min(h[2*k], h[2*k + 1]))
                break;

            if(h[2*k] < h[2*k + 1]){
                swap(h[k], h[2*k]);
                k *= 2;
            }
            else{
                swap(h[k], h[2*k + 1]);
                k = 2*k + 1;
            }
        }
        else{
            if(h[k] > h[2*k]){
                swap(h[k], h[2*k]);
                k *= 2;
            }
            else break;
        }

    }
}


int main(){
    fin>>nr;
    for(t = 1; t <= nr; ++ t) {
        fin >> h[++n];
        percolate(n);
    }

    while(nr){
        v[++cnt] = h[1];
        k = 1;
        swap(h[k], h[n]);
        --n;
        if (2*k + 1 <= n) {
            if (h[k] > min(h[2*k + 1], h[2 * k]))
                sift(k);
        }
        else
            if (h[k] > h[2*k])
                sift(k);
        --nr;
    }

    for (int i = 1; i <= cnt; ++i) {
        fout<<v[i]<<" ";
    }
    return 0;
}