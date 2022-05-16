all:
	g++ -std=c++20 main.cpp -I SDL2/include -L SDL2/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main