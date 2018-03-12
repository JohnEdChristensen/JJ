#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <random>
#include "Tilemap.h"

void randomizeMap(int** tiles,int x, int y){
  int randNum;
  for(int i = 0; i < x; i++){
    for(int j = 0; j < y; j++){
      if(!(i == 0 || j == 0 || i == (x-1) || j == (y-1))){
        randNum = rand()%4;
        if(randNum == 0)
          tiles[i][j] = 0;
        else
          tiles[i][j] = 1;
      }
    }
  }
}
int main(){
  srand (time(NULL));
  int xdim = 1200;
  int ydim = 1000;
  float scaleFactor = 5;
  int tileSize = 16;

  sf::RenderWindow window(sf::VideoMode(xdim, ydim), "Tiles");

  sf::Texture tileTexture;
  if(!tileTexture.loadFromFile("Grass_Dirt_Set.png")){
    return 1;
  }
  //randomizeMap(tileValues,mapDimension.x,mapDimension.y);
  std::string path = "map.csv";
  Tilemap tilemap(tileTexture,path,scaleFactor,tileSize);

  while(window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
    }

    window.clear();
    tilemap.draw(window);
    window.display();
  }

  return 0;
}
