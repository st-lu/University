//
// Created by luana on 4/30/2020.
//

#include "Grenadier.h"
#include "Grenade.h"
Grenadier::Grenadier(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Grenade;
    armor = new BulletproofVest;
}

void Grenadier::name(){
    cout << "Grenadier";
}

int Grenadier::getDamage() {
    //Grenadiers regenerate health every time they kill or wound an enemy
    //depending on their overall kill count
    int damage = weapon->getDamage();
    Health += weapon->getKillCount()*75;
    return damage;
}

Grenadier::~Grenadier(){
    delete weapon;
    delete armor;
}
