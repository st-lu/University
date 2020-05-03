//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_MAP_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_MAP_H

#include <iostream>
using  namespace std;

class Map {
protected:
    int height;
    int width;
    char **map;
public:
    Map(int, int);
    int getHeight() const;
    int getWidth() const;
    void addCharacter(char, pair<int, int>);
    char* operator [](int) const;
    friend ostream&operator<<(ostream&, Map&);
    ~Map();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_MAP_H
