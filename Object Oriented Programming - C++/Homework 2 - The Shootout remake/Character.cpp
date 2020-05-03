//
// Created by luana on 4/30/2020.
//

#include "Character.h"


Character::Character(pair<int, int> position, int health, int range, char type ) : Position(position), Health(health), Range(range), Type(type){}

int Character::getHealth() {
    return Health;
}

void Character::setHealth(const int newHealth){
    Health = newHealth;
}

int Character::getRange() {
    return Range;
}


pair<int, int> Character::getPosition(){
    return Position;
}

int Character::getDamage() {
    armor->decreaseDurability();
    return weapon->getDamage();
}

int Character::getProtection() {
    if(armor->getDurability())
        return armor->getProtection();

    return 0;
}


bool Character::isDead() {

    return Health <= 0;
}

void Character::changePosition(Map &Battlefield, const pair<int, int> position) {
    Battlefield.addCharacter(Type, position);
    Battlefield.addCharacter(' ', Position);
    Position = position;
}

void Character::positionMessage(const pair<int, int> newPosition) {
    name();
    cout << "(" << Position.first + 1 << ", " << Position.second + 1
         << ")" << " changed position to (" << newPosition.first + 1 << ", " << newPosition.second + 1 << ")\n";
}

void Character::deadMessage() {
    name();
    cout << "(" << Position.first + 1 << ", " << Position.second + 1 << ") is now dead. ";
}

void Character::killerMessage() {
    cout << "Killed by ";
    name();
    cout<< "(" << Position.first + 1 << ", " << Position.second + 1 << ")\n";
}

Character::~Character(){
    Health = 0;
    Range = 0;
    Position = pair<int, int>(0, 0);
    Type = ' ';
}

void Character::winMessage() {
    name();
    cout << "(" << Position.first << ", " << Position.second << ") won.";
}


