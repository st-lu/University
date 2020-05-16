//
// Created by luana on 5/16/2020.
//

#include "HashMap.h"

template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap() {
    table = new HashNode<K, V> *[Size];
}

template<typename K, typename V, typename F>
HashMap<K, V, F>::~HashMap() {
    for (int i = 0; i < Size; ++i) {
        HashNode<K, V> *p = table[i];
        while (p != nullptr) {
            HashNode<K, V> *prev = p;
            p = p->getNext();
            delete prev;
        }
        table[i] = nullptr;
    }

    delete [] table;
}

template<typename K, typename V, typename F>
bool HashMap<K, V, F>::search(const K &key, const V &value) { ///make it so that you can search for just a key or both a key and a value associated to it
    int index = hashFunction(key);
    HashNode<K, V> *p = table[index];

    while (p != nullptr) {
        if (p->getKey() == key) {
            for(auto val : p->getValues()){
                if(val == value)
                    return true;
            }
        }
        p = p->getNext();
    }
    return false;
}

template<typename K, typename V, typename F>
void HashMap<K, V, F>::add(const K &key, const V &value) {
    int index = hashFunction(key);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *p = table[index];

    //this while searches to see if the key we want to insert is already in the hashmap
    //it also searches to see where the key should be placed at the hash index
    while (p != nullptr && p->getKey() != key) {
        prev = p;
        p = p->getNext();
    }

    if (p == nullptr) {
        p = new HashNode<K, V>(key, value);
        if (prev == nullptr) {
            table[index] = p; // if there is no other key at this index
        } else {
            prev->setNext(p); // if there are other keys, put p after them
        }
    } else {
        //if the key is already in the table, add a new value to it
        p->addValue(value);
    }
}

template<typename K, typename V, typename F>
void HashMap<K, V, F>::remove(const K &key) {
    int index = hashFunction(key);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *p = table[index];

    while (p != nullptr && p->getKey() != key) {
        prev = p;
        p = p->getNext();
    }

    if (p == nullptr) {
        // key not found
        return;
    }
    else {
        if (prev == nullptr) {
            table[index] = p->getNext(); //if the key has no predecessor it means it's the first at its respective index
                                         //so, to delete it, we make its successor the first key in the table
        } else {
            prev->setNext(p->getNext()); //ay caramba
        }

        delete p;
    }
}

///does this even work
template<typename K, typename V, typename F>
HashMap<K, V, F>::HashMap(HashMap &H) {
    H.table = table;
}

template<typename K, typename V, typename F>
HashMap<K, V, F>& HashMap<K, V, F>::operator=(const HashMap &H) {
    if(this == &H)
        return *this;

    this->table = H.table;

    return *this;
}

template<typename K, typename V, typename F>
vector<V> HashMap<K, V, F>::getValuesByKey(const K &key) {
    int index = hashFunction(key);
    HashNode<K, V> *p = table[index];

    while (p != nullptr) {
        if (p->getKey() == key) {
            return p->getValues();
        }
        p = p->getNext();
    }

}

template<typename K, typename V, typename F>
int HashMap<K, V, F>::getNoOfKeys() {
    int keys = 0;
    for (int i = 0; i < Size; ++i) {
        if(table[i] != nullptr)
            for(auto p : table[i])
                keys++;
    }

    return keys;
}

template<typename K, typename V, typename F>
V HashMap<K, V, F>::operator[](const K &key) const {
    int index = hashFunction(key);
    for(auto p : table[index]){
        if(p->getKey() == key)
            return p->getValues().begin();
    }
}


template<typename K, typename V, typename F>
ostream &operator<<(ostream &f, const HashMap<K, V, F> &H) {
    f << "Number of keys in the hash map: " << H.getNoOfKeys() << "\n";

    for (int i = 0; i < Size; ++i) {
        if(H.table[i] != nullptr) {
            for (auto elem : H.table[i]) {
                f << elem->getKey() << ": ";
                for(auto val : elem.getValues())
                    f << val << " ";
                f << "\n";
            }
        }

    }

    return f;
}


