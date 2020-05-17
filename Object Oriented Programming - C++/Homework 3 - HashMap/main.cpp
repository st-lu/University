#include <iostream>
#include <cassert>
#include "HashMap.h"
using namespace std;

class Hashing {
    int size;
public:
    explicit Hashing(int size = 1111){
        this->size = size;
    }
    int operator()(const string& key) const{
        int sum = 0;
        for(auto ch : key){
            sum += int(ch);
        }
        return sum;
    }
};

int main() {
    HashMap<int, int> H;
    H.add(3, 4);
    H.add(3, 5);
    H.add(976, 10);
    HashMap<int, int> h1;
    h1 = H;
    cout << h1;
    vector<int> aux = H.getValuesByKey(3);
    assert(*aux.begin() == 4 && *(aux.begin()+1) == 5 && aux.size() == 2);
    assert(H[3] == 4);
    assert(H.getNoOfKeys() == 2);
    H.remove(3, 4);
    HashMap<int, int> h(H);
    cout << h;
    assert(H.getValuesByKey(3).size() == 1 && *H.getValuesByKey(3).begin() == 5);
    assert(H.search(976, 10));
    H.remove(3);
    assert(!H.search(3));

    HashMap<string, int, Hashing> StringHash;
    StringHash.add("hello", 3);
    StringHash.add("world", 90);
    cout << StringHash;
    assert(*StringHash.getValuesByKey("hello").begin() == 3);
    assert(StringHash.search("world"));
    assert(StringHash["hello"] == 3);
    return 0;
}
