#ifndef TEMA1_NODDDD_H
#define TEMA1_NODDDD_H

class Nod{
    int info;
    Nod *next;
public:
    Nod(){
        info = 0;
        next = nullptr;
    }
    Nod(int x, Nod *n){
        info = x;
        next = n;
    }
    Nod(Nod &p){
        info = p.info;
        next = p.next;
    }
    int getInfo(){
        return info;
    }
    void setNext(Nod *n){
        next = n;
    }
    Nod* getNext(){
        return next;
    }
};

#endif //TEMA1_NODDDD_H
