#include <fstream>
using  namespace std;
ifstream fin ("bitstring.in");
ofstream fout ("bitstring.out");
int n, len;
string x;

struct BIT{
    string info;
    BIT *left;
    BIT *right;
} *bit;

void insert(string x){
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

void inorder(BIT *p){
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

    inorder(bit);

}
