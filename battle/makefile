test: test.o Character.o Battle.o
	g++ -o test test.o Character.o Battle.o -lsfml-window -lsfml-graphics -lsfml-system

test.o: Character.o Battle.o
	g++ -c test.cpp Character.o Battle.o

Battle.o: Character.o
	g++ -c Battle.cpp Character.o

Character.o:
	g++ -c Character.cpp
