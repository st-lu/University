#include <iostream>
#include <fstream>
using namespace std;
ifstream fin ("test.txt");
#include "GameEngine.h"

int main() {
    int h, w;
    cout << "In a battlefield far, far away\n";
    cout << "Made out of spaces and a variations of the same 4 letters\n";
    cout << "4 types of players are fighting to death\nFor whatever reason\n";
    cout << "But will the winner be announced in time?\n";
    cout << "Or will the nuclear bomb planted by a mysterious evil force\n";
    cout << "explode before that happens?\n";
    cout << "If you wish to see how the game unfolds\n";
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
    while(cont == 'y' || cont == 'Y'){
        cout << "\nKey: S - sniper; Y - spy; P - Soldier; G - Grenadier\n\n";
        cout << "Phase " << round << "\n";
        G.run(round);
        cout<< "Do you wish to go on?\nYes - Press Y\n No - Press N\n";
        //fin >> cont;
        cin >> cont;
        round ++;
    }

    return 0;
}
