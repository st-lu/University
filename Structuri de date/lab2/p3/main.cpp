#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("p3.in");
ofstream fout("p3.out");
int n, tos;
int main() {
    fin>>n;
    bool viz[n+1];
    for(int i = 1; i<= n; i++)
        viz[i] = false;
    int stack[n+1];
    for(int i = 0; i < n; ++i){
        int x;
        fin>>x;
        if(!viz[x]){
            viz[x] = true;
            tos++;
            stack[tos] = x;
        }
        else{
            if(stack[tos] == x)
                tos -= 1;
        }
    }
    if(!tos)
        fout<<"configuratie valida";
    else
        fout<<"configuratie invalida";
}
