#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "Tilemap.h"
#include <iostream>

int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);
    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("player_sheet_l.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

	sf::Texture tileTexture;
  	if(!tileTexture.loadFromFile("Grass_Dirt_Set.png")){
    return 1;
  	}
  
  	Tilemap tilemap(tileTexture,"map.csv",5,16);

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(18*5, 0, 18*5, 28*5));
    walkingAnimationUp.addFrame(sf::IntRect(18*2*5, 0, 18*5, 28*5));
    walkingAnimationUp.addFrame(sf::IntRect(18*5, 0, 18*5, 28*5));
    walkingAnimationUp.addFrame(sf::IntRect(0, 0, 18*5, 28*5));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(18*5, 28*5, 18*5, 28*5));
    walkingAnimationRight.addFrame(sf::IntRect(18*2*5, 28*5, 18*5, 28*5));
    walkingAnimationRight.addFrame(sf::IntRect(18*5, 28*5, 18*5, 28*5));
    walkingAnimationRight.addFrame(sf::IntRect(0, 28*5, 18*5, 28*5));

        Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(18*5, 56*5, 18*5, 28*5));
    walkingAnimationDown.addFrame(sf::IntRect(18*2*5, 56*5, 18*5, 28*5));
    walkingAnimationDown.addFrame(sf::IntRect(18*5, 56*5, 18*5, 28*5));
    walkingAnimationDown.addFrame(sf::IntRect(0, 56*5, 18*5, 28*5));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(18*5, 84*5, 18*5, 28*5));
    walkingAnimationLeft.addFrame(sf::IntRect(18*2*5, 84*5, 18*5, 28*5));
    walkingAnimationLeft.addFrame(sf::IntRect(18*5, 84*5, 18*5, 28*5));
    walkingAnimationLeft.addFrame(sf::IntRect(0, 84*5, 18*5, 28*5));


    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 200.f;
    bool noKeyWasPressed = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
	tilemap.draw(window);
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
