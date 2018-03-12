#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"

using namespace std;

class Battle{
public:
    vector<Character*> players, enemies;

    Battle(vector<Character*>,vector<Character*>);
    void update();
    void win();
    void lose();
    bool players_are_dead();
    void draw(sf::RenderWindow*);

private:
};

#endif
