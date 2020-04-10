#include <fstream>
using  namespace std;
ifstream fin ("bstpath.in");
ofstream fout ("bstpath.out");
int n, x, nr, len;
struct BST{
    int info;
    BST *left;
    BST *right;
} *bst;

void insert(int x){
    if(len == 0) {
        bst = new BST;
        bst->info = x;
        bst->left = bst->right = nullptr;
        return;
    }

    BST *p = bst;
    while(p != nullptr) {
        if(x < p->info){
            if(p->left != nullptr){
                p = p->left;
            }
            else{
                BST *q = new BST;
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
                BST *q = new BST;
                p->right = q;
                q->info = x;
                q->left = q->right = nullptr;
                break;
            }
        }
    }

}

void path(BST *p, int a, int b){
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
        path(bst, a, b);
        fout << "\n";
    }

}
