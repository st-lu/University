#include <fstream>
using  namespace std;
ifstream fin ("bststring.in");
ofstream fout ("bststring.out");
int n, len;
string x;

struct BST{
    string info;
    BST *left;
    BST *right;
} *bst;

void insert(string x){
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


int main() {
    fin>>n;
    for (int i = 1; i <= n ; ++i) {
        fin >> x;
        insert(x);
        len++;
    }

    inorder(bst);

}
