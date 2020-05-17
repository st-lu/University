//
// Created by luana on 5/16/2020.
//

#ifndef HOMEWORK_3___HASHMAP_HASHMAP_H
#define HOMEWORK_3___HASHMAP_HASHMAP_H


#include "KeyHash.h"
#include "HashNode.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
    HashNode<K, V> **table;
    int size;
    F hashFunction;
public:
    // the user can pass a custom size for the hashmap
    // otherwise the hashmap will stick to a default size
    HashMap(int size = 1111);
    HashMap(HashMap&);
    ~HashMap();

    //method that searches for a key or a key-value pair in the hashmap
    bool search(const K &key, const V &value = V());
    //method that adds a key-value pair to the hashmap
    void add(const K &key, const V &value);
    //method that removes either a key or a value for a key
    void remove(const K &key, const V &value = V());

    //method that returns a vector of known values for a given key
    vector<V> getValuesByKey(const K &key);
    //method that returns the number of keys in the hashmap
    int getNoOfKeys();

    //overloading of the [] operator to return first value know for a given key
    V operator[](const K &key) const;

    template <typename A, typename B, typename C>
    friend ostream&operator<<(ostream&, HashMap<A, B, C>&);

    HashMap& operator=(const HashMap&);
};


template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(int s) : size(s), hashFunction(s) {
    table = new HashNode<K, V> *[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr; //makes all the buckets null
    }
}

template<typename K, typename V, typename F>
HashMap<K, V, F>::~HashMap() {
    for (int i = 0; i < size; ++i) {
        HashNode<K, V> *p = table[i];
        while (p != nullptr) {
            //deletes each key
            HashNode<K, V> *prev = p;
            p = p->getNext();
            delete prev;
        }
        table[i] = nullptr;
    }
    //deletes table
    delete [] table;
}


template<typename K, typename V, typename F>
bool HashMap<K, V, F>::search(const K &key, const V &value) {
    int index = hashFunction(key); //find the index of the key in the table
    HashNode<K, V> *p = table[index];

    while (p != nullptr) {
        //for each key found at the resulting index we search to see
        //if it's the key we're looking for
        if (p->getKey() == key) {
            //if the value has not changed from the default, it means the user only passed the key to be searched
            //otherwise, if the user did pass a value to be searched alongside the key
            //we search the key's vector of values for our requested value
            if(value != V())
                for(auto val : p->getValues()){
                    if(val == value)
                        return true;
                }
            else
                return true;
        }
        p = p->getNext();
    }

    // if the method has returned nothing after the search,
    // it means the queried key is not in the table
    return false;
}

template<typename K, typename V, typename F>
void HashMap<K, V, F>::add(const K &key, const V &value) {
    int index = hashFunction(key);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *p = table[index];

    //this while searches to see if the key we want to insert is already in the hashmap
    //it also searches to see where the key should be placed in the hash list we found
    while (p != nullptr && p->getKey() != key) {
        prev = p;
        p = p->getNext();
    }

    if (p == nullptr) {
        p = new HashNode<K, V>(key, value);
        if (prev == nullptr) {
            table[index] = p; // if there is no other key at this index, put p first
        } else {
            prev->setNext(p); // if there are other keys, put p after them
        }
    } else {
        //if the key is already in the table, add a new value to it
        p->addValue(value);
    }
}

template<typename K, typename V, typename F>
void HashMap<K, V, F>::remove(const K &key, const V &value) {
    int index = hashFunction(key);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *p = table[index];

    //searches for the key we want to remove
    while (p != nullptr && p->getKey() != key) {
        prev = p;
        p = p->getNext();
    }

    if (p == nullptr) {
        // key not found
        return;
    }
    else {
        if(value != V()){ //this means the user only passed a key's value to be deleted
            bool ok = false;
            //we find the index of the value in the key's vector of values and delete it
            int cnt = 0;
            for(auto elem : p->getValues()){
                if(elem == value) {
                    ok = true;
                    break;
                }
                ++cnt;
            }
            //this means the value was not found, so we can't delete it
            if(!ok)
                return;
            //otherwise the value was found and we proceed to delete it
            vector<V> aux = p->getValues();
            aux.erase(aux.begin()+cnt);
            p->setValues(aux);
            return;
        }
        if (prev == nullptr) {
            //if the key has no predecessor it means it's placed first at its respective index
            //so, to delete it, we make its successor the first key in the table
            table[index] = p->getNext();

        } else {
            //if the key is placed at a random position in the list, we link its successor to its predecessor
            prev->setNext(p->getNext());
        }

        delete p;
    }
}

template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(HashMap &H) {
    //we allocate a new table for the container hashmap
    size = H.size;
    table = new HashNode<K, V> *[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }


    for (int i = 0; i < size; ++i) {
        if(H.table[i] == nullptr){
            continue;
        }
        // we add each key-value pair in the copied hashmap to the container hashmap
        auto p = H.table[i];
        while(p != nullptr){
            for(auto elem : p->getValues()){
                add(p->getKey(), elem);
            }
            p = p->getNext();
        }
    }
}

template<typename K, typename V, typename F>
HashMap<K, V, F>& HashMap<K, V, F>::operator=(const HashMap &H) {
    if(this == &H)
        return *this;

    //first we clear the hashmap
    for (int i = 0; i < size; ++i) {
        HashNode<K, V> *p = table[i];
        while (p != nullptr) {
            HashNode<K, V> *prev = p;
            p = p->getNext();
            delete prev;
        }
        table[i] = nullptr;
    }

    auto auxTable = table;
    table = new HashNode<K, V> *[H.size]();
    delete auxTable;
    size = H.size;

    // then we copy the passed hashmap into the container hashmap
    // exactly the same as we did in the copy constructor
    for (int i = 0; i < size; ++i) {
        if(H.table[i] == nullptr){
            continue;
        }
        auto p = H.table[i];
        while(p != nullptr){
            for(auto elem : p->getValues()){
                add(p->getKey(), elem);
            }
            p = p->getNext();
        }
    }

    return *this;
}

template<typename K, typename V, typename F>
vector<V> HashMap<K, V, F>::getValuesByKey(const K &key) {
    int index = hashFunction(key);
    HashNode<K, V> *p = table[index];

    //we search for the key
    while (p != nullptr) {
        if (p->getKey() == key) {
            //once we found the key, we return the vector of values
            return p->getValues();
        }
        p = p->getNext();
    }

    //if the key was not found, the method returns an empty vector
    return vector<V>();
}

template<typename K, typename V, typename F>
int HashMap<K, V, F>::getNoOfKeys() {
    int keys = 0; //variable that stores the number of keys in the hashmap
    for (int i = 0; i < size; ++i) {
        //we search the table for buckets that are not empty
        if(table[i] != nullptr) {
            //for the occupied buckets, we go through all the keys they contain
            auto *p = table[i];
            while(p != nullptr) {
                //once we find a key, we update 'keys'
                keys++;
                p = p->getNext();
            }
        }
    }

    return keys;
}

template<typename K, typename V, typename F>
V HashMap<K, V, F>::operator[](const K &key) const {
    int index = hashFunction(key);
    auto *p = table[index];
    //we search for the passed key
    while(p != nullptr){
        if(p->getKey() == key) {
            vector<V> val = p->getValues();
            //once we find it, we return the first value
            return *val.begin();
        }
        p = p->getNext();
    }
    return 0;
}


template<typename K, typename V, typename F>
ostream &operator<<(ostream &f, HashMap<K, V, F> &H) {
    f << "Number of keys in the hash map: " << H.getNoOfKeys() << "\n";

    for (int i = 0; i < H.size; ++i) {
        if(H.table[i] != nullptr) {
            auto *elem = H.table[i];
            while(elem != nullptr) {
                //we display the values for each key
                f << elem->getKey() << ": ";
                for(auto val : elem->getValues())
                    f << val << " ";
                f << "\n";
                elem = elem->getNext();
            }
        }

    }

    return f;
}




#endif //HOMEWORK_3___HASHMAP_HASHMAP_H
