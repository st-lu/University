//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_REVOLVER_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_REVOLVER_H

#include "Weapon.h"

class Revolver : public Weapon {
protected:
    int Health;
public:
    Revolver(int damage = 100);
    //damage of this weapon changes based on how much health
    //its wielder has left. only spies can wield revolvers
    int getDamage() override;
    void setHealth(int) override;
    ~Revolver();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_REVOLVER_H
