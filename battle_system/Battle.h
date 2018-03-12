#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Tilemap.h"

using namespace std;

class Battle{
public:
    vector<Character*> players, enemies;
    sf::Sprite background;
    sf::Texture background_texture;    

    Battle(vector<Character*>,vector<Character*>);
    void update();
    void win();
    void lose();
    bool players_are_dead();
    void draw(sf::RenderWindow*);
    
private:
};

#endif
