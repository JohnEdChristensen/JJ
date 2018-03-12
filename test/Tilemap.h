#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
using namespace std;
class Tilemap{
private:
  struct Cell{
    int a,b,c,d;
    sf::Sprite sprite;
  };
  sf::Sprite main;
  sf::Sprite fill;
  sf::Sprite edge;
  sf::Sprite outerCorner;
  sf::Sprite innerCorner;
  sf::Texture tileSheet;
  float scaleFactor;
  int** tileValues;
  Cell** cellGrid;
  int spriteSize;
  sf::Vector2i dimension;
  sf::Vector2f centerOffset;
  void setCellGrid();
  void readCSV(string path, int** values);
public:
  Tilemap(sf::Texture ts,string path,float sf,int ss);
  ~Tilemap(){
    for(int i; i < dimension.x; i++){
      delete[] cellGrid[i];
    }
    delete[] cellGrid;
  }
  void draw(sf::RenderWindow&);
};
