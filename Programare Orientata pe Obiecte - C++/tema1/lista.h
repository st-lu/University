#ifndef TEMA1_LISTA_H
#define TEMA1_LISTA_H
#include <climits>
#include "nod.h"

class Lista {
    Nod *start;
    Nod *end;
    unsigned int size;
public:
    Lista();
    void inserare(int);
    Lista(Lista &l);

    int get(int i);
    int* getlist();
    unsigned int length();

    ~Lista();
};

inline Lista::Lista() {
    size = 0;
    start = end = nullptr;
}

inline Lista::Lista(Lista &l){
    size = 0;
    start = end = nullptr;
    for (int i = 0; i < l.length() - 1; i++) {
        inserare(l.get(i));
    }
}

inline Lista::~Lista() {
    Nod *q = start;
    while (q != nullptr) {
        Nod *p = q->getNext();
        delete q;
        q = p;
    }
}

#endif //TEMA1_LISTA_H
