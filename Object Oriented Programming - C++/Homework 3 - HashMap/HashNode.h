//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_HASHNODE_H
#define HOMEWORK_3___HASHMAP_HASHNODE_H

#include <vector>
using namespace std;

template <typename K, typename V>
class HashNode {
    K key;
    vector<V> value;
    HashNode *next;
public:
    HashNode(const K &key, const V &value);

    K getKey() const;
    vector<V> getValue() const;
    void addValue(V value);
    HashNode* getNext() const;
    void setNext(HashNode *next);

};



#endif //HOMEWORK_3___HASHMAP_HASHNODE_H
