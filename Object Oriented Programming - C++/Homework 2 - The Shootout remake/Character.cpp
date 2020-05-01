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

pair<int, int> Character::findTarget(Map Battlefield){
    for (int i = 0; i < Range/2; ++i) {
        for (int j = 0; j < Range/2; ++j) {
            if(i == 0 && j == 0)
                continue;
            if(Position.first + i < Battlefield.getHeight() && Position.first + j < Battlefield.getWidth() && Battlefield[Position.first + i][Position.second + j] != ' ')
                return pair<int, int>(Position.first + i, Position.second + j);
            if(Position.first - i > 0 && Position.first - j > 0 && Battlefield[Position.first - i][Position.second - j] != ' ')
                return pair<int, int>(Position.first - i, Position.second - j);
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


