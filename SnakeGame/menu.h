#pragma once
#include <vector>
#include "graphic.h"
#include "screen.h"

using namespace std;

struct Menu {
	int x, y;
	string data;

	Menu() {
		x = y = 0;
		data = "";
	}
};

struct Player {
	string name, dateAndTime;
	int score;

	Player() {
		name = "";
		dateAndTime = "";
		score = 0;
	}
};

void initMenu(vector<Menu>& listMenu);

void printMenu(vector<Menu> listMenu);

void moveSelect(vector<Menu> listMenu, int& dir, bool& check);

void moveSelectSetting(vector<Menu> listMenu, int& dir, bool& check);

void setting();

void ourTeam();

void guide();

void swap(Player& a, Player& b);

void highScore(vector<Player>& savePlayers, Screen screen)
;
void loadFileScore(vector<Player>& savePlayers);

void ourTeam();

void fillName(string& name);

int loseGame(string& name, string& dateAndTime);

void pauseGame();

void loadGameGraphic(string& uName, string& password);

void loadingGameGraphic();

void fillPassword(string& key);

void settingGraphic();