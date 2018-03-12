main: main.o Tilemap.h Tilemap.o
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system Tilemap.cpp Animation.cpp AnimatedSprite.cpp

main.o: main.cpp Tilemap.cpp Animation.cpp AnimatedSprite.cpp
	g++ -c main.cpp -std=c++11


