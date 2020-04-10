#include <fstream>
using  namespace std;
ifstream fin ("bst.in");
ofstream fout ("bst.out");
int n, x, nr, len;
string op;
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

BST* find(int x){
    BST *p = bst;
    while(p != nullptr){
        if(x == p->info)
            return p;

        if(x < p->info)
            p = p->left;
        else
            p = p->right;
    }

    return nullptr;
}

void inorder(BST *p){
    if(!len) {
        fout<<"empty";
        return;
    }
    if(p != nullptr) {
        inorder(p->left);
        fout << p->info << " ";
        inorder(p->right);
    }
}

void preorder(BST *p){
    if(!len) {
        fout<<"empty";
        return;
    }
    if(p != nullptr) {
        fout << p->info << " ";
        preorder(p->left);
        preorder(p->right);
    }
}

void erase(int x){
    BST *p = find(x);
    if(p == nullptr)
        return;
    //cazul 1 -> nodul are ambii fii
    if(p->left != nullptr && p->right != nullptr){
        BST *q = p->left; bool okr = false; BST *prevq = p; // in q am nodul cel mai mare mai mic decat p
        while(q->right != nullptr) {
            okr = true;
            prevq = q;
            q = q->right;
        }

        BST *r = p->right; bool okl = false; BST *prevr = p; // in r am nodul cel mai mic mai mare decat p
        while (r->left != nullptr) {
            prevr = r;
            r = r->left;
            okl = true;
        }

        if(q->left == nullptr) {
            p->info = q->info;
            if(okr)
                prevq->right = nullptr;
            else
                prevq->left = nullptr;
            delete q;
        }
        else if(r->right == nullptr) {
            p->info = r->info;
            if(okl)
                prevr->left = nullptr;
            else
                prevr->right = nullptr;
            delete r;
        }
        else {
            p->info = q->info;
            if(okr)
                prevq->right = q->left;
            else
                prevq->left = q->left;
            delete q;
        }
        return;
    }

    //cazul 2 -> nodul are doar un fiu
    if(p->left != nullptr || p->right != nullptr){
        BST *q;
        if(p->left)
            q = p->left;
        else
            q = p->right;

        p->info = q->info;
        p->left = q->left;
        p->right = q->right;
        delete q;
        return;
    }

    //cazul 3 -> nodul nu are niciun fiu
    p = bst;
    BST *prev = p;
    bool l = false;
    while(p != nullptr){
        if(x == p->info)
            break;
        prev = p;
        if(x < p->info) {
            p = p->left;
            l = true;
        }
        else {
            p = p->right;
            l = false;
        }
    }

    if(l)
        prev->left = nullptr;
    else
        prev->right = nullptr;

    delete p;
}


int main() {
    fin>>n;
    for (int i = 1; i <= n ; ++i) {
        fin >> x;
        insert(x);
        len++;
    }

    inorder(bst);
    fout<<"\n";
    preorder(bst);

    fin>>nr;
    for (int t = 0; t < nr; ++t) {
        fin >> op;
        if(op == "find"){
            fin >> x;
            if(find(x) == nullptr)
                fout << "\n" << x << " not found";
            else
                fout << "\n" << x << " found";
        }

        if(op == "erase"){
            fin >> x;
            erase(x);
            len--;
            fout << "\n";
            preorder(bst);
        }
    }

}
