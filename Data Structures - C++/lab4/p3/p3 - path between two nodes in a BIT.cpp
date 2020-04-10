#include <fstream>
using  namespace std;
ifstream fin ("bitpath.in");
ofstream fout ("bitpath.out");
int n, x, nr, len;
string op;
struct BIT{
    int info;
    BIT *left;
    BIT *right;
} *bit;

void insert(int x){
    if(len == 0) {
        bit = new BIT;
        bit->info = x;
        bit->left = bit->right = nullptr;
        return;
    }

    BIT *p = bit;
    while(p != nullptr) {
        if(x < p->info){
            if(p->left != nullptr){
                p = p->left;
            }
            else{
                BIT *q = new BIT;
                p->left = q;
                q->info = x;
                q->left = q->right = nullptr;
                break;
            }
        }
        else{
            if(p->right != nullptr){
                p = p->right;
            }
            else{
                BIT *q = new BIT;
                p->right = q;
                q->info = x;
                q->left = q->right = nullptr;
                break;
            }
        }
    }

}

void path(BIT *p, int a, int b){
    if(p != nullptr) {
        if(p->info > a)
            path(p->left, a, b);
        if(p->info <= b && p->info >= a)
            fout << p->info << " ";
        if(p->info < b)
            path(p->right, a, b);
    }
}


int main() {
    fin >> n;
    for (int i = 1; i <= n ; ++i) {
        fin >> x;
        insert(x);
        len++;
    }

    fin >> nr;
    for (int t = 0; t < nr; ++t) {
        int a, b;
        fin >> a >> b;
        path(bit, a, b);
        fout << "\n";
    }

}
