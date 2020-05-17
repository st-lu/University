//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_KEYHASH_H
#define HOMEWORK_3___HASHMAP_KEYHASH_H

#include <iostream>
#define Size 1111
using namespace std;

template <typename K>
class KeyHash {
public:
    int operator()(const K& key) const{
        return (int)(key) % Size; ///dont forget size here
    }
};


#endif //HOMEWORK_3___HASHMAP_KEYHASH_H
