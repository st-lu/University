//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H

#include "Weapon.h"

class Grenade : public Weapon {
protected:
    int KillCount = 0;
public:
    //only grenadiers can wield grenades
    Grenade(int damage = 1000);
    int getKillCount() const override;
    int getDamage() override;
    ~Grenade() override;
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H
