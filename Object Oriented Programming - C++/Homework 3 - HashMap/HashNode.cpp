//
// Created by luana on 5/16/2020.
//

#include "HashNode.h"

template<typename K, typename V>
HashNode<K, V>::HashNode(const K &key, const V &value)  : key(key), value(value), next(nullptr) {

}

template<typename K, typename V>
K HashNode<K, V>::getKey() const {
    return key;
}

template<typename K, typename V>
vector<V> HashNode<K, V>::getValue() const {
    return value;
}

template<typename K, typename V>
void HashNode<K, V>::addValue(V value) {
    this->value.push_back(value);
}

template<typename K, typename V>
HashNode<K, V>* HashNode<K, V>::getNext() const {
    return next;
}

template<typename K, typename V>
void HashNode<K, V>::setNext(HashNode *next) {
    HashNode::next = next;
}
