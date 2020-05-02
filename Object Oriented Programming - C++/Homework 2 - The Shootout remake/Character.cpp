//
// Created by luana on 4/30/2020.
//

#include "Character.h"


Character::Character(pair<int, int> position, int health, int range, char type ) : Position(position), Health(health), Range(range), Type(type){}

int Character::getHealth() {
    return Health;
}

void Character::setHealth(int newHealth){
    Health = newHealth;
}

int Character::getRange() {
    return Range;
}

char Character::getType() {
    return Type;
}

pair<int, int> Character::getPosition(){
    return Position;
}

int Character::getDamage() {
    return weapon->getDamage();
}

int Character::getProtection() {
    return armor->getProtection();
}


bool Character::isDead() {
    return Health < 0;
}

pair<int, int> Character::findTarget(Map& Battlefield){
    int *di = new int[8]; di[0] = 0; di[1] = 0; di[2] = 1; di[3] = -1; di[4] = 1; di[5] = 1; di[6] = -1; di[7] = -1;
    int *dj = new int[8]; dj[0] = 1; dj[1] = -1; dj[2] = 0; dj[3] = 0; dj[4] = 1; dj[5] = -1; dj[6] = 1; di[7] = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 1; k <= Range; ++k) {
                if (Position.first + di[i]*k < Battlefield.getHeight() && Position.first + di[i]*k > 0 &&
                    Position.second + dj[j]*k < Battlefield.getWidth() && Position.second + dj[j]*k > 0 &&
                    Battlefield[Position.first + di[i]*k][Position.second + dj[j]]*k != ' ')
                    return pair<int, int>(Position.first + di[i]*k, Position.second + dj[j]*k);
            }
        }
    }
    return pair<int, int>(-1, -1);
}

void Character::changePosition(Map &Battlefield, pair<int, int> position) {
    Battlefield.addCharacter(Type, position);
    Battlefield.addCharacter(' ', Position);
    Position = position;
}

Character::~Character(){
    Health = 0;
    Range = 0;
    Position = pair<int, int>(0, 0);
    char type = ' ';
}


