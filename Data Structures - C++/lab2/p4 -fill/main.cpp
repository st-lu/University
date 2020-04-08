#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("p4.in");
ofstream fout("p4.out");
int n, color;
int a[1001][1001];
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, 1, -1};

void fill(int i, int j){
    a[i][j] = color;
    for (int d = 0; d < 4; ++d) {
        int iv = i + di[d];
        int jv = j + dj[d];
        if( iv >= 0 && iv < n && jv >= 0 && jv < n && a[iv][jv] == 1){
            fill(iv, jv);
        }
    }
}

int main() {
    fin>>n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin>>a[i][j];
        }
    }

    color = 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(a[i][j] == 1){
                fill(i, j);
                color ++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout<<a[i][j]<<" ";
        }
        fout<<"\n";
    }

    return 0;
}
