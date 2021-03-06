#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/System/Time.hpp>
#include"AnimatedSprite.hpp"

using namespace std;

enum State{waiting, moving, charging};

class Character{
public:
    int level, hp, str, spd, def, agi, reach;
    bool enemy;
    float bat_x_pos, bat_y_pos, initiative;
    State state;
    string name;
    vector<Character*> targets;
    sf::Texture texture;
    AnimatedSprite sprite;
    Animation current_animation, moving_up, moving_left, moving_right, moving_down;
    sf::Clock frame_clock;
    sf::Time frame_time;

    Character();

    void update();
    void set_action();
    float get_init_prog();
    float get_dist_to_trg();    
    void phys_attack();    
    bool is_dead();
    void set_targets(vector<Character*>);
    void draw(sf::RenderWindow*);
    void move_to_trg();
    void knock_back(Character*);
private:
};

#endif
