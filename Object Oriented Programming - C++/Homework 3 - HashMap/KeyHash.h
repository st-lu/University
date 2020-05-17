//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_KEYHASH_H
#define HOMEWORK_3___HASHMAP_KEYHASH_H

#include <iostream>
using namespace std;

template <typename K>
class KeyHash {
    int size;
public:
    explicit KeyHash(int s = 1111);
    int operator()(const K& key) const{
        // simple hashing function that returns the mod of the key to the size of the hashtable
        return (int)(key) % size;
    }
};

template<typename K>
KeyHash<K>::KeyHash(int s) : size(s){}


#endif //HOMEWORK_3___HASHMAP_KEYHASH_H
