#include "Battle.h"
#include <iostream>
#include <unistd.h>

int main(){
    sf::RenderWindow window(sf::VideoMode(600,600), "Battle");

    Character player;
    Character enemy;
    player.name = "Junius";
    enemy.name = "Wolf";
    enemy.bat_x_pos = 500;
    enemy.bat_y_pos = 500;
    enemy.sprite.setPosition(500,500);
    vector<Character*> players, enemies;
    players.push_back(&player);
    enemies.push_back(&enemy);

    Battle battle(players,enemies);

    while(window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
        
        window.clear();
        battle.update();
        battle.draw(&window);
        window.display();
        
    }
        return 0;
}
