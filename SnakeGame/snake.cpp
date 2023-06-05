#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "snake.h"
#include "graphic.h"
#include "gameSound.h"
#include "level.h"
#include "menu.h"

#include <vector>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <future>
#include <ctime>

std::string studentIds = "21127003211276482112709021127493";
int position = 8;
string colorXY[205][85], userName;
size_t password;
short snakeColor;
vector<Player> savePlayers;
Status Sound;
double Speed = SPEEDFIRST;
int requirement[] = { 3, 3, 4, 4, 5, 99999 };
int currRequirement, currentLevel;
time_t now;
int bonus = 5;
int maxTime = 20;
int tmp = 20;
bool saved = false, loaded = false;


void randFood(Information& Food) {
	Food.x = 5 + rand() % (WidthGame - 5);
	Food.y = 5 + rand() % (HeightGame - 5);

	while ((colorXY[Food.x][Food.y] == "DANGER") || ((Food.y == 23 || Food.y == 20 || Food.x == 63 || Food.x == 72) && currentLevel == 4)) {
		srand((unsigned int)time(0));
		Food.x = 5 + rand() % (WidthGame - 5);
		Food.y = 5 + rand() % (HeightGame - 5);
	}
	colorXY[Food.x][Food.y] = "FOOD_INC";
}

void init(vector<Information>& Snake, Information& Food, Information& Direction, bool& endGame, int score) {
	Information Body;
	endGame = false;

	gotoXY(147, 5);
	colorText("Score: ", RED);
	cout << score;
	gotoXY(143, 6);
	colorText("Requirement: ", RED);
	cout << currRequirement << " / " << requirement[currentLevel];
	gotoXY(145, 7);
	colorText("Speed: ", RED);
	cout << (int)-Speed + 120 << " km/h";

	drawInGate(7, 5);
	for (int i = 0; i < 8; i++) {
		Body.data = studentIds[i];
		Body.x = 11; Body.y = 3;
		Snake.push_back(Body);
	}

	/*randFood(Food);
	gotoXY(Food.x, Food.y);
	colorText(254, snakeColor);*/

	// Init direction
	Direction.x = 0;
	Direction.y = 1;
}

void moveSnake(vector<Information>& Snake, Information dir, Information& Food, bool& endGame, int& score) {
	Information Add;
	size_t size = Snake.size();

	for (size_t i = 0; i < size_t(size); i++) {
		if (i == 0) {
			// Move the head
			Snake[0].ox = Snake[0].x;
			Snake[0].oy = Snake[0].y;

			Snake[0].x += dir.x;
			Snake[0].y += dir.y;
		}
		else {
			// Move the body
			Snake[i].ox = Snake[i].x;
			Snake[i].oy = Snake[i].y;

			Snake[i].x = Snake[i - 1].ox;
			Snake[i].y = Snake[i - 1].oy;
		}

		// Pass the width and height
		//if (Snake[i].x >= WidthGame) {
		//	Snake[i].x = 0;
		//}

		//if (Snake[i].x < 0) {
		//	Snake[i].x = WidthGame - 1;
		//}
		//if (Snake[i].y >= HeightGame) { 
		//	Snake[i].y = 0; 
		//}
		//if (Snake[i].y < 0) {
		//	Snake[i].y = HeightGame - 1;
		//}
		int checkSnake = 0;
		for (int i = 0; i < Snake.size(); i++) {
			if (colorXY[Snake[i].x][Snake[i].y] == "DANGER") checkSnake = 1;
		}

		if (colorXY[Snake[i].x][Snake[i].y] == "DANGER") {
			position = 8;
			currRequirement = 0;
			Speed = SPEEDFIRST;
			currentLevel = 0;
			maxTime = 20;
			endGame = true;
		}

		// Check seft-hitting
		if (i != 0 && (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y)) {
			position = 8;
			currRequirement = 0;
			currentLevel = 0;
			Speed = SPEEDFIRST;
			maxTime = 20;
			gotoXY(Food.x, Food.y);
			cout << " ";
			endGame = true;
		}
	}

	// Eat food
	if (colorXY[Snake[0].x][Snake[0].y] == "FOOD_INC") {
		colorXY[Food.x][Food.y] = "SAFE";

		if (Sound == Status::OFF) {
			playSound(L"resources/eatfood.wav");
		}

		if (position == studentIds.size() - 1) {
			position = 0;
		}

		Add.data = studentIds[position++];
		Add.x = Snake[size - 1].ox;
		Add.y = Snake[size - 1].oy;
		Snake.push_back(Add);

		score += 100;
		currRequirement += 1;

		if (currRequirement < requirement[currentLevel]) {
			// Creat new food
			randFood(Food);

			gotoXY(Food.x, Food.y);
			colorXY[Food.x][Food.y] = "FOOD_INC";
			colorText(254, snakeColor);
		}
	}
	else if (colorXY[Snake[0].x][Snake[0].y] == "FOOD_BINC") { // Bonus increase, increase length and score
		colorXY[Food.x][Food.y] = "SAFE";

		if (Sound == Status::OFF) {
			playSound(L"resources/eatfood.wav");
		}

		if (position == studentIds.size() - 1) {
			position = 0;
		}

		Add.data = studentIds[position++];
		Add.x = Snake[size - 1].ox;
		Add.y = Snake[size - 1].oy;
		Snake.push_back(Add);

		score += 100;
		currRequirement += 1;
		//gotoXY(147, 5);
		//colorText("Score: ", RED);
		//cout << score;
	}
	else if (colorXY[Snake[0].x][Snake[0].y] == "FOOD_BST") { // Just increase score
		colorXY[Food.x][Food.y] = "SAFE";

		if (Sound == Status::OFF) {
			playSound(L"resources/eatfood.wav");
		}

		score += 100;
		currRequirement += 1;
		//gotoXY(147, 5);
		//colorText("Score: ", RED);
		//cout << score;
	}
}

void drawSnake(vector<Information>& Snake) {
	size_t size = Snake.size();
	textColor(snakeColor);
	for (int i = 0; i < size; i++) {
		gotoXY(Snake[i].x, Snake[i].y);
		cout << Snake[i].data;
	}
	gotoXY(Snake[size - 1].ox, Snake[size - 1].oy);
	cout << " ";
}

void print() {
	for (int i = 0; i < 100; ++i) {
		gotoXY(10, 10);
		cout << i;
		Sleep(100);
	}
}

bool upSpeed = false;

void mainLoop(
	Status& StatusMove, Status& StatusGame,
	vector<Information>& Snake,
	Information& Direction, Information& Food,
	double& Speed, bool& endGame, int& score
) {
	gotoXY(147, 5);
	colorText("Score: ", RED);
	cout << score;
	gotoXY(143, 6);
	colorText("Requirement: ", RED);
	cout << currRequirement << " / " << requirement[currentLevel];
	gotoXY(145, 7);
	colorText("Speed: ", RED);
	cout << (int)-Speed + 120 << " km/h";
	moveSnake(Snake, Direction, Food, endGame, score);
	obstacle(currentLevel);
	obstacle1(currentLevel);
	obstacle2(currentLevel);
	obstacle3(currentLevel);

	gotoXY(10, 10);
	//cout << currentLevel << ' ' << bonus;
	if (currentLevel == bonus) {
		gotoXY(10, 10);
		time_t currSec = time(0);
		if (maxTime != 0) {
			maxTime = tmp - (int)(currSec - now);
		}
		coolDown();
	}

	if (_kbhit()) {
		int key = _getch();

		if (key < 97 && key > 65) { // A - Z
			key += 32;
		}

		if (key == 'a') {
			StatusMove = Status::LEFT;
		}
		else if (key == 'd') {
			StatusMove = Status::RIGHT;
		}
		else if (key == 'w') {
			StatusMove = Status::UP;
		}
		else if (key == 's') {
			StatusMove = Status::DOWN;
		}
		else if (key == 'l') {
			StatusGame = Status::SAVE;
		}
		else if (key == 32) { // Space - pause game
			pauseGame();
			StatusGame = Status::PAUSE;
		}
		else if (key == 27) {
			StatusGame = Status::ESC; // ESC - Exit game
		}
		else if (key == 13) {
			StatusGame = Status::SPEED_UP;
		}
	}

	if (StatusMove == Status::LEFT) {
		if (Direction.x != 1) {
			Direction.x = -1;
			Direction.y = 0;
		}
	}
	else if (StatusMove == Status::RIGHT) {
		if (Direction.x != -1) {
			Direction.x = 1;
			Direction.y = 0;
		}
	}
	else if (StatusMove == Status::UP) {
		if (Direction.y != 1) {
			Direction.y = -1;
			Direction.x = 0;
		}
	}
	else if (StatusMove == Status::DOWN) {
		if (Direction.y != -1) {
			Direction.y = 1;
			Direction.x = 0;
		}
	}

	if (StatusGame == Status::PAUSE) {
		while (true) {
			if (_kbhit()) { // Wait for pressing space again
				int key = _getch();

				if (key == 32) {
					system("cls");
					level[currentLevel]();

					if (currRequirement != requirement[currentLevel]) {
						gotoXY(Food.x, Food.y);
						colorXY[Food.x][Food.y] = "FOOD_INC";
						colorText(254, snakeColor);
					}

					if (currRequirement == requirement[currentLevel]) {
						drawOutGate(3, 121, 38);
					}

					StatusGame = Status::EMPTY;
					break;
				}
				else {
					continue;
				}
			}
		}
	}

	if (StatusGame == Status::ESC) {
		position = 8;
		currRequirement = 0;
		endGame = true;
	}

	if (StatusGame == Status::SPEED_UP) {
		if (upSpeed == true) {
			Speed += 20;
			upSpeed = false;
			StatusGame = Status::EMPTY;
		}
		else {
			Speed -= 20;
			upSpeed = true;
			StatusGame = Status::EMPTY;
		}
	}

	if (StatusGame == Status::SAVE) {
		std::hash <std::string> hash;
		cout << "Enter sercurity key: ";
		string key;

		if (!loaded) {
			fillPassword(key);
			password = hash(key);
		}

		ofstream fOut;
		fOut.open("saveData.txt", ios::app);
		fOut << "\n\nUser: " << userName << "\n";
		fOut << "Password: " << password << "\n";
		fOut << "Level: " << currentLevel + 1 << "\n";
		fOut << "Length: " << Snake.size() << "\n";
		fOut << "Snake Data: ";
		for (int i = 0; i < Snake.size(); ++i) {
			fOut << Snake[i].data;
		}
		fOut << "\n";
		fOut << "Snake Position: ";
		for (int i = 0; i < Snake.size(); ++i) {
			fOut << Snake[i].x << ' ' << Snake[i].y << ' ';
		}
		fOut << "\n";
		fOut << "Direction: " << Direction.x << ' ' << Direction.y << "\n";
		fOut << "Requirement: " << currRequirement << "\n";
		fOut << "Speed: " << Speed << "\n";

		if (currentLevel == bonus) {
			fOut << "Score: " << score << "\n";
		}
		else {
			fOut << "Food position: " << Food.x << ' ' << Food.y << "\n";
			fOut << "Score: " << score;
		}
		if (currentLevel == bonus) {
			fOut << "Time: " << maxTime;
		}

		fOut.close();

		position = 8;
		currRequirement = 0;
		maxTime = 20;
		tmp = 20;

		saveGame();
		saved = true;
		endGame = true;
	}
}

void playGame(string name, string& dateAndTime) {
	system("cls");
	loadingGameGraphic();
	system("cls");

	userName = name;
	upSpeed = false;
	vector<Information> Snake;
	Information Direction, Food;
	Status StatusMove, StatusGame;
	string oldSnake = "";

	srand((unsigned int)time(0));

	saved = false;
	int score = 0;
	bool endGame = false, isDrawGate = false;

	currentLevel = 0;
	currRequirement = 0;

	initLevel();

	level[currentLevel]();

	init(Snake, Food, Direction, endGame, score);

	int cal = false;

	while (!endGame) {
		Sleep(Speed);
		mainLoop(StatusMove, StatusGame, Snake, Direction, Food, Speed, endGame, score);
		drawSnake(Snake);

		int xStart = Snake[0].x;
		int yStart = Snake[0].y;

		if (colorXY[xStart][yStart] == "SAFE") {
			oldSnake.resize(Snake.size());
			for (int i = 0; i < Snake.size(); ++i) {
				oldSnake[i] = (Snake[i].data[0]);
			}
		}

		if (colorXY[xStart][yStart] == "PASS" && Snake.size() > 1) {
			Snake.erase(Snake.begin());
		}

		int xEnd = Snake[Snake.size() - 1].x;
		int yEnd = Snake[Snake.size() - 1].y;

		if (colorXY[xEnd][yEnd] == "DONE") {
			clearInGate(7, 5);
			randFood(Food);
			gotoXY(Food.x, Food.y);
			colorText(254, snakeColor);
		}

		if ((maxTime == 0 || currRequirement == requirement[currentLevel]) && !isDrawGate) {
			if (currentLevel < 2) {
				drawOutGate(3, 121, 38);
			}
			else if (currentLevel < 4) {
				drawOutGate(2, 121, 38);
			}
			else {
				drawOutGate(1, 121, 38);
			}
			isDrawGate = true;
		}

		if (currentLevel == bonus && !cal) {
			now = time(0);
			cal = true;
		}

		if (maxTime == 0) {
			for (int i = 5; i <= WidthGame; ++i) {
				for (int j = 5; j <= HeightGame; ++j) {
					if (colorXY[i][j] == "FOOD_BINC" || colorXY[i][j] == "FOOD_BST" || colorXY[i][j] == "FOOD_INC") {
						gotoXY(i, j);
						colorXY[i][j] = "SAFE";
						colorText(254, BACKGROUND_COLOR);
					}
				}
			}
			gotoXY(Food.x, Food.y);
			colorXY[Food.x][Food.y] = "SAFE";
			colorText(254, BACKGROUND_COLOR);
		}

		if ((maxTime == 0 || currRequirement == requirement[currentLevel]) && colorXY[xEnd][yEnd] == "PASS") {
			isDrawGate = false;
			system("cls");

			if (maxTime == 0) {
				maxTime = 20;
			}

			if (upSpeed == true) {
				Speed += 20;
				upSpeed = false;
				StatusGame = Status::EMPTY;
			}
			else {
				Speed -= 20;
				upSpeed = true;
				StatusGame = Status::EMPTY;
			}

			if (currentLevel <= bonus - 1) {
				++currentLevel;
				level[currentLevel]();
				if (Speed > 30) Speed -= 10;
				else Speed = Speed / 1.25;
			}
			else {
				currentLevel = 0;
				level[currentLevel]();
				if (Speed > 30) Speed -= 10;
				else Speed = Speed / 1.25;
			}

			drawInGate(7, 5);

			Sleep(2000);

			currRequirement = 0;
			//score = 0;

			Snake.resize(oldSnake.size());
			for (int i = 0; i < oldSnake.size(); ++i) {
				Snake[i].data = oldSnake[i];
				Snake[i].x = 11;
				Snake[i].y = 3;
			}

			Snake[0].ox = Snake[0].x;
			Snake[0].oy = Snake[0].y;

			Snake[0].x = 11;
			Snake[0].y = 3;

			for (size_t i = 1; i < Snake.size(); ++i) {
				Snake[i].x = Snake[i - 1].x;
				Snake[i].y = Snake[i - 1].y;
			}

			StatusMove = Status::DOWN;
			Direction.x = 0;
			Direction.y = 1;

			if (currentLevel == bonus) {
				now = time(0);
			}

			mainLoop(StatusMove, StatusGame, Snake, Direction, Food, Speed, endGame, score);
			drawSnake(Snake);
		}

	}

	if (!saved) {
		// end game
		while (true) {
			playSoundLoop(L"resources/losegame.wav");
			drawLosingSnake(Snake);
			deleteBorder();
			turnOffSound();
			break;
		}

		if (Sound == Status::ON) {
			playSoundLoop(L"resources/backgroundmusic.wav");
		}

		Sleep(500);
		loseGame(name, dateAndTime);
	}

	time_t now = time(0);
	dateAndTime = ctime(&now);
	dateAndTime.pop_back();

	Player t;
	t.score = score;
	t.name = name;
	t.dateAndTime = dateAndTime;
	savePlayers.push_back(t);
	ofstream fileout;

	fileout.open("saveScore.txt", ios::app);
	if (fileout.fail() == true) {
		cout << "File cannot be found";
	}
	else {
		fileout << endl << t.score << endl;
		fileout << t.name << endl;
		fileout << t.dateAndTime;
	}
}

extern User user[100];

int loadFileUserData() {
	FILE* file;
	fopen_s(&file, "saveData.txt", "r");
	int cnt = 0;

	for (int i = 0; i < 100; ++i) {
		user[i].Snake.clear();
	}

	if (file != nullptr) {
		while (!feof(file)) {
			fscanf_s(file, "User: %s\n", user[cnt].name, 20);
			fscanf_s(file, "Password: %lld\n", &user[cnt].password);
			//cout << user[cnt].password << ' ' << cnt << "\n\n";
			fscanf_s(file, "Level: %d\n", &user[cnt].level);
			user[cnt].level--;

			fscanf_s(file, "Length: %d\n", &user[cnt].snakeLenght);

			fscanf_s(file, "Snake Data: %s\n", user[cnt].snakeData, 100);

			fscanf_s(file, "Snake Position: ");
			Information data;
			for (int i = 0; i < user[cnt].snakeLenght; ++i) {
				int x = 0, y = 0;
				fscanf_s(file, "%d %d", &x, &y);
				data.data = user[cnt].snakeData[i];
				data.x = x;
				data.y = y;
				user[cnt].Snake.push_back(data);
			}

			fscanf_s(file, "\nDirection: %d %d", &user[cnt].dirX, &user[cnt].dirY);
			fscanf_s(file, "\nRequirement: %d", &user[cnt].requirement);
			fscanf_s(file, "\nSpeed: %d\n", &user[cnt].speed);

			if (user[cnt].level != bonus) {
				fscanf_s(file, "Food position: %d %d\n", &user[cnt].food.x, &user[cnt].food.y);
			}

			if (user[cnt].level == bonus) {
				fscanf_s(file, "Score: %d\n", &user[cnt].score);
				fscanf_s(file, "Time: %d\n\n", &user[cnt].time);
			}
			else {
				fscanf_s(file, "Score: %d\n\n", &user[cnt].score);
			}

			++cnt;
		}
		fclose(file);
	}
	return cnt;
}

void deleteElement(int pos, int &cnt) {
	if (cnt >= 2) {
		for (int i = pos; i < cnt - 1; i++) {
			user[i] = user[i + 1];
		}
	}
	--cnt;

	ofstream fOut;
	fOut.open("saveData.txt", ios::out);
	for (int i = 0; i < cnt; ++i) {
		if (i != 0) {
			fOut << "\n";
		}

		fOut << "User: " << user[i].name << "\n";
		fOut << "Password: " << user[i].password << "\n";
		fOut << "Level: " << user[i].level + 1 << "\n";
		fOut << "Length: " << user[i].snakeLenght << "\n";
		fOut << "Snake Data: ";
		for (int j = 0; j < user[i].snakeLenght; ++j) {
			fOut << user[i].snakeData[j];
		}
		fOut << "\n";
		fOut << "Snake Position: ";
		for (int j = 0; j < user[i].snakeLenght; ++j) {
			fOut << user[i].Snake[j].x << ' ' << user[i].Snake[j].y << ' ';
		}
		fOut << "\n";
		fOut << "Direction: " << user[i].dirX << ' ' << user[i].dirY << "\n";
		fOut << "Requirement: " << user[i].requirement << "\n";
		fOut << "Speed: " << user[i].speed << "\n";

		if (user[i].level != bonus) {
			fOut << "Food position: " << user[i].food.x << ' ' << user[i].food.y << "\n";
		}

		if (i != cnt - 1) {
			fOut << "Score: " << user[i].score << "\n";

			if (user[i].level == bonus) {
				fOut << "Time: " << user[i].time << "\n";
			}
		}
		else {
			fOut << "Score: " << user[i].score;

			if (user[i].level == bonus) {
				fOut << "Time: " << user[i].time;
			}
		}

	}
	fOut.close();
}

void loadGame() {
	std::hash <std::string> hash;
	int cnt = loadFileUserData();

	loaded = true;
	upSpeed = false;
	string uName;
	int pos = -1;

	string uPass;
	loadGameGraphic(uName, uPass);
	size_t uPassHash = hash(uPass);
	password = uPassHash;

	userName = uName;

	for (int i = 0; i < cnt; ++i) {
		if (user[i].name == uName && user[i].password == uPassHash) {
			pos = i;
		}
	}

	if (pos == -1) {
		gotoXY(40, 8);
		textColor(RED);
		cout << "Invalid user name or password!";
		gotoXY(40, 9);
		cout << "You will be brought into main in 3s";
		Sleep(1000);
		gotoXY(40, 9);
		cout << "You will be brought into main in 2s";
		Sleep(1000);
		gotoXY(40, 9);
		cout << "You will be brought into main in 1s";
		Sleep(1000);
		gotoXY(40, 9);
		cout << "You will be brought into main in 0s";
		Sleep(1000);
		return;
	}
	system("cls");
	loadingGameGraphic();
	system("cls");

	vector<Information> Snake = user[pos].Snake;
	Information Direction, Food;
	Status StatusMove, StatusGame;
	string oldSnake = "";

	srand((unsigned int)time(0));

	double Speed = user[pos].speed;
	saved = false;
	int score = user[pos].score;
	bool endGame = false, isDrawGate = false;

	currentLevel = user[pos].level;
	currRequirement = user[pos].requirement;

	initLevel();

	level[currentLevel]();

	//init(Snake, Food, Direction, endGame, score);

	if (currRequirement < requirement[currentLevel]) {
		gotoXY(user[pos].food.x, user[pos].food.y);
		colorXY[user[pos].food.x][user[pos].food.y] = "FOOD_INC";
		colorText(254, snakeColor);
	}

	Food.x = user[pos].food.x;
	Food.y = user[pos].food.y;

	Direction.x = user[pos].dirX;
	Direction.y = user[pos].dirY;

	drawSnake(Snake);
	Sleep(1000);

	tmp = user[pos].time;

	deleteElement(pos, cnt);

	int cal = false;

	while (!endGame) {
		Sleep(Speed);
		mainLoop(StatusMove, StatusGame, Snake, Direction, Food, Speed, endGame, score);
		drawSnake(Snake);

		int xStart = Snake[0].x;
		int yStart = Snake[0].y;

		if (colorXY[xStart][yStart] == "SAFE") {
			oldSnake.resize(Snake.size());
			for (int i = 0; i < Snake.size(); ++i) {
				oldSnake[i] = (Snake[i].data[0]);
			}
		}

		if (colorXY[xStart][yStart] == "PASS" && Snake.size() > 1) {
			Snake.erase(Snake.begin());
		}

		int xEnd = Snake[Snake.size() - 1].x;
		int yEnd = Snake[Snake.size() - 1].y;

		if (colorXY[xEnd][yEnd] == "DONE") {
			clearInGate(7, 5);
		}

		if (currentLevel == bonus && !cal) {
			now = time(0);
			cal = true;
		}

		if ((maxTime == 0 || currRequirement == requirement[currentLevel]) && !isDrawGate) {
			if (currentLevel < 2) {
				drawOutGate(3, 121, 38);
			}
			else if (currentLevel < 4) {
				drawOutGate(2, 121, 38);
			}
			else {
				drawOutGate(1, 121, 38);
			}
			isDrawGate = true;
		}

		if (maxTime == 0) {
			for (int i = 5; i <= WidthGame; ++i) {
				for (int j = 5; j <= HeightGame; ++j) {
					if (colorXY[i][j] == "FOOD_BINC" || colorXY[i][j] == "FOOD_BST" || colorXY[i][j] == "FOOD_INC") {
						gotoXY(i, j);
						colorXY[i][j] = "SAFE";
						colorText(254, BACKGROUND_COLOR);
					}
				}
			}
			gotoXY(Food.x, Food.y);
			colorXY[Food.x][Food.y] = "SAFE";
			colorText(254, BACKGROUND_COLOR);
		}

		if ((maxTime == 0 || currRequirement == requirement[currentLevel]) && colorXY[xEnd][yEnd] == "PASS") {
			isDrawGate = false;
			system("cls");

			tmp = 20;

			if (maxTime == 0) {
				maxTime = 20;
			}

			if (upSpeed == true) {
				Speed += 20;
				upSpeed = false;
				StatusGame = Status::EMPTY;
			}
			else {
				Speed -= 20;
				upSpeed = true;
				StatusGame = Status::EMPTY;
			}

			if (currentLevel <= bonus - 1) {
				++currentLevel;
				level[currentLevel]();
				if (Speed > 30) Speed -= 10;
				else Speed = Speed / 1.25;
			}
			else {
				currentLevel = 0;
				level[currentLevel]();
				if (Speed > 30) Speed -= 10;
				else Speed = Speed / 1.25;
			}

			drawInGate(7, 5);

			Sleep(2000);

			currRequirement = 0;
			//score = 0;

			Snake.resize(oldSnake.size());
			for (int i = 0; i < oldSnake.size(); ++i) {
				Snake[i].data = oldSnake[i];
				Snake[i].x = 11;
				Snake[i].y = 3;
			}

			Snake[0].ox = Snake[0].x;
			Snake[0].oy = Snake[0].y;

			Snake[0].x = 11;
			Snake[0].y = 3;

			for (size_t i = 1; i < Snake.size(); ++i) {
				Snake[i].x = Snake[i - 1].x;
				Snake[i].y = Snake[i - 1].y;
			}

			StatusMove = Status::DOWN;
			Direction.x = 0;
			Direction.y = 1;

			randFood(Food);
			gotoXY(Food.x, Food.y);
			colorText(254, snakeColor);

			if (currentLevel == bonus) {
				now = time(0);
			}

			mainLoop(StatusMove, StatusGame, Snake, Direction, Food, Speed, endGame, score);
			drawSnake(Snake);
		}

	}

	string pName;
	time_t now = time(0);
	string dateAndTime = ctime(&now);
	dateAndTime.pop_back();

	for (int i = 0; i < strlen(user[pos].name); ++i) {
		pName.push_back(user[pos].name[i]);
	}

	if (!saved) {
		// end game
		while (true) {
			playSoundLoop(L"resources/losegame.wav");
			drawLosingSnake(Snake);
			deleteBorder();
			turnOffSound();
			break;
		}

		if (Sound == Status::ON) {
			playSoundLoop(L"resources/backgroundmusic.wav");
		}

		Sleep(500);
		loseGame(pName, dateAndTime);
	}

	ofstream fileout;
	fileout.open("saveScore.txt", ios::app);
	
	if (fileout.fail() == true) {
		cout << "File cannot be found";
	}
	else {
		fileout << endl << score << endl;
		fileout << pName << endl;
		fileout << dateAndTime;
	}
}

void drawLosingSnake(vector<Information>& Snake) {
	size_t size = Snake.size();
	for (int i = 0; i < size; i++) {
		if (i % 2 == 0)
		{
			textColor(snakeColor);
			gotoXY(Snake[i].x, Snake[i].y);
			cout << Snake[i].data;
			Sleep(30);
		}
		else
		{
			textColor(WHITE);
			gotoXY(Snake[i].x, Snake[i].y);
			cout << Snake[i].data;
			Sleep(30);
		}
	}

	for (int i = 0; i < size; i++) {
		if (i % 2 != 0)
		{
			textColor(snakeColor);
			gotoXY(Snake[i].x, Snake[i].y);
			cout << Snake[i].data;
			Sleep(30);
		}
		else
		{
			textColor(WHITE);
			gotoXY(Snake[i].x, Snake[i].y);
			cout << Snake[i].data;
			Sleep(30);
		}
	}

	for (int i = 0; i < size; i++) {
		textColor(GRAY);
		gotoXY(Snake[i].x, Snake[i].y);
		cout << Snake[i].data;
		Sleep(30);
	}

	gotoXY(Snake[size - 1].ox, Snake[size - 1].oy);
	cout << " ";
}

void decorateBonus() {
	Screen gameDisplay;
	gameDisplay.draw.retangle({ 135, 10 }, { 17, 0 }, RED, 1, colorXY);

	textColor(6);
	int col1 = 138, row1 = 12;
	gotoXY(col1, row1++);
	wcout << L"██████ ";
	gotoXY(col1, row1++);
	wcout << L"██   ██";
	gotoXY(col1, row1++);
	wcout << L"██████ ";
	gotoXY(col1, row1++);
	wcout << L"██   ██";
	gotoXY(col1, row1++);
	wcout << L"██████ ";
	row1++;
	gotoXY(col1, row1++);
	wcout << L" ██████ ";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L" ██████ ";
	row1++;
	gotoXY(col1, row1++);
	wcout << L"███    ██";
	gotoXY(col1, row1++);
	wcout << L"████   ██";
	gotoXY(col1, row1++);
	wcout << L"██ ██  ██";
	gotoXY(col1, row1++);
	wcout << L"██  ██ ██";
	gotoXY(col1, row1++);
	wcout << L"██   ████";
	row1++;
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L"██    ██";
	gotoXY(col1, row1++);
	wcout << L" ██████ ";
	row1++;
	gotoXY(col1, row1++);
	wcout << L"███████ ";
	gotoXY(col1, row1++);
	wcout << L"██     ";
	gotoXY(col1, row1++);
	wcout << L"███████ ";
	gotoXY(col1, row1++);
	wcout << L"     ██ ";
	gotoXY(col1, row1++);
	wcout << L"███████ ";
}

void coolDown() {
	int col2 = 153, row2 = 20;
	if (maxTime == 20) {
		gotoXY(col2, row2++);
		wcout << L"██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██╗";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝";
		gotoXY(col2, row2++);
		wcout << L"██╔═══╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗";
		gotoXY(col2, row2++);
		wcout << L"╚══════╝";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
	}
	if (maxTime == 19) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" █████╗  ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚██████║ ";
		gotoXY(col2, row2++);
		wcout << L" ╚═══██║ ";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L" ╚════╝  ";
	}
	if (maxTime == 18) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" █████╗  ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚█████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚█████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L" ╚════╝  ";
	}
	if (maxTime == 17) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██║ ";
		gotoXY(col2, row2++);
		wcout << L"    ██╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"   ██╔╝  ";
		gotoXY(col2, row2++);
		wcout << L"   ██║   ";
		gotoXY(col2, row2++);
		wcout << L"   ╚═╝   ";
	}
	if (maxTime == 16) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔════╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═══██╗";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
	}
	if (maxTime == 15) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔════╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██║ ";
		gotoXY(col2, row2++);
		wcout << L"███████║ ";
		gotoXY(col2, row2++);
		wcout << L"╚══════╝ ";
	}
	else if (maxTime == 14) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";


		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██╗  ██╗";
		gotoXY(col2, row2++);
		wcout << L"██║  ██║";
		gotoXY(col2, row2++);
		wcout << L"███████║";
		gotoXY(col2, row2++);
		wcout << L"╚════██║";
		gotoXY(col2, row2++);
		wcout << L"     ██║";
		gotoXY(col2, row2++);
		wcout << L"     ╚═╝";
	}
	else if (maxTime == 13) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";


		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██╗";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═══██╗";
		gotoXY(col2, row2++);
		wcout << L"██████╔╝";
		gotoXY(col2, row2++);
		wcout << L"╚═════╝ ";
	}
	else if (maxTime == 12) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██╗";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝";
		gotoXY(col2, row2++);
		wcout << L"██╔═══╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗";
		gotoXY(col2, row2++);
		wcout << L"╚══════╝";
	}
	else if (maxTime == 11) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";


		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";
	}
	else if (maxTime == 10) {
		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";


		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
	}
	else if (maxTime == 1) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██╗     ";
		gotoXY(col2, row2++);
		wcout << L"███║     ";
		gotoXY(col2, row2++);
		wcout << L"╚██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ██║     ";
		gotoXY(col2, row2++);
		wcout << L" ╚═╝     ";
	}
	else if (maxTime == 2) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██████╗  ";
		gotoXY(col2, row2++);
		wcout << L"╚════██╗ ";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═══╝  ";
		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚══════╝ ";
	}
	else if (maxTime == 3) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██████╗  ";
		gotoXY(col2, row2++);
		wcout << L"╚════██╗ ";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L" ╚═══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"██████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"╚═════╝  ";
	}
	else if (maxTime == 4) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"██╗  ██╗ ";
		gotoXY(col2, row2++);
		wcout << L"██║  ██║ ";
		gotoXY(col2, row2++);
		wcout << L"███████║ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██║ ";
		gotoXY(col2, row2++);
		wcout << L"     ██║ ";
		gotoXY(col2, row2++);
		wcout << L"     ╚═╝ ";
	}
	else if (maxTime == 5) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔════╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██║ ";
		gotoXY(col2, row2++);
		wcout << L"███████║ ";
		gotoXY(col2, row2++);
		wcout << L"╚══════╝ ";
	}
	else if (maxTime == 6) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔════╝ ";
		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═══██╗";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
	}
	else if (maxTime == 7) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L"███████╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚════██║ ";
		gotoXY(col2, row2++);
		wcout << L"    ██╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"   ██╔╝  ";
		gotoXY(col2, row2++);
		wcout << L"   ██║   ";
		gotoXY(col2, row2++);
		wcout << L"   ╚═╝   ";
	}
	else if (maxTime == 8) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" █████╗  ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚█████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚█████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L" ╚════╝  ";
	}
	else if (maxTime == 9) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" █████╗  ";
		gotoXY(col2, row2++);
		wcout << L"██╔══██╗ ";
		gotoXY(col2, row2++);
		wcout << L"╚██████║ ";
		gotoXY(col2, row2++);
		wcout << L" ╚═══██║ ";
		gotoXY(col2, row2++);
		wcout << L" █████╔╝ ";
		gotoXY(col2, row2++);
		wcout << L" ╚════╝  ";
	}
	else if (maxTime == 0) {

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";

		row2 += 1;

		gotoXY(col2, row2++);
		wcout << L" ██████╗ ";
		gotoXY(col2, row2++);
		wcout << L"██╔═████╗";
		gotoXY(col2, row2++);
		wcout << L"██║██╔██║";
		gotoXY(col2, row2++);
		wcout << L"████╔╝██║";
		gotoXY(col2, row2++);
		wcout << L"╚██████╔╝";
		gotoXY(col2, row2++);
		wcout << L" ╚═════╝ ";
	}
}


void saveGame() {
	saveGameGraphic();
	int pos = -1;

	if (pos == -1) {
		textColor(RED);
		gotoXY(40, 11);
		cout << "You will be brought into main in 3s";
		Sleep(1000);
		gotoXY(40, 11);
		cout << "You will be brought into main in 2s";
		Sleep(1000);
		gotoXY(40, 11);
		cout << "You will be brought into main in 1s";
		Sleep(1000);
		gotoXY(40, 11);
		cout << "You will be brought into main in 0s";
		Sleep(1000);
		return;
	}
}

void obstacle(int currentLevel) {
	static int x = 8, y = 23;
	static int tempx;
	static int t = 1;
	if (currentLevel == 4) {
		if (t == 1) {
			textColor(BLUE);
			gotoXY(x + 3, y);
			cout << (char)16;
			colorXY[x + 3][y] = "DANGER";
			gotoXY(x + 2, y);
			cout << (char)254;
			colorXY[x + 2][y] = "DANGER";
			gotoXY(x + 1, y);
			cout << (char)254;
			colorXY[x + 1][y] = "DANGER";
			gotoXY(x, y);
			cout << (char)254;
			colorXY[x][y] = "DANGER";
			gotoXY(x - 1, y);
			cout << (char)254;
			colorXY[x - 1][y] = "DANGER";
			gotoXY(x - 2, y);
			cout << " ";
			colorXY[x - 2][y] = "SAFE";
			x++;
			if (x == 128) {
				t = 2;
				gotoXY(x + 2, y);
				cout << " ";

			}
		}
		if (t == 2) {
			textColor(BLUE);
			gotoXY(x - 3, y);
			colorXY[x - 3][y] = "DANGER";
			cout << (char)17;
			gotoXY(x - 2, y);
			cout << (char)254;
			colorXY[x - 2][y] = "DANGER";
			gotoXY(x - 1, y);
			cout << (char)254;
			colorXY[x - 1][y] = "DANGER";
			gotoXY(x, y);
			cout << (char)254;
			colorXY[x][y] = "DANGER";
			gotoXY(x + 1, y);
			cout << (char)254;
			colorXY[x + 1][y] = "DANGER";
			gotoXY(x + 2, y);
			cout << " ";
			colorXY[x + 2][y] = "SAFE";
			x--;
			if (x == 8) {
				t = 1;
				gotoXY(x - 2, y);
				cout << " ";
			}
		}
	}
}
void obstacle1(int currentLevel) {
	static int x = 128, y = 20;
	static int tempx;
	static int t = 1;
	if (currentLevel == 4) {
		if (t == 2) {
			textColor(BLUE);
			gotoXY(x + 3, y);
			cout << (char)16;
			colorXY[x + 3][y] = "DANGER";
			gotoXY(x + 2, y);
			cout << (char)254;
			colorXY[x + 2][y] = "DANGER";
			gotoXY(x + 1, y);
			cout << (char)254;
			colorXY[x + 1][y] = "DANGER";
			gotoXY(x, y);
			cout << (char)254;
			colorXY[x][y] = "DANGER";
			gotoXY(x - 1, y);
			cout << (char)254;
			colorXY[x - 1][y] = "DANGER";
			gotoXY(x - 2, y);
			cout << " ";
			colorXY[x - 2][y] = "SAFE";
			x++;
			if (x == 128) {
				t = 1;
				gotoXY(x + 2, y);
				cout << " ";

			}
		}
		if (t == 1) {
			textColor(BLUE);
			gotoXY(x - 3, y);
			colorXY[x - 3][y] = "DANGER";
			cout << (char)17;
			gotoXY(x - 2, y);
			cout << (char)254;
			colorXY[x - 2][y] = "DANGER";
			gotoXY(x - 1, y);
			cout << (char)254;
			colorXY[x - 1][y] = "DANGER";
			gotoXY(x, y);
			cout << (char)254;
			colorXY[x][y] = "DANGER";
			gotoXY(x + 1, y);
			cout << (char)254;
			colorXY[x + 1][y] = "DANGER";
			gotoXY(x + 2, y);
			cout << " ";
			colorXY[x + 2][y] = "SAFE";
			x--;
			if (x == 8) {
				t = 2;
				gotoXY(x - 2, y);
				cout << " ";
			}
		}
	}
}

void obstacle2(int currentLevel) {
	static int x = 63, y = 4;
	static int tempx;
	static int t = 1;
	if (currentLevel == 4) {
		if (t == 1) {
			textColor(BLUE);
			gotoXY(x, y + 2);
			cout << (char)31;
			colorXY[x][y + 2] = "DANGER";
			gotoXY(x, y + 1);
			cout << (char)219;
			colorXY[x][y + 1] = "DANGER";
			gotoXY(x, y);
			cout << (char)219;
			colorXY[x][y] = "DANGER";
			gotoXY(x, y - 1);
			cout << " ";
			colorXY[x][y - 1] = "SAFE";
			y++;
			if (y == 40) t = 2;
		}
		if (t == 2) {
			textColor(BLUE);
			gotoXY(x, y - 2);
			colorXY[x][y - 2] = "DANGER";
			cout << (char)30;
			gotoXY(x, y - 1);
			cout << (char)219;
			colorXY[x][y - 1] = "DANGER";
			gotoXY(x, y);
			cout << (char)219;
			colorXY[x][y] = "DANGER";
			gotoXY(x, y + 1);
			cout << " ";
			colorXY[x][y + 1] = "SAFE";
			y--;
			if (y == 4) t = 1;
		}
	}
}
void obstacle3(int currentLevel) {
	static int x = 72, y = 40;
	static int tempx;
	static int t = 1;
	if (currentLevel == 4) {
		if (t == 2) {
			textColor(BLUE);
			gotoXY(x, y + 2);
			cout << (char)31;
			colorXY[x][y + 2] = "DANGER";
			gotoXY(x, y + 1);
			cout << (char)219;
			colorXY[x][y + 1] = "DANGER";
			gotoXY(x, y);
			cout << (char)219;
			colorXY[x][y] = "DANGER";
			gotoXY(x, y - 1);
			cout << " ";
			colorXY[x][y - 1] = "SAFE";
			y++;
			if (y == 40) t = 1;
		}
		if (t == 1) {
			textColor(BLUE);
			gotoXY(x, y - 2);
			colorXY[x][y - 2] = "DANGER";
			cout << (char)30;
			gotoXY(x, y - 1);
			cout << (char)219;
			colorXY[x][y - 1] = "DANGER";
			gotoXY(x, y);
			cout << (char)219;
			colorXY[x][y] = "DANGER";
			gotoXY(x, y + 1);
			cout << " ";
			colorXY[x][y + 1] = "SAFE";
			y--;
			if (y == 4) t = 2;
		}
	}
}