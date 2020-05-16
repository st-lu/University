//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_HASHMAP_H
#define HOMEWORK_3___HASHMAP_HASHMAP_H

#define Size 1111
#include "KeyHash.h"
#include "HashNode.h"

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
    HashNode<K, V> **table;
    F hashFunction;
public:
    HashMap();
    HashMap(HashMap&);
    ~HashMap();

    bool search(const K &key, const V &value);
    void add(const K &key, const V &value);
    void remove(const K &key);
};




#endif //HOMEWORK_3___HASHMAP_HASHMAP_H
