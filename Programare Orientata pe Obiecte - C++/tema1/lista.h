#ifndef TEMA1_LISTA_H
#define TEMA1_LISTA_H
#include <climits>
#include "nod.h"

class Lista {
    Nod *start;
    Nod *end;
    unsigned int size;
public:
    //constructori & destructor
    Lista();
    Lista(Lista &l);
    ~Lista();

    //metode
    void inserare(int); //metoda prin care inseram un nod la lista
    int* getlist(); //metoda prin care returnam valorile din lista sub forma de array
    unsigned int length(); //metoda prin care returnam size-ul listei
};

inline Lista::Lista() {
    size = 0;
    start = end = nullptr;
}

inline Lista::Lista(Lista &l){
    size = 0;
    start = end = nullptr;
    int *aux = l.getlist();
    for (int i = 0; i < l.length() - 1; i++) {
        inserare(aux[i]);
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
