//
// Created by luana on 4/30/2020.
//

#include "Spy.h"
#include "Revolver.h"
#include "BulletproofVest.h"
Spy::Spy(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Revolver;
    weapon->setHealth(health);
    armor = new BulletproofVest(0); //spies don't wear armors
}

void Spy::setHealth(const int health) {
    Health = health;
    //when a spy's health gets updated, we communicate that to the weapon
    weapon->setHealth(health);
}

void Spy::name(){
    cout << "Spy";
}

Spy::~Spy(){
    delete weapon;
    delete armor;
}