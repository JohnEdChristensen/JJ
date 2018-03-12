#include "Battle.h"

Battle::Battle(vector<Character*> players, vector<Character*> enemies){
    this->players = players;
    this->enemies = enemies;
    
    for(int i = 0;i<players.size();++i){
        players[i]->set_targets(enemies);
    }

    for(int i = 0;i<enemies.size();++i){
        enemies[i]->set_targets(players);
    }


    background_texture.loadFromFile("mapfinal.png");
    background.setTexture(background_texture);   
}

void Battle::update(){
    for(int i = 0;i<players.size();++i){
        players[i]->update();
    }

    for(int i = 0;i<enemies.size();++i){
        enemies[i]->update();
    }

    if(enemies.size() == 0) win();
    
    if(players_are_dead()) lose();
}

void Battle::win(){}

void Battle::lose(){}

bool Battle::players_are_dead(){
    for(int i = 0;i<players.size();++i){
        if(!players[i]->is_dead()) return false; 
    }
    return true;
}
 
void Battle::draw(sf::RenderWindow* window){
    window->draw(background);

    for(int i = 0;i<players.size();++i){
        players[i]->draw(window);
    }

    for(int i = 0;i<enemies.size();++i){
        enemies[i]->draw(window);
    }
}
