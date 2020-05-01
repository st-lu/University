//
// Created by luana on 4/30/2020.
//

#include "Spy.h"
#include "Revolver.h"
#include "BulletproofVest.h"
Spy::Spy(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Revolver;
    armor = new BulletproofVest(0); //spy does not have an armor
}

Spy::~Spy(){
    delete weapon;
    delete armor;
}