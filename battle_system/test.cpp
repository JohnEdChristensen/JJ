#include "Battle.h"
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode(600,600), "Battle");
    window.setFramerateLimit(60);

    Character player;
    Character enemy;
    player.name = "Junius";
    enemy.name = "Wolf";
    enemy.bat_x_pos = 500;
    enemy.bat_y_pos = 400;
    enemy.current_animation = enemy.moving_left;
    player.bat_x_pos = 50;
    player.bat_y_pos = 300;
    player.current_animation = player.moving_right;
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
