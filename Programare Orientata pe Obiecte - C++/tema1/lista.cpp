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

int Lista::get(int i){
    if (i > size)
        return INT_MAX; ///exceptie
    Nod *q = start;
    int j = 0;
    while (j < i) {
        q = q->getNext();
        j++;
    }
    return q->getInfo();
}

unsigned int Lista::length() {
    return size;
}