//
// Created by luana on 4/30/2020.
//

#include "Soldier.h"
#include "Rifle.h"
Soldier::Soldier(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Rifle;
    armor = new BulletproofVest;
}

void Soldier::name(){
    cout << "Soldier";
}

bool Soldier::isDead(){
    if(Health <= 0 && Reinforcement > 0){
        //Soldiers have the power of Brotherhood. Kill one and another one comes to reinforce him.
        //A soldier can call for reinforcements up to 5 times.
        //However, adrenaline points are lost
        --Reinforcement;
        cout << "Soldier (" << Position.first << ", " << Position.second << ") "
             << "called for reinfocement.\n";
        Health = 300;
        weapon->setAdrenaline(0);
    }
    return Health <= 0;
}


Soldier::~Soldier(){
    delete weapon;
    delete armor;
}