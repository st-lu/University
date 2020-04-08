#include <fstream>
using namespace std;
ifstream fin("heapuri.in");
ofstream fout ("heapuri.out");
int n, nr, t, ad, k, h[200002];
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
    for(t = 1; t <= nr; ++ t){
        fin>>op;
        if(op == "insert"){
            fin>>h[++n];
            percolate(n);
        }
        if(op == "pop"){
            fout<<h[1]<<"\n";
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
        }

    }
    return 0;
}