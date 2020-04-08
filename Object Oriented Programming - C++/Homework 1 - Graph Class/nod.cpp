#include "nod.h"


int Nod::getInfo() {
    return info;
}

void Nod::setNext(Nod *n) {
    next = n;
}

Nod* Nod::getNext() {
    return next;
}