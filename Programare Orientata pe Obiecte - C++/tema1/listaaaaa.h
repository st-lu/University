#ifndef TEMA1_LISTAAAAA_H
#define TEMA1_LISTAAAAA_H

#include "nodddd.h"
class Lista {
    Nod *start;
    Nod *end;
    unsigned int size;
public:
    Lista() {
        size = 0;
        start = end = nullptr;
    }

    void inserare(int x) {
        if (size == 0) {
            start = end = new Nod(x, nullptr);
            size = 1;
        } else {
            end->setNext(new Nod(x, nullptr));
            size++;
            end = end->getNext();
        }
    }

    Lista(Lista &l) {
        size = 0;
        start = end = nullptr;
        for (int i = 0; i < l.length() - 1; i++) {
            inserare(l.get(i));
        }
    }

    int get(int i) {
        if (i > size)
            return INT_MAX;
        Nod *q = start;
        int j = 0;
        while (j < i) {
            q = q->getNext();
            j++;
        }
        return q->getInfo();
    }

    unsigned int length() {
        return size;
    }

    ~Lista() {
        Nod *q = start;
        while (q != nullptr) {
            Nod *p = q->getNext();
            delete q;
            q = p;
        }
    }
};

#endif //TEMA1_LISTAAAAA_H
