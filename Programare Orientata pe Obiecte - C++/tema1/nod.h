#ifndef TEMA1_NOD_H
#define TEMA1_NOD_H


class Nod {
    int info;
    Nod *next;
public:
    Nod();
    Nod(int, Nod *);
    Nod(Nod &p);

    int getInfo();
    void setNext(Nod *n);
    Nod *getNext();
};

inline Nod::Nod(){
    info = 0;
    next = nullptr;
}

inline Nod::Nod(int x, Nod *n){
    info = x;
    next = n;
}

inline Nod::Nod(Nod &p) {
    info = p.info;
    next = p.next;
}

#endif //TEMA1_NOD_H
