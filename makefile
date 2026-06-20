all: game
game:
	g++ sfml.cc -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -O3 -march=native -flto=auto
