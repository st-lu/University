//
// Created by luana on 4/30/2020.
//

#include "Soldier.h"
#include "Rifle.h"
Soldier::Soldier(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Rifle;
    armor = new BulletproofVest;
}

Soldier::~Soldier(){
    delete weapon;
    delete armor;
}