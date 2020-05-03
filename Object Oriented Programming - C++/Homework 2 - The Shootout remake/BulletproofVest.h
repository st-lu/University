//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_BULLETPROOFVEST_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_BULLETPROOFVEST_H


class BulletproofVest {
protected:
    int Protection;
    int Durability;
public:
    BulletproofVest(int protection = 50);
    int getProtection();
    int getDurability();
    void decreaseDurability();
    ~BulletproofVest();

};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_BULLETPROOFVEST_H
