//
// Created by luana on 4/30/2020.
//

#include <iostream>
#include "GameEngine.h"
#include <vector>
using namespace std;
Game::Game(const int height, const int width) : Battlefield(height, width){
    addCharacters();
}

void Game::addCharacters(){
    int maxim = max(Battlefield.getHeight(), Battlefield.getWidth());
    int noOfCharacters = rand()%maxim + 1; //random generation of the number of agents
    for(int i = 0; i < noOfCharacters; i++){
        int ch = rand()%4; //random generation of a character (there are 4 characters)
        pair<int, int> position;
        //random generation of the character's position
        position.first = rand()%Battlefield.getHeight();
        position.second = rand()%Battlefield.getWidth();
        //switch case is my mortal enemy
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

void Game::run(const int round){

    if(round >= Timer){ //if the timer of the nuclear bomb went off, the game is over
        cout << "----GAME OVER----\nGrenadiers won.\n";
        return;
    }

    cout << "Battle Report: \n\n";

    //search if there is only one character left alive
    int aliveCount = 0;
    int cnt = -1;
    for(auto character : Characters){
        ++cnt;
        if(!character->isDead()) {
            aliveCount++;
        }
    }

    //if there is only one character left alive, game is over
    if(aliveCount == 1){
        cout << "GAME OVER\n";
        auto winner = *(Characters.begin()+cnt);
        winner->winMessage();
        return;
    }

    int *di = new int[8]; di[0] = 0; di[1] = 0; di[2] = 1; di[3] = -1; di[4] = 1; di[5] = 1; di[6] = -1; di[7] = -1;
    int *dj = new int[8]; dj[0] = 1; dj[1] = -1; dj[2] = 0; dj[3] = 0; dj[4] = 1; dj[5] = -1; dj[6] = 1; di[7] = -1;

    //if the game is not over, we take each character(player) from the list
    //and set a target for it, or we change it's position
    for (auto player : Characters) {
        if(player->isDead()) //if the current player is dead, skip to the next one
            continue;
        auto target = findTarget(player->getPosition(), player->getRange());
        //if not target was found, the character can move
        if(target == pair<int, int>(-1, -1)){
            pair<int, int> position = player->getPosition();
            bool ok = false;
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if(position.first + di[i] < Battlefield.getHeight() && position.first + di[i] > 0
                        && position.second + dj[j] < Battlefield.getWidth() && position.second + dj[j] > 0) {
                        pair<int, int> newPosition = pair<int, int>(position.first + di[i], position.second + dj[j]);
                        player->positionMessage(newPosition);
                        player->changePosition(Battlefield, newPosition);
                        ok = true;
                        break;
                    }
                }
                if(ok)
                    break;
            }
        } else{
            //if there is an enemy in our player's range, we search for it and attack it
            for (auto enemy : Characters) {
                if (enemy->getPosition() == target) {
//                        player->name();
//                        cout << "(" << player->getPosition().first << ", "
//                             << player->getPosition().second <<") attacked ";
//                        enemy->name();
//                        cout << "(" << enemy->getPosition().first << ", " << player->getPosition().second << ")\n";
                    int inflictedDamage = player->getDamage();
                    int armorProtection = enemy->getProtection();
                    enemy->setHealth(enemy->getHealth() - inflictedDamage + armorProtection);
                    //if an enemy is dead we delete it off the map
                    if(enemy->isDead()) {
                        Battlefield.addCharacter(' ', enemy->getPosition());
                        enemy->deadMessage();
                        player->killerMessage();
                    }
                }
            }

        }
    }

    showMap();
    delete[] di;
    delete[] dj;
}

pair<int, int> Game::findTarget(const pair<int, int> attackerPosition, int range) {
    for(auto enemy : Characters) {
        if(enemy->isDead())
            continue;
        auto enemyPosition = enemy->getPosition();
        //a player can't attack itself
        if(enemyPosition == attackerPosition)
            continue;
        //if the enemy is in range, we return its position
        if(enemyPosition.first < attackerPosition.first + range &&
            enemyPosition.first > attackerPosition.first - range &&
            enemyPosition.second < attackerPosition.second + range &&
            enemyPosition.second > attackerPosition.second - range)
            return enemyPosition;
    }
    return pair<int, int>(-1, -1);
}

void Game::showMap() {
    cout << "\n" << Battlefield;
}

Game::~Game(){}