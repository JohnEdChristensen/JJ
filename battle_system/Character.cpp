#include "Character.h"
#include <cmath>

Character::Character() : sprite(sf::seconds(0.2),true,false) {
    texture.loadFromFile("player_sheet_l.png");
    hp = 10;
    str = 1;
    spd = 1;
    initiative = 0;
    reach = 50;
    state = waiting;

    moving_up.setSpriteSheet(texture);
    moving_up.addFrame(sf::IntRect(18*5, 0, 18*5, 28*5));
    moving_up.addFrame(sf::IntRect(18*2*5, 0, 18*5, 28*5));
    moving_up.addFrame(sf::IntRect(18*5, 0, 18*5, 28*5));
    moving_up.addFrame(sf::IntRect(0, 0, 18*5, 28*5));

    moving_right.setSpriteSheet(texture);
    moving_right.addFrame(sf::IntRect(18*5, 28*5, 18*5, 28*5));
    moving_right.addFrame(sf::IntRect(18*2*5, 28*5, 18*5, 28*5));
    moving_right.addFrame(sf::IntRect(18*5, 28*5, 18*5, 28*5));
    moving_right.addFrame(sf::IntRect(0, 28*5, 18*5, 28*5));

    moving_down.setSpriteSheet(texture);
    moving_down.addFrame(sf::IntRect(18*5, 56*5, 18*5, 28*5));
    moving_down.addFrame(sf::IntRect(18*2*5, 56*5, 18*5, 28*5));
    moving_down.addFrame(sf::IntRect(18*5, 56*5, 18*5, 28*5));
    moving_down.addFrame(sf::IntRect(0, 56*5, 18*5, 28*5));

    moving_left.setSpriteSheet(texture);
    moving_left.addFrame(sf::IntRect(18*5, 84*5, 18*5, 28*5));
    moving_left.addFrame(sf::IntRect(18*2*5, 84*5, 18*5, 28*5));
    moving_left.addFrame(sf::IntRect(18*5, 84*5, 18*5, 28*5));
    moving_left.addFrame(sf::IntRect(0, 84*5, 18*5, 28*5));

    current_animation = moving_left;
}

void Character::update(){
    frame_time = frame_clock.restart();
    sprite.play(current_animation);    
    if(initiative>=1.0 && state==waiting) set_action();
    
    switch(state){
    case waiting:
        initiative += get_init_prog();
        sprite.stop();
        break;
    case moving:
        if(get_dist_to_trg()<=reach*reach){
            phys_attack();
            state = waiting;
            initiative = 0;
        }else{
            move_to_trg();
        }
        break;
    case charging:
        break;
    }


    sprite.update(frame_time);
}

void Character::set_action(){
    state = moving;
}

float Character::get_init_prog(){
    return 0.005*spd;
}
    
float Character::get_dist_to_trg(){
    return (bat_x_pos-targets[0]->bat_x_pos)*(bat_x_pos-targets[0]->bat_x_pos)+(bat_y_pos-targets[0]->bat_y_pos)*(bat_y_pos-targets[0]->bat_y_pos); 
}    

void Character::phys_attack(){
    targets[0]->hp-=str;
    cout<<name<<" attacked for "<<str<<" damage"<<endl;
    
    //knock_back(targets[0]);
}

void Character::knock_back(Character* target){
    float x_comp = targets[0]->bat_x_pos-bat_x_pos;
    float y_comp = targets[0]->bat_y_pos-bat_y_pos;
    float dist = sqrt(get_dist_to_trg());

    x_comp/=dist;
    y_comp/=dist;

    target->bat_x_pos-=x_comp*str*100;
    target->bat_y_pos-=y_comp*str*100;
}

void Character::move_to_trg(){
    float x_comp = targets[0]->bat_x_pos-bat_x_pos;
    float y_comp = targets[0]->bat_y_pos-bat_y_pos;
    float dist = sqrt(get_dist_to_trg());

    x_comp/=dist;
    y_comp/=dist;

    bat_x_pos += x_comp*spd;
    bat_y_pos += y_comp*spd;

    if(abs(x_comp) >= abs(y_comp) && x_comp>0) current_animation = moving_right;
    if(abs(x_comp) >= abs(y_comp) && x_comp<0) current_animation = moving_left;
    if(abs(x_comp) <= abs(y_comp) && y_comp>0) current_animation = moving_down;
    if(abs(x_comp) <= abs(y_comp) && y_comp<0) current_animation = moving_up;
}

void Character::draw(sf::RenderWindow* window){
    sprite.setPosition(bat_x_pos,bat_y_pos);
    window->draw(sprite);
}

bool Character::is_dead(){
    if(hp<=0) return true;
    return false;
}
    
void Character::set_targets(vector<Character*> targets){
    this->targets = targets;
}
