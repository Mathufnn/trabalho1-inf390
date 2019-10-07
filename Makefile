make: Tetris.o Window.o
	g++ Tetris.o Window.o -lglut -lGLU -lGL -o main.out

Tetris.o:
	g++ -c Tetris.cpp

jogoTetris.o:
	g++ -c Window.cpp
