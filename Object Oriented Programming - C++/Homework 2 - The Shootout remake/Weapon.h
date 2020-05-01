//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H


class Weapon {
protected:
    int Damage;
public:
    Weapon(int damage = 50);
    int getDamage();

    virtual ~Weapon() = 0;
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H
