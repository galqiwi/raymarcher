all:
	g++ -O3 -pthread -std=c++17 `pkg-config --cflags --libs opencv` main.cpp -o main