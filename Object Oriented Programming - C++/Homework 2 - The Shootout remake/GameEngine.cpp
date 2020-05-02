//
// Created by luana on 4/30/2020.
//

#include <iostream>
#include "GameEngine.h"
#include <vector>
using namespace std;
Game::Game(int height, int width) : Battlefield(height, width){
    addCharacters();
}

void Game::addCharacters(){
    int maxim = max(Battlefield.getHeight(), Battlefield.getWidth());
    int noOfCharacters = rand()%maxim + 1;
    for(int i = 0; i < noOfCharacters; i++){
        int ch = rand()%4;
        pair<int, int> position;
        position.first = rand()%Battlefield.getHeight();
        position.second = rand()%Battlefield.getWidth();
        if(ch == 1){
            auto *s = new Sniper(position);
            Characters.push_back(s);
            Battlefield.addCharacter('s', position);
        }
        if(ch == 2){
            auto *y = new Spy(position);
            Characters.push_back(y);
            Battlefield.addCharacter('y', position);
        }
        if(ch == 3){
            auto *p = new Soldier(position);
            Characters.push_back(p);
            Battlefield.addCharacter('p', position);
        }
        if(ch == 0){
            auto *g = new Grenadier(position);
            Characters.push_back(g);
            Battlefield.addCharacter('g', position);
        }
    }
}

void Game::run(){

    int *di = new int[8]; di[0] = 0; di[1] = 0; di[2] = 1; di[3] = -1; di[4] = 1; di[5] = 1; di[6] = -1; di[7] = -1;
    int *dj = new int[8]; dj[0] = 1; dj[1] = -1; dj[2] = 0; dj[3] = 0; dj[4] = 1; dj[5] = -1; dj[6] = 1; di[7] = -1;

    if(Characters.size() == 1){
        cout << "GAME OVER\n";
        auto winner = *Characters.begin();
        switch(winner->getType()){
            case 's': { cout << "Snipers won";}
            case 'y': {cout << "Spies won";}
            case 'p': {cout << "Soldiers won";}
            case 'g': {cout << "Grenadiers won";}
        }
    }

    for (auto player : Characters) {
        if(player->isDead())
            continue;
        auto target = findTarget(player->getPosition(), player->getRange());
        if(target == pair<int, int>(-1, -1)){
            pair<int, int> position = player->getPosition();
            bool ok = false;
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if(position.first + di[i] < Battlefield.getHeight() && position.first + dj[j] > 0
                        && position.second + dj[j] < Battlefield.getWidth() && position.second + dj[j] > 0) {
                        pair<int, int> newPosition = pair<int, int>(position.first + di[i], position.second + dj[j]);
                        player->changePosition(Battlefield, newPosition);
                        ok = true;
                        break;
                    }

                }
                if(ok)
                    break;
            }
        } else{
            int cnt = 0;
            if(player->getType() == 's' || player->getType() == 'p') { //if the player is a sniper or a soldier, it will only attack one target
                for (auto enemy : Characters) {
                    ++cnt;
                    if (enemy->getPosition() == target) {
                        int inflictedDamage = player->getDamage();
                        int armorProtection = player->getProtection();
                        enemy->setHealth(enemy->getHealth() - inflictedDamage + armorProtection);
                    }
                    if(enemy->isDead()) {
                        Battlefield.addCharacter(' ', enemy->getPosition());
                    }
                }
            } else{ //if the player is a spy or a grenadier, it will attack the entire area covered by its range
                int top = max(player->getPosition().first - player->getRange()/2, 0);
                int left = max(player->getPosition().second - player->getRange()/2, 0);
                int bottom = min(player->getPosition().first + player->getRange()/2, Battlefield.getHeight());
                int right = min(player->getPosition().second + player->getRange()/2, Battlefield.getWidth());
                for(auto enemy : Characters){
                    ++cnt;
                    if(enemy->getPosition().first > top && enemy->getPosition().first < bottom &&
                        enemy -> getPosition().second > left && enemy->getPosition().second < right && enemy!=player){
                        int inflictedDamage = player->getDamage();
                        int armorProtection = player->getProtection();
                        enemy->setHealth(enemy->getHealth() - inflictedDamage + armorProtection);
                    }
                    if(enemy->isDead()){
                        Battlefield.addCharacter(' ', enemy->getPosition());
                    }
                }
            }
        }
    }
    showMap();
    delete[] di;
}

pair<int, int> Game::findTarget(pair<int, int> attackerPosition, int range) {
    for(auto enemy : Characters) {
        if(enemy->isDead())
            continue;
        auto enemyPosition = enemy->getPosition();
        if(enemyPosition == attackerPosition)
            continue;
        if(enemyPosition.first < attackerPosition.first + range &&
            enemyPosition.first > attackerPosition.first - range &&
            enemyPosition.second < attackerPosition.second + range &&
            enemyPosition.second > attackerPosition.second - range)
            return enemyPosition;
    }
    return pair<int, int>(-1, -1);
}

void Game::showMap() {
    cout << Battlefield;
}

Game::~Game(){}