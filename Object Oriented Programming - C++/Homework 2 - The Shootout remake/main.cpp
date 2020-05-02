#include <iostream>
#include <fstream>
using namespace std;
ifstream fin ("test.txt");
#include "GameEngine.h"

int main() {
    int h, w;
    cout << "Insert map size (has to be bigger than 25x25)\n";
    h = w = 0;
    while(h < 25 || w < 25) {
        cout << "Height: ";
        //fin >> h;
        cin >> h;
        if(h < 25) {
            cout << "Invalid height. Try again\n";
            continue;
        }
        cout << "Width: ";
        //fin >> w;
        cin >> w;
        if(w < 25) {
            cout << "Invalid width. Try again.\n";
            continue;
        }
    }

    Game G(h, w);
    char cont;
    int round = 1;
    G.showMap();
    cout<< "Do you wish to go on?\nYes - Press Y\n No - Press N\n";
    //fin >> cont;
    cin >> cont;
    while(cont == 'y'){
        cout << "\nKey: S - sniper; Y - spy; P - Soldier; G - Grenadier\n";
        cout << "Phase " << round << "\n";
        G.run();
        cout<< "Do you wish to go on?\nYes - Press Y\n No - Press N\n";
        //fin >> cont;
        cin >> cont;
        round ++;
    }

    return 0;
}
