all: game
game: ctral.cc
	g++ sfml.cc -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -O3 -march=native
