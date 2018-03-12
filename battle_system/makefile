test: test.o Character.o Battle.o Animation.o AnimatedSprite.o Tilemap.o
	g++ -o test test.o Character.o Battle.o Animation.o AnimatedSprite.o Tilemap.o -lsfml-window -lsfml-graphics -lsfml-system

%.o: %.cpp
	g++ -c $<

