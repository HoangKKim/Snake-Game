#pragma once
#include <string>
#include <vector>
#include "screen.h"

using namespace std;

enum class Status {UP, DOWN, LEFT, RIGHT, ESC, PAUSE, EMPTY, ON, OFF, SAVE, SPEED_UP};

#define WidthGame      120
#define HeightGame     35
#define SPEEDFIRST     80
#define SPEEDLATER	   30

struct Information {
	string data;
	int x, y;     
	int ox, oy;  

	Information () {
		data = "";
		x = y = ox = oy = 0;
	}
};

struct User {
	char* name;
	size_t password;
	int level;
	int score;
	int time;
	int snakeLenght;
	int speed;
	int requirement;
	char* snakeData;
	int dirX, dirY;
	Information food;
	vector<Information> Snake;

	User() {
		level = score = snakeLenght = dirX = dirY = 0;
		password = 0, time = 0, speed = 0, requirement = 0;
		name = new char[20];
		snakeData = new char[100];
		Snake.clear();
	}
};

void init(vector<Information>&, Information&, Information&, bool&, int);

void moveSnake(vector<Information>&, Information, Information&, bool&, int&);

void drawSnake(vector<Information>&);

void mainLoop(Status&, Status&, vector<Information>&, Information&, Information&, double&, bool&, int&);

void playGame(string name, string& dateAndTime);

void randFood(Information &Food);

void loadGame();

int loadFileUserData();

void drawLosingSnake(vector<Information>& Snake);

void decorateBonus();

void coolDown();

void obstacle(int currentLevel);

void obstacle1(int currentLevel);

void obstacle2(int currentLevel);

void obstacle3(int currentLevel);

void saveGame();
