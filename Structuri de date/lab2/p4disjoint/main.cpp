#include <fstream>
using namespace std;
ifstream fin ("disjoint.in");
ofstream fout ("disjoint.out");
int n,m,op,T[100001], cnt, iv, jv;
int a[1000][1000];
int di[] = {0, 0, 1, -1};
int dj[] = {-1, 1, 0, 0};

struct queue{
    int tata, tag, x, y;
}coada[100001], current, added, rc, rp;

queue rad (queue x){
    while(x.tata > 0)
        x = coada[x.tata];
    return x;
}


int main(){
    fin>>n;
    for(int i = 0; i < n*n; i++)
        coada[i].tata=-1;

    cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin>>a[i][j];
            if(a[i][j]) {
                for (int d = 0; d < 4; ++d) {
                    iv = i + di[d];
                    jv = j + dj[d];

                }


            }
        }
    }







//    current = coada[0];
//    for(int i = 0; i < cnt; i++){
//        int iv, jv;
//        for (int d = 0; d < 4; ++d) {
//            iv = current.x + di[d];
//            jv = current.y + dj[d];
//            if(iv >= 0 && iv < n && jv >= 0 && jv < n && a[iv][jv])
//                added =
//        }
//
//        rc=rad(current);
//        rp=rad(added);
//
//        if(rc.tag != rp.tag){
//            if(rc.tag < rp.tag){
//                coada[rc.tag].tata += coada[rp.tag].tata;
//                coada[rp.tag].tata= rc.tag;
//            }
//            else{
//                coada[rp.tag].tata += coada[rc.tag].tata;
//                coada[rc.tag].tata= rp.tag;
//            }
//        }
//    }

}
