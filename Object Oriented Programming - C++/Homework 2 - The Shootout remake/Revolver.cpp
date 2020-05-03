//
// Created by luana on 4/30/2020.
//

#include "Revolver.h"

Revolver::Revolver(int damage) : Weapon(damage){}



Revolver::~Revolver(){}

int Revolver::getDamage() {
    //Spies can deal more damage depending on how much
    //health they have left
    //don't ask why... it just happens

    return Damage + Health*0.75;

}

void Revolver::setHealth(const int health) {
    Health = health;
}
