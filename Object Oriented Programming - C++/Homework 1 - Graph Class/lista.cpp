#include "lista.h"

void Lista::inserare(int x) {
    if (size == 0) {
        start = end = new Nod(x, nullptr);
        size = 1;
    } else {
        end->setNext(new Nod(x, nullptr));
        size++;
        end = end->getNext();
    }
}

int* Lista::getlist(){
    Nod *q = start;
    int *sol = new int[size];
    int j = 0;
    while (j < size) {
        sol[j] = q->getInfo();
        q = q->getNext();
        j++;
    }
    return sol;
}

unsigned int Lista::length() {
    return size;
}