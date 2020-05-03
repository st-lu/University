//
// Created by luana on 4/30/2020.
//

#include <algorithm>
#include "Map.h"
using namespace std;
Map::Map(int h, int w) : height(h), width(w) {
    map = new char*[height];
    for(int i = 0; i < height; ++i){
        map[i] = new char[width];
        fill(map[i], map[i] + width, ' ');
    }
}

int Map::getWidth() const{
    return width;
}

int Map::getHeight() const {
    return height;
}

//this method started out as a method to add characters
//now its an universal method for changing the data on the map
//for a given position
void Map::addCharacter(const char type, const pair<int, int> position) {
    map[position.first][position.second] = type;
}

//overloaded [] to return a given row on the map
char* Map::operator[](const int row) const{
    char *aux = map[row];
    return aux;
}

ostream&operator<<(ostream& f, Map& M){
    f << "Map:\n";

    for (int i = 0; i < M.getHeight(); ++i) {
        for (int j = 0; j < M.getWidth(); ++j) {
            f << M[i][j];
        }
        f << "\n";
    }
    return f;
}

Map::~Map(){
    height = 0;
    width = 0;
    for(int i = 0; i < height; ++i)
        delete[] map[i];
    delete map;
}