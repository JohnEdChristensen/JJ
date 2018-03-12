#include "Tilemap.h"
#include <sstream>
using namespace std;
Tilemap::Tilemap(sf::Texture ts,string path,float sf,int ss):
tileSheet(ts),scaleFactor(sf),spriteSize(ss){
    std::ifstream tilesIn(path.c_str());
    std::string line;
    std::getline(tilesIn, line);
    int xSize, ySize;
    std::stringstream sstream(line);
    sstream >> xSize >> ySize;
    dimension = sf::Vector2i(xSize,ySize);
    //initialize tileValues
    cout << "Initialize tileValues" << endl;
    tileValues = new int*[dimension.x];
    for(int i = 0; i < dimension.x; i++){
      tileValues[i] = new int[dimension.y];
    }
    readCSV(path, tileValues);
    centerOffset = sf::Vector2f(spriteSize/2.0f,spriteSize/2.0f);
    main.setTexture(tileSheet);
    main.setTextureRect(sf::IntRect(0,0,16,16));
    fill.setTexture(tileSheet);
    fill.setTextureRect(sf::IntRect(16,0,16,16));
    edge.setTexture(tileSheet);
    edge.setTextureRect(sf::IntRect(32,0,16,16));
    outerCorner.setTexture(tileSheet);
    outerCorner.setTextureRect(sf::IntRect(48,0,16,16));
    innerCorner.setTexture(tileSheet);
    innerCorner.setTextureRect(sf::IntRect(64,0,16,16));
    cellGrid = new Cell*[dimension.x];
    for(int i; i < dimension.x; i++){
      cellGrid[i] = new Cell[dimension.y];
    }
    setCellGrid();
}
void Tilemap::readCSV(string path, int** values){
  std::ifstream tilesIn(path.c_str());
  std::string line;
  std::getline(tilesIn, line);
  int value;
  int j = 0;

  while(std::getline(tilesIn,line)){
    std::stringstream ss(line);
    int i = 0;
    while (ss >> value){
      values[i][j] = value;
      if (ss.peek() == ',')
        ss.ignore();
      i++;
    }
    j++;
  }
}
void Tilemap::draw(sf::RenderWindow& window){
  for(size_t i=0; i < dimension.x; i++){
    for(size_t j=0; j < dimension.y; j++){
      cellGrid[i][j].sprite.setScale(scaleFactor,scaleFactor);
      window.draw(cellGrid[i][j].sprite);
    }
  }
}
void Tilemap::setCellGrid(){
  //set base tiles
  for(int i = 0; i < dimension.x; i++){
    for(int j = 0; j < dimension.y; j++){
      if(tileValues[i][j] == 1){
        cellGrid[i][j].sprite = main;
        cellGrid[i][j].a = 1;
        cellGrid[i][j].b = 1;
        cellGrid[i][j].c = 1;
        cellGrid[i][j].d = 1;

      }else if(tileValues[i][j] == 0){
        cellGrid[i][j].sprite = fill;
        cellGrid[i][j].a = 0;
        cellGrid[i][j].b = 0;
        cellGrid[i][j].c = 0;
        cellGrid[i][j].d = 0;
      }
      cellGrid[i][j].sprite.setPosition(i*spriteSize*scaleFactor,j*spriteSize*scaleFactor);

    }
  }
  //set edge tiles;
  for(int i = 0; i < dimension.x; i++){
    for(int j = 0; j < dimension.y; j++){
      if(tileValues[i][j] == 0){
        //top left
        cellGrid[i-1][j-1].d = 0;
        //top
        cellGrid[i][j-1].c = 0;
        cellGrid[i][j-1].d = 0;
        //top right
        cellGrid[i+1][j-1].c = 0;
        //right
        cellGrid[i+1][j].a = 0;
        cellGrid[i+1][j].c = 0;
        //bottom right
        cellGrid[i+1][j+1].a = 0;
        //bottom
        cellGrid[i][j+1].a = 0;
        cellGrid[i][j+1].b = 0;
        //bottom left
        cellGrid[i-1][j+1].b = 0;
        //left
        cellGrid[i-1][j].b = 0;
        cellGrid[i-1][j].d = 0;
      }
    }
  }
  for(int i = 0; i < dimension.x; i++){
    for(int j = 0; j < dimension.y; j++){
      if(tileValues[i][j] == 1){
        Cell cell = cellGrid[i][j];
        if(cell.a == 1 && cell.b == 1 && cell.c == 1 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(outerCorner.getTextureRect());
        }
        else if(cell.a == 1 && cell.b == 1 && cell.c == 0 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(outerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(90);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,0.0f);
        }
        else if(cell.a == 0 && cell.b == 1 && cell.c == 1 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(outerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(180);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,spriteSize*scaleFactor);
        }
        else if(cell.a == 1 && cell.b == 0 && cell.c == 1 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(outerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(-90);
          cellGrid[i][j].sprite.move(0,spriteSize*scaleFactor);
        }
        else if(cell.a == 1 && cell.b == 1 && cell.c == 0 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(edge.getTextureRect());
        }
        else if(cell.a == 0 && cell.b == 1 && cell.c == 0 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(edge.getTextureRect());
          cellGrid[i][j].sprite.setRotation(90);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,0.0f);
        }
        else if(cell.a == 0 && cell.b == 0 && cell.c == 1 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(edge.getTextureRect());
          cellGrid[i][j].sprite.setRotation(180);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,spriteSize*scaleFactor);
        }
        else if(cell.a == 1 && cell.b == 0 && cell.c == 1 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(edge.getTextureRect());
          cellGrid[i][j].sprite.setRotation(-90);
          cellGrid[i][j].sprite.move(0,spriteSize*scaleFactor);
        }
        else if(cell.a == 0 && cell.b == 0 && cell.c == 0 && cell.d == 1){
          cellGrid[i][j].sprite.setTextureRect(innerCorner.getTextureRect());
        }
        else if(cell.a == 0 && cell.b == 0 && cell.c == 1 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(innerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(90);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,0.0f);
        }
        else if(cell.a == 1 && cell.b == 0 && cell.c == 0 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(innerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(180);
          cellGrid[i][j].sprite.move(spriteSize*scaleFactor,spriteSize*scaleFactor);
        }
        else if(cell.a == 0 && cell.b == 1 && cell.c == 0 && cell.d == 0){
          cellGrid[i][j].sprite.setTextureRect(innerCorner.getTextureRect());
          cellGrid[i][j].sprite.setRotation(-90);
          cellGrid[i][j].sprite.move(0,spriteSize*scaleFactor);
        }
        else if(cell.a == 0 && cell.b == 0 && cell.c == 0 && cell.d == 0){
            cellGrid[i][j].sprite.setTextureRect(fill.getTextureRect());
        }
        else if(!(cell.a == 1 && cell.b == 1 && cell.c == 1 && cell.d == 1)){
          cellGrid[i][j].sprite.setTextureRect(innerCorner.getTextureRect());
        }
      }
    }
  }
}
