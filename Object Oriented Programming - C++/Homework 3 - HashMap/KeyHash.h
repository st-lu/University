//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_KEYHASH_H
#define HOMEWORK_3___HASHMAP_KEYHASH_H


template <typename K>
class KeyHash {
public:
    unsigned long operator()(const K& key) const;
};

template<typename K>
inline unsigned long KeyHash<K>::operator()(const K &key) const {
    return reinterpret_cast<unsigned long>(key) % Size; ///dont forget Size here
}


#endif //HOMEWORK_3___HASHMAP_KEYHASH_H
