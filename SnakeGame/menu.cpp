#pragma once
#include "menu.h"
#include "screen.h"
#include "graphic.h"
#include "snake.h"
#include "gameSound.h"
#include <fstream>
#include <string>
using namespace std;

void initMenu(vector<Menu>& listMenu) {
	Menu items;

	items.x = 85;
	items.y = 24;
	items.data = "PLAY GAME";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 26;
	items.data = "LOAD GAME";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 28;
	items.data = "HIGH SCORE";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 30;
	items.data = "GUIDE";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 32;
	items.data = "SETTING";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 34;
	items.data = "OUR TEAM";
	listMenu.push_back(items);

	items.x = 85;
	items.y = 36;
	items.data = "QUIT GAME";
	listMenu.push_back(items);
}

void printMenu(vector<Menu> listMenu) {
	for (int i = 0; i < listMenu.size(); i++) {
		gotoXY(listMenu[i].x, listMenu[i].y);
		cout << listMenu[i].data;
	}
}

void moveSelect(vector<Menu> listMenu, int& dir, bool& check) {
	while (true) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 72) {
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << "             ";
				gotoXY(listMenu[dir].x, listMenu[dir].y); cout << listMenu[dir].data;
				if (dir == 0) {
					dir = listMenu.size() - 1;
				}
				else {
					dir--;
				}

				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				textColor(RED);
				cout << (char)175 << " " << listMenu[dir].data << " ";
				textColor(BLUE);
				//break;
			}
			else if (key == 80) {
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << "             ";
				gotoXY(listMenu[dir].x, listMenu[dir].y);
				cout << listMenu[dir].data;

				if (dir == listMenu.size() - 1) {
					dir = 0;
				}
				else {
					dir++;
				}

				textColor(RED);
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << (char)175 << " " << listMenu[dir].data << " ";
				textColor(BLUE);
				//break;
			}
			else if (key == 13) {
				check = true;
				break;
			}
		}
	}
}

void moveSelectSetting(vector<Menu> listMenu, int& dir, bool& check) {
	while (true) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 72) {
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << "             ";
				gotoXY(listMenu[dir].x, listMenu[dir].y); cout << listMenu[dir].data;
				if (dir == 0) {
					dir = listMenu.size() - 1;
				}
				else {
					dir--;
				}

				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				textFillColor(RED, BLACK);
				cout << (char)175 << " " << listMenu[dir].data << " ";
				textFillColor(WHITE, BLACK);
				//break;
			}
			else if (key == 80) {
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << "             ";
				gotoXY(listMenu[dir].x, listMenu[dir].y);
				cout << listMenu[dir].data;

				if (dir == listMenu.size() - 1) {
					dir = 0;
				}
				else {
					dir++;
				}

				textFillColor(RED, BLACK);
				gotoXY(listMenu[dir].x - 3, listMenu[dir].y);
				cout << (char)175 << " " << listMenu[dir].data << " ";
				textFillColor(WHITE, BLACK);
				//break;
			}
			else if (key == 13) {
				check = true;
				break;
			}
			else if (key == 27) {
				check = true;
				dir = -1;
				break;
			}
		}
	}
}

void blackBoard() {
	int leng = 9;
	textFillColor(BLUE, BLACK);
	for (int j = 15; j <= 40; ++j) {
		gotoXY(20 - leng, j);
		cout << "                                                                                                                                                          ";
		Sleep(8);
	}

	textFillColor(WHITE, BLACK);
	for (int i = 20 - leng; i <= 155 + leng; ++i) {
		gotoXY(i, 15);
		cout << (char)(205);
		gotoXY(i, 40);
		cout << (char)(205);
	}

	for (int i = 15; i <= 40; ++i) {
		gotoXY(20 - leng, i);
		cout << (char)(186);
		gotoXY(155 + leng, i);
		cout << (char)(186);
	}

	gotoXY(20 - leng, 15);
	cout << (char)(201);

	gotoXY(20 - leng, 40);
	cout << (char)(200);

	gotoXY(155 + leng, 15);
	cout << (char)(187);

	gotoXY(155 + leng, 40);
	cout << (char)(188);
}

void setting() {
	blackBoard();
	

	int row = 16, col = 60;

	textFillColor(BYELLOW, BLACK);
	gotoXY(col, row++);
	wcout << L"	███████╗███████╗████████╗████████╗██╗███╗   ██╗ ██████╗ ";
	gotoXY(col, row++);
	wcout << L"	██╔════╝██╔════╝╚══██╔══╝╚══██╔══╝██║████╗  ██║██╔════╝ ";
	gotoXY(col, row++);
	wcout << L"	███████╗█████╗     ██║      ██║   ██║██╔██╗ ██║██║  ███╗";
	gotoXY(col, row++);
	wcout << L"	╚════██║██╔══╝     ██║      ██║   ██║██║╚██╗██║██║   ██║";
	gotoXY(col, row++);
	wcout << L"	███████║███████╗   ██║      ██║   ██║██║ ╚████║╚██████╔╝";
	gotoXY(col, row++);
	wcout << L"	╚══════╝╚══════╝   ╚═╝      ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝	";
	gotoXY(col, row++);

	int row5 = 32, col5 = 20;
	gotoXY(col5, row5++);
	textFillColor(GRAY, 64);
	cout << "                                                                                                                                   _____";
	gotoXY(col5, row5++);
	textFillColor(VIOLET, 64);
	cout << "                                                                                                                                  / . . \\";
	gotoXY(col5, row5++);
	textFillColor(BLUE, 64);
	cout << "                                                                                                                                  \\   ------<";
	gotoXY(col5, row5++);
	textFillColor(GREEN, 64);
	cout << "                                                                                                                                   \\    /";
	gotoXY(col5, row5++);
	textFillColor(GREEN, 64);
	cout << "                                                                                                                                    \\  /";
	gotoXY(col5, row5++);
	textFillColor(BYELLOW, 64);
	cout << "   _________________________________________________________________________________________________________________________________/ /";
	gotoXY(col5, row5++);
	textFillColor(RED, 64);
	cout << "-=:__________________________________________________________________________________________________________________________________/";

	textFillColor(WHITE, 64);
	settingGraphic();
	// Exit
	int row6 = 39, col6 = 43;
	gotoXY(col6, row6++);
	cout << "Press ESC to exit. Press enter to change value.";
}

void ourTeam() {
	blackBoard();

	// Ourteam logo
	//int row = 16, col = 70;
	//textFillColor(GRAY, 64);
	//gotoXY(col, row++);
	//cout << "   ____               _______                  ";
	//gotoXY(col, row++);
	//cout << "  / __ \\             |__   __|                  ";
	//gotoXY(col, row++);
	//cout << " | |  | |_   _ _ __     | | ___  __ _ _ __ ___  ";
	//gotoXY(col, row++);
	//cout << " | |  | | | | | '__|    | |/ _ \\/ _` | '_ ` _ \\ ";
	//gotoXY(col, row++);
	//cout << " | |__| | |_| | |       | |  __/ (_| | | | | | |";
	//gotoXY(col, row++);
	//cout << "  \\____/ \\__,_|_|       |_|\\___|\\__,_|_| |_| |_|";

	//textFillColor(WHITE, 64);

	// Ourteam logo
	int row = 16, col = 60;
	textFillColor(RED, 64);
	gotoXY(col, row++);
	wcout << L" ██████╗ ██╗   ██╗██████╗     ████████╗███████╗ █████╗ ███╗   ███╗";
	gotoXY(col, row++);
	wcout << L"██╔═══██╗██║   ██║██╔══██╗    ╚══██╔══╝██╔════╝██╔══██╗████╗ ████║";
	gotoXY(col, row++);
	wcout << L"██║   ██║██║   ██║██████╔╝       ██║   █████╗  ███████║██╔████╔██║";
	gotoXY(col, row++);
	wcout << L"██║   ██║██║   ██║██╔══██╗       ██║   ██╔══╝  ██╔══██║██║╚██╔╝██║";
	gotoXY(col, row++);
	wcout << L"╚██████╔╝╚██████╔╝██║  ██║       ██║   ███████╗██║  ██║██║ ╚═╝ ██║";
	gotoXY(col, row++);
	wcout << L" ╚═════╝  ╚═════╝ ╚═╝  ╚═╝       ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝";

	// Team 8 border
	textFillColor(11, 64);
	for (int i = 43; i <= 79; ++i) {
		gotoXY(i, 24);
		cout << (char)(205);
		gotoXY(i, 32);
		cout << (char)(205);
	}
	for (int i = 24; i <= 32; ++i) {
		gotoXY(43, i);
		cout << (char)(186);
		gotoXY(79, i);
		cout << (char)(186);
	}

	gotoXY(43, 24);
	cout << (char)(201);
	gotoXY(43, 32);
	cout << (char)(200);
	gotoXY(79, 24);
	cout << (char)(187);
	gotoXY(79, 32);
	cout << (char)(188);

	textFillColor(WHITE, 64);

	// Teamm 8 logo
	int row1 = 22, col1 = 46;
	textFillColor(11, 64);

	gotoXY(col1, row1++);
	cout << "  _____ ___   _   __  __   ___ ";
	gotoXY(col1, row1++);
	cout << " |_   _| __| /_\\ |  \\/  | ( _ )";
	gotoXY(col1, row1++);
	cout << "   | | | _| / _ \\| |\\/| | / _ \\";
	gotoXY(col1, row1++);
	cout << "   |_| |___/_/ \\_\\_|  |_| \\___/";

	textFillColor(WHITE, 64);

	// Team member
	int row2 = 27, col2 = 45;

	gotoXY(col2, row2++);
	textFillColor(RED, 64);
	cout << "Phan Thanh An       - 21127003";

	gotoXY(col2, row2++);
	textFillColor(BYELLOW, 64);
	cout << "Nguyen Nhat Nam     - 21127648";

	gotoXY(col2, row2++);
	textFillColor(CYAN, 64);
	cout << "Vo Nguyen Hoang Kim - 21127090";

	gotoXY(col2, row2++);
	textFillColor(GREEN, 64);
	cout << "Luu Hoang Bach      - 21127493";

	textFillColor(WHITE, 64);

	// Instructor border
	textFillColor(11, 64);
	for (int i = 81; i <= 138; ++i) {
		gotoXY(i, 24);
		cout << (char)(205);
		gotoXY(i, 29);
		cout << (char)(205);
	}

	for (int i = 24; i <= 29; ++i) {
		gotoXY(81, i);
		cout << (char)(186);
		gotoXY(138, i);
		cout << (char)(186);
	}

	gotoXY(81, 24);
	cout << (char)(201);
	gotoXY(81, 29);
	cout << (char)(200);
	gotoXY(138, 24);
	cout << (char)(187);
	gotoXY(138, 29);
	cout << (char)(188);

	textFillColor(WHITE, 64);

	// Instructor logo
	int row3 = 22, col3 = 84;
	textFillColor(11, 64);
	gotoXY(col3, row3++);
	cout << "  ___ _  _ ___ _____ ___ _   _  ___ _____ ___  ___ ";
	gotoXY(col3, row3++);
	cout << " |_ _| \\| / __|_   _| _ \\ | | |/ __|_   _/ _ \\| _ \\";
	gotoXY(col3, row3++);
	cout << "  | || .` \\__ \\ | | |   / |_| | (__  | || (_) |   /";
	gotoXY(col3, row3++);
	cout << " |___|_|\\_|___/ |_| |_|_\\\\___/ \\___| |_| \\___/|_|_\\";

	textFillColor(WHITE, 64);

	// Instructor information
	int row4 = 27, col4 = 83;

	gotoXY(col4, row4++);
	textFillColor(14, 64);
	cout << "Dr.Truong Toan Thinh - Teacher";

	textFillColor(WHITE, 64);

	// Snake image
	/*int flag = 0;
	while (flag == 0) {
		Sleep(100);
		textFillColor(RED, 64);
		snakeImage();
		Sleep(100);
		textFillColor(VIOLET, 64);
		snakeImage();
		Sleep(100);
		textFillColor(BLUE, 64);
		snakeImage();
		Sleep(100);
		textFillColor(GREEN, 64);
		snakeImage();
		Sleep(100);
		textFillColor(BYELLOW, 64);
		snakeImage();
		Sleep(100);
		textFillColor(WHITE, 64);
		snakeImage();
	}*/

	// Snake image
	int row5 = 33, col5 = 41;
	gotoXY(col5, row5++);
	textFillColor(GRAY, 64);
	cout << "                           __    __    __    __    __    __    __    __    __    __ ";
	gotoXY(col5, row5++);
	textFillColor(VIOLET, 64);
	cout << "                          /  \\  /  \\  /  \\  /  \\  /  \\  /  \\  /  \\  /  \\  /  \\  /  \\";
	gotoXY(col5, row5++);
	textFillColor(BLUE, 64);
	cout << " ________________________/  __\\/  __\\/  __\\/  __\\/  __\\/  __\\/  __\\/  __\\/  __\\/  __\\______________";
	gotoXY(col5, row5++);
	textFillColor(GREEN, 64);
	cout << " _______________________/  /__/  /__/  /__/  /__/  /__/  /__/  /__/  /__/  /__/  /_________________";
	gotoXY(col5, row5++);
	textFillColor(BYELLOW, 64);
	cout << "                       /  / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\   / \\  \\____";
	gotoXY(col5, row5++);
	textFillColor(RED, 64);
	cout << "                      / /    \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\_/   \\    o \\";
	gotoXY(col5, row5++);
	cout << "                     //                                                             \\_____/--<";
	textFillColor(WHITE, 64);

	// Exit
	int row6 = 39, col6 = 43;
	gotoXY(col6, row6++);
	cout << "Press ESC to exit.";
}

void guide() {
	blackBoard();

	int row = 16, col = 75;
	textFillColor(CYAN, BLACK);
	gotoXY(col, row++);
	wcout << L" ██████╗ ██╗   ██╗██╗██████╗ ███████╗";
	gotoXY(col, row++);
	wcout << L"██╔════╝ ██║   ██║██║██╔══██╗██╔════╝";
	gotoXY(col, row++);
	wcout << L"██║  ███╗██║   ██║██║██║  ██║█████╗ ";
	gotoXY(col, row++);
	wcout << L"██║   ██║██║   ██║██║██║  ██║██╔══╝ ";
	gotoXY(col, row++);
	wcout << L"╚██████╔╝╚██████╔╝██║██████╔╝███████╗";

	// KEYBOARD SHORTCUTS 
	textFillColor(BYELLOW, 64);
	col = 19, row = 20;
	gotoXY(col, row);
	cout << "KEYBOARD-SHORTCUTS";
	textFillColor(GREEN, 64);
	for (int i = 0; i < 30; i++)
	{
		cout << '-';
		if (i == 24)
		{
			cout << " ";
			for (int j = 0; j < 2; j++)
			{
				cout << char(254) << " ";
			}
			break;
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		row++;
		gotoXY(col, row);
		cout << (char)254;
	}
	for (int i = 0; i < 16; i++)
	{
		row++;
		gotoXY(col, row);
		if (i == 15)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << (char)254 << " ";
			}
		}
		else
			cout << "|";
	}
	for (int i = 0; i < 43; i++)
	{
		cout << '-';
	}
	col = col + 48;
	for (int i = 1; i <= 3; i++)
	{
		row--;
		gotoXY(col, row);
		cout << (char)254;
	}
	for (int i = 0; i < 16; i++)
	{
		row--;
		gotoXY(col, row);
		if (i != 15)
		{
			cout << '|';
		}
		else
			cout << (char)254;
	}

	// BE CAREFUL
	textFillColor(VIOLET, 64);
	col = col + 8;
	row = row + 3;
	gotoXY(col, row);
	for (int i = 0; i < 82; i++)
	{
		col++;
		gotoXY(col, row);
		if (i != 81)
		{
			cout << (char)205;
		}
		else
			cout << (char)187;
	}

	gotoXY(col - 48, row);
	textFillColor(RED, 64);
	cout << (char)254 << " BE-CAREFUL " << (char)254;
	
	textFillColor(VIOLET, 64);
	for (int i = 0; i < 14; i++)
	{
		row++;
		gotoXY(col, row);
		if (i != 13)
		{
			cout << (char)186;
		}
		else
			cout << (char)188;
	}

	for (int i = 0; i < 82; i++)
	{
		col--;
		gotoXY(col, row);
		if (i != 81)
		{
			cout << (char)205;
		}
		else
			cout << (char)200;
	}
	
	for (int i = 0; i < 14; i++)
	{
		row--;
		gotoXY(col, row);
		if (i != 13)
		{
			cout << (char)186;
		}
		else
			cout << (char)201;
	}

	// text for "keyboard shortcuts"
	textFillColor(WHITE, 64);
	col = 26; row = 22;
	for (int i = 0; i < 4; i++)
	{
		gotoXY(col, row);
		for (int j = 0; j < 5; j++)
		{
			cout << (char)219;
		}
		row = row + 1;
	}
	row = row - 2;
	col = col - 4;
	for (int i = 0; i < 3; i++)
	{
		gotoXY(col, row);
		for (int j = 0; j < 13; j++)
		{
			if (i < 2)
			{
				cout << (char)219;
			}
			else
			{
				cout << (char)223;
			}
		}
		row = row + 1;
	}
	textFillColor(BLACK, 63);
	gotoXY(28, 23);
	cout << "W";
	gotoXY(24, 25);
	cout << "A   S   D";
	textFillColor(GRAY, 64);
	gotoXY(40, 23);
	cout << "Pressing these keys";
	gotoXY(40, 24);
	cout << "to control the snake";

	textFillColor(WHITE, 64);
	col = 22; row = 28;
	for (int i = 0; i < 3; i++)
	{
		gotoXY(col, row);
		for (int j = 0; j < 13; j++)
		{
			switch (i)
			{
			case 0:
				cout << (char)220;
				break;
			case 1:
				cout << (char)219;
				break;
			case 2:
				cout << (char)223;
				break;
			}
		}
		row++;
	}
	textFillColor(BLACK, 63);
	gotoXY(26, row - 2);
	cout << "Enter";
	textFillColor(WHITE, 64);
	gotoXY(40, 29);
	cout << "Increase/decrease speed";

	col = 22; row = row + 1;
	for (int i = 0; i < 3; i++)
	{
		gotoXY(col, row);
		for (int j = 0; j < 13; j++)
		{
			switch (i)
			{
			case 0:
				cout << (char)220;
				break;
			case 1:
				cout << (char)219;
				break;
			case 2:
				cout << (char)223;
				break;
			}
		}
		row = row + 1;
	}
	textFillColor(BLACK, 63);
	gotoXY(26, row - 2);
	cout << "SPACE";
	textFillColor(GRAY, 64);
	gotoXY(40, row - 2);
	cout << "Pause / Continue";

	textFillColor(WHITE, 64);
	col = 26; row = row + 1;
	for (int i = 0; i < 3; i++)
	{
		gotoXY(col, row);
		for (int j = 0; j < 5; j++)
		{
			switch (i)
			{
			case 0:
				cout << (char)220;
				break;
			case 1:
				cout << (char)219;
				break;
			case 2:
				cout << (char)223;
				break;
			}
		}
		row++;
	}
	textFillColor(BLACK, 63);
	gotoXY(col + 2, row - 2);
	cout << "L";
	textFillColor(GRAY, 64);
	gotoXY(40, row - 2);
	cout << "Save game";

	// text for "be careful"
	col = 77, row = 25;
	gotoXY(col, row);
	cout << (char)5 << " Do not hit any obstacles ";
	gotoXY(col, row + 2);
	cout << (char)5 << " Avoid the walls";
	gotoXY(col, row + 4);
	cout << (char)5 << " Do not let the head of snake touches any part of its body";
	textFillColor(BYELLOW, 64);
	col = 98, row = 31;
	gotoXY(col, row);
	cout << "- - - - - - BONUS LEVEL - - - - -";
	textFillColor(WHITE, 64);
	col = 77, row = 33;
	gotoXY(col, row);
	cout << (char)5 << " The food has the same color with the snake will make increase its length";
	gotoXY(col, row + 2);
	cout << (char)5 << " The food has the different color with the snake will make increase your score";


	textFillColor(CYAN, 64);
	gotoXY(143, 39);
	cout << "Press ESC to exit";
}

void swap(Player& a, Player& b) {
	Player temp;
	temp = a;
	a = b;
	b = temp;
}

void loadFileScore(vector<Player>& savePlayers) {
	ifstream filein;
	filein.open("saveScore.txt", ios::in);
	if (filein.fail() == true) {
		cout << "File cannot be found";
	}
	else {
		savePlayers.clear();
		Player x;
		while (!filein.eof()) {
			filein >> x.score;
			filein.ignore();
			getline(filein, x.name);
			getline(filein, x.dateAndTime);
			savePlayers.push_back(x);
		}
	}
}

void highScore(vector<Player>& savePlayers, Screen screen) {
	blackBoard();

	int colHS = 48;
	int rowHS = 17;
	textFillColor(14, BLACK);
	gotoXY(colHS, rowHS++);
	wcout << L"	██╗  ██╗██╗ ██████╗ ██╗  ██╗    ███████╗ ██████╗ ██████╗ ██████╗ ███████╗";
	gotoXY(colHS, rowHS++);
	wcout << L"	██║  ██║██║██╔════╝ ██║  ██║    ██╔════╝██╔════╝██╔═══██╗██╔══██╗██╔════╝";
	gotoXY(colHS, rowHS++);
	wcout << L"	███████║██║██║  ███╗███████║    ███████╗██║     ██║   ██║██████╔╝█████╗  ";
	gotoXY(colHS, rowHS++);
	wcout << L"	██╔══██║██║██║   ██║██╔══██║    ╚════██║██║     ██║   ██║██╔══██╗██╔══╝  ";
	gotoXY(colHS, rowHS++);
	wcout << L"	██║  ██║██║╚██████╔╝██║  ██║    ███████║╚██████╗╚██████╔╝██║  ██║███████╗";
	gotoXY(colHS, rowHS++);
	wcout << L"	╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═╝    ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝";

	textFillColor(14, BLACK);
	int a = 134;
	int b = 24;
	gotoXY(a, b++);
	wcout << L"  █████████████████  ";
	gotoXY(a, b++);
	wcout << L" ███████████████████ ";
	gotoXY(a, b++);
	wcout << L"██ ███████████████ ██";
	gotoXY(a, b++);
	wcout << L" ███████████████████ ";
	gotoXY(a, b++);
	wcout << L"  █████████████████  ";
	gotoXY(a, b++);
	wcout << L"   ███████████████   ";
	gotoXY(a, b++);
	wcout << L"     █  ██████  █    ";
	gotoXY(a, b++);
	wcout << L"         ███        ";
	gotoXY(a, b++);
	wcout << L"         ███        ";
	gotoXY(a, b++);
	wcout << L"         ███        ";
	gotoXY(a, b++);
	wcout << L"       ███████      ";
	gotoXY(a, b++);
	wcout << L"      █████████      ";
	gotoXY(a, b++);
	wcout << L"     ███████████      ";
	gotoXY(a, b++);
	wcout << L"     ███████████      ";
	gotoXY(a, b++);
	wcout << L"     ███████████      ";

	//High score border
	//screen.draw.retangle({ 44, 23 }, { 36, 16 }, 3, 1, colorXY);
	int s5 = 11;
	textFillColor(3, BLACK);
	for (int i = 43 + s5; i <= 115 + s5; i++) {
		gotoXY(i, 23);
		cout << (char)220;
		gotoXY(i, 38);
		cout << (char)223;
		if (i != 43 + s5 && i != 53 + s5 && i != 65 + s5 && i != 86 + s5) {
			gotoXY(i, 27);
			cout << (char)223;
		}

	}
	textFillColor(GRAY, BLACK);
	for (int i = 43 + s5; i <= 115 + s5; i++) {
		gotoXY(i, 27);
		cout << (char)223;
	}
	textFillColor(3, BLACK);
	gotoXY(43 + s5, 27);
	cout << char(221);
	for (int i = 24; i <= 37; i++) {
		gotoXY(43 + s5, i);
		cout << (char)219;
		gotoXY(53 + s5, i);
		cout << (char)219;
		gotoXY(65 + s5, i);
		cout << (char)219;
		gotoXY(86 + s5, i);
		cout << (char)219;
		gotoXY(115 + s5, i);
		cout << (char)219;
	}

	//screen.draw.retangle({ 52, 24 }, { 0, 14 }, 3, 1, colorXY);
	//screen.draw.retangle({ 44, 27 }, { 36, 0 }, 3, 1, colorXY);
	//screen.draw.retangle({ 65, 24 }, { 0, 14 }, 3, 1, colorXY);
	//screen.draw.retangle({ 86, 24 }, { 0, 14 }, 3, 1, colorXY);
	gotoXY(46 + s5, 25);
	textFillColor(11, BLACK);
	cout << "RANK";
	gotoXY(57 + s5, 25);
	cout << "SCORE";
	gotoXY(74 + s5, 25);
	cout << "NAME";
	gotoXY(100 + s5, 25);
	cout << "DATE";

	//Sort function
	for (int i = 0; i < savePlayers.size() - 1; i++) {
		for (int j = i + 1; j < savePlayers.size(); j++) {
			if (savePlayers[i].score < savePlayers[j].score) {
				swap(savePlayers[i], savePlayers[j]);
			}
		}
	}
	//gotoXY(0, 0);
	//cout << savePlayers.size();
	//textColor(WHITE);

	textFillColor(14, BLACK);
	for (int i = 0; i < savePlayers.size(); i++) {
		if (i >= 10) break;
		gotoXY(48 + s5, i + 28);
		cout << i + 1;
		gotoXY(58 + s5, i + 28);
		cout << savePlayers[i].score << endl;
		gotoXY(70 + s5, i + 28);
		cout << savePlayers[i].name << endl;
		gotoXY(89 + s5, i + 28);
		cout << savePlayers[i].dateAndTime << endl;
	}
	textFillColor(14, BLACK);
	int a1 = 16;
	int b1 = 20;
	gotoXY(a1, b1++);
	wcout << L"              ░░  ";
	gotoXY(a1, b1++);
	wcout << L"              ██  ";
	gotoXY(a1, b1++);
	wcout << L"            ██  ██ ";
	gotoXY(a1, b1++);
	wcout << L"          ▓▓      ▓▓   ";
	gotoXY(a1, b1++);
	wcout << L"     ████████░░░░░░██████  ";
	gotoXY(a1, b1++);
	wcout << L"     ██    ██▓▓▓▓██    ██  ";
	gotoXY(a1, b1++);
	wcout << L"    ████  ██░░░░░░▒▒██  ██  ";
	gotoXY(a1, b1++);
	wcout << L"  ██  ░░██░░░░░░░░░░▒▒██████  ";
	gotoXY(a1, b1++);
	wcout << L"▓▓    ░░██░░░░░░░░░░▒▒██▒▒░░▓▓ ";
	gotoXY(a1, b1++);
	wcout << L"  ██  ░░██░░░░░░░░░░▒▒██░░    ██ ";
	gotoXY(a1, b1++);
	wcout << L"    ▓▓▓▓██▒▒░░░░░░░░▒▒██░░  ▓▓ ";
	gotoXY(a1, b1++);
	wcout << L"      ██  ██▒▒▒▒▒▒▒▒██  ████  ";
	gotoXY(a1, b1++);
	wcout << L"      ██    ██▓▓████    ██ ";
	gotoXY(a1, b1++);
	wcout << L"      ██████░░░░░░████████ ";
	gotoXY(a1, b1++);
	wcout << L"          ██      ██  ";
	gotoXY(a1, b1++);
	wcout << L"            ██  ██  ";
	gotoXY(a1, b1++);
	wcout << L"              ██  ";
	int row6 = 39, col6 = 13;
	gotoXY(col6, row6++);
	cout << "Press ESC to exit.";
}

User user[100];

void fillName(string& name) {
	system("cls");
	int t = 25;
	Sleep(t);
	textFillColor(3, BACKGROUND_COLOR);
	int col1 = 50, row1 = 18;
	gotoXY(col1, row1++);
	wcout << L"██    ██  ██████  ██    ██ ██████      ███    ██  █████  ███    ███ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L" ██  ██  ██    ██ ██    ██ ██   ██     ████   ██ ██   ██ ████  ████ ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"  ████   ██    ██ ██    ██ ██████      ██ ██  ██ ███████ ██ ████ ██ █████   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"   ██    ██    ██ ██    ██ ██   ██     ██  ██ ██ ██   ██ ██  ██  ██ ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"   ██     ██████   ██████  ██   ██     ██   ████ ██   ██ ██      ██ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1 + 15, row1++);
	textColor(3);
	cout << "Please fill in your name in the blanks below. ";
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 25 }, 12, 1, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 66, 27 }, { 20, 4 }, 3, 2, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 65, 26 }, { 21, 6 }, 3, 2, colorXY);
	Sleep(t);
	while (1) {
		gotoXY(78, 29);
		textColor(3);
		int check = 0;
		cin >> name;

		int N = loadFileUserData();
		for (int i = 0; i < N; i++) {
			if (name == user[i].name) {
				gotoXY(0, 30);
				cout << "           ";
				Sleep(500);
				gotoXY(55, 34);
				textColor(RED);
				cout << "Your name is not valid or already exist. Please retype your name ";
				check = 1;
				gotoXY(78, 29);
				cout << "                     ";

			}
		}
		if (check == 0) break;
	}
}

int loseGame(string& name, string& dateAndTime) {
	system("cls");
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 27 }, 12, 1, colorXY);
	int t = 25;
	Sleep(t);
	textFillColor(3, BACKGROUND_COLOR);
	int col1 = 42, row1 = 18;
	gotoXY(col1, row1++);
	wcout << L"██    ██  ██████  ██    ██      █████  ██████  ███████     ██       ██████  ███████ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L" ██  ██  ██    ██ ██    ██     ██   ██ ██   ██ ██          ██      ██    ██ ██      ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"  ████   ██    ██ ██    ██     ███████ ██████  █████       ██      ██    ██ ███████ █████   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"   ██    ██    ██ ██    ██     ██   ██ ██   ██ ██          ██      ██    ██      ██ ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"   ██     ██████   ██████      ██   ██ ██   ██ ███████     ███████  ██████  ███████ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1 + 28, row1 + 5);
	textColor(3);
	int s = 8;
	int s2 = 38;
	cout << "Do you want to continue playing ? ";


	for (int i = 55 + s; i <= 70 + s; ++i) {
		gotoXY(i, 33);
		cout << (char)(205);
		gotoXY(i, 37);
		cout << (char)(205);
	}

	for (int i = 34; i <= 36; ++i) {
		gotoXY(54 + s, i);
		cout << (char)(186);
		gotoXY(71 + s, i);
		cout << (char)(186);
	}

	gotoXY(54 + s, 33);
	cout << (char)(201);
	gotoXY(54 + s, 37);
	cout << (char)(200);
	gotoXY(71 + s, 33);
	cout << (char)(187);
	gotoXY(71 + s, 37);
	cout << (char)(188);
	gotoXY(54 + s + 8, 35);
	cout << "YES";

	for (int i = 55 + s2; i <= 70 + s2 + 1; ++i) {
		gotoXY(i, 33);
		cout << (char)(205);
		gotoXY(i, 37);
		cout << (char)(205);
	}
	for (int i = 34; i <= 36; ++i) {
		gotoXY(54 + s2, i);
		cout << (char)(186);
		gotoXY(71 + s2, i);
		cout << (char)(186);
	}
	gotoXY(54 + s2, 33);
	cout << (char)(201);
	gotoXY(54 + s2, 37);
	cout << (char)(200);
	gotoXY(71 + s2, 33);
	cout << (char)(187);
	gotoXY(71 + s2, 37);
	cout << (char)(188);
	gotoXY(54 + s + 38, 35);
	cout << "NO";
	//This line for using getch
	int t2 = 0.5;
	textColor(RED);
	for (int i = 55 + s; i <= 70 + s; ++i) {
		gotoXY(i, 33);
		cout << (char)(205);
		Sleep(t2);
		gotoXY(i, 37);
		cout << (char)(205);
		Sleep(t2);

	}

	for (int i = 34; i <= 36; ++i) {
		gotoXY(54 + s, i);
		cout << (char)(186);
		Sleep(t2);
		gotoXY(71 + s, i);
		cout << (char)(186);
		Sleep(t2);
	}
	int temp1 = 1;
	gotoXY(54 + s, 33);
	cout << (char)(201);
	gotoXY(54 + s, 37);
	cout << (char)(200);
	gotoXY(71 + s, 33);
	cout << (char)(187);
	gotoXY(71 + s, 37);
	cout << (char)(188);
	gotoXY(54 + s + 8, 35);
	cout << "YES";
	while (true) {
		int key = _getch();
		if (key == 'd' || key == 'a' || key == 75 || key == 77) {
			temp1++;
			if (temp1 % 2 == 1) {
				textColor(3);
				for (int i = 55 + s2; i <= 70 + s2 + 1; ++i) {
					gotoXY(i, 33);
					cout << (char)(205);
					Sleep(t2);
					gotoXY(i, 37);
					cout << (char)(205);
					Sleep(t2);
				}
				for (int i = 34; i <= 36; ++i) {
					gotoXY(54 + s2, i);
					cout << (char)(186);
					Sleep(t2);
					gotoXY(71 + s2, i);
					cout << (char)(186);
					Sleep(t2);
				}
				gotoXY(54 + s2, 33);
				cout << (char)(201);
				gotoXY(54 + s2, 37);
				cout << (char)(200);
				gotoXY(71 + s2, 33);
				cout << (char)(187);
				gotoXY(71 + s2, 37);
				cout << (char)(188);
				gotoXY(54 + s + 38, 35);
				cout << "NO";
				textColor(RED);
				for (int i = 55 + s; i <= 70 + s; ++i) {
					gotoXY(i, 33);
					cout << (char)(205);
					Sleep(t2);
					gotoXY(i, 37);
					cout << (char)(205);
					Sleep(t2);

				}

				for (int i = 34; i <= 36; ++i) {
					gotoXY(54 + s, i);
					cout << (char)(186);
					Sleep(t2);
					gotoXY(71 + s, i);
					cout << (char)(186);
					Sleep(t2);
				}
				gotoXY(54 + s, 33);
				cout << (char)(201);
				gotoXY(54 + s, 37);
				cout << (char)(200);
				gotoXY(71 + s, 33);
				cout << (char)(187);
				gotoXY(71 + s, 37);
				cout << (char)(188);
				gotoXY(54 + s + 8, 35);
				cout << "YES";

			}
			else {
				textColor(3);
				for (int i = 55 + s; i <= 70 + s; ++i) {
					gotoXY(i, 33);
					cout << (char)(205);
					Sleep(t2);
					gotoXY(i, 37);
					cout << (char)(205);
					Sleep(t2);

				}
				for (int i = 34; i <= 36; ++i) {
					gotoXY(54 + s, i);
					cout << (char)(186);
					Sleep(t2);
					gotoXY(71 + s, i);
					cout << (char)(186);
					Sleep(t2);
				}
				gotoXY(54 + s, 33);
				cout << (char)(201);
				gotoXY(54 + s, 37);
				cout << (char)(200);
				gotoXY(71 + s, 33);
				cout << (char)(187);
				gotoXY(71 + s, 37);
				cout << (char)(188);
				gotoXY(54 + s + 8, 35);
				cout << "YES";
				textColor(RED);
				for (int i = 55 + s2; i <= 70 + s2 + 1; ++i) {
					gotoXY(i, 33);
					cout << (char)(205);
					Sleep(t2);
					gotoXY(i, 37);
					cout << (char)(205);
					Sleep(t2);
				}
				for (int i = 34; i <= 36; ++i) {
					gotoXY(54 + s2, i);
					cout << (char)(186);
					Sleep(t2);
					gotoXY(71 + s2, i);
					cout << (char)(186);
					Sleep(t2);
				}
				gotoXY(54 + s2, 33);
				cout << (char)(201);
				gotoXY(54 + s2, 37);
				cout << (char)(200);
				gotoXY(71 + s2, 33);
				cout << (char)(187);
				gotoXY(71 + s2, 37);
				cout << (char)(188);
				gotoXY(54 + s + 38, 35);
				cout << "NO";
			}

		}
		else if (key == 13 && temp1 % 2 == 1) {
			playGame(name, dateAndTime);
			break;
		}
		else if (key == 13 && temp1 % 2 == 0) {
			break;
		}

	}

	Sleep(t);
	return 1;
}

void pauseGame() {
	//Black board
	textFillColor(BLUE, BLACK);
	for (int j = 16; j <= 29; ++j) {
		gotoXY(27, j);
		cout << "                                                                                    ";
		Sleep(8);
	}

	//Horizontal border
	textFillColor(WHITE, BLACK);
	for (int i = 27; i <= 110; ++i) {
		gotoXY(i, 16);
		cout << (char)(205);
		gotoXY(i, 29);
		cout << (char)(205);
	}

	//Veritcal border
	for (int i = 17; i <= 28; ++i) {
		gotoXY(26, i);
		cout << (char)(186);
		gotoXY(110, i);
		cout << (char)(186);
	}

	gotoXY(26, 16); // Top right
	cout << (char)(201);

	gotoXY(26, 29); // Bottom right
	cout << (char)(200);

	gotoXY(110, 16); // Top left
	cout << (char)(187);

	gotoXY(110, 29); // Bottom left
	cout << (char)(188);

	//Graphic
	textFillColor(3, 64);
	int col1 = 29, row1 = 19;
	gotoXY(col1, row1++);
	wcout << L"██████   █████  ██    ██ ███████ ███████     ██████   █████  ███    ███ ███████ ";
	gotoXY(col1, row1++);
	wcout << L"██   ██ ██   ██ ██    ██ ██      ██         ██       ██   ██ ████  ████ ██      ";
	gotoXY(col1, row1++);
	wcout << L"██████  ███████ ██    ██ ███████ █████      ██   ███ ███████ ██ ████ ██ █████   ";
	gotoXY(col1, row1++);
	wcout << L"██      ██   ██ ██    ██      ██ ██         ██    ██ ██   ██ ██  ██  ██ ██      ";
	gotoXY(col1, row1++);
	wcout << L"██      ██   ██  ██████  ███████ ███████     ██████  ██   ██ ██      ██ ███████ ";

	//Text
	gotoXY(col1 + 22, row1 + 2);
	textFillColor(WHITE, BLACK);
	cout << "Press spacebar again to continue";
	textColor(snakeColor);
}
void loadGameGraphic() {
	system("cls");
	int t = 25;
	Sleep(t);
	textFillColor(12, BACKGROUND_COLOR);
	int col1 = 59, row1 = 18;
	gotoXY(col1, row1++);
	wcout << L"    __   ____  ___    ____     _________    __  _________";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"   / /  / __ \\/   |  / __ \\   / ____/   |  /  |/  / ____/";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"  / /  / / / / /| | / / / /  / / __/ /| | / /|_/ / __/   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L" / /__/ /_/ / ___ |/ /_/ /  / /_/ / ___ |/ /  / / /___   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"/_____|____/_/  |_/_____/   \\____/_/  |_/_/  /_/_____/   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1 - 2, row1++);
	textColor(12);
	cout << "Please input your name exactly to load game which you saved. ";
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 25 }, BLACK, 1, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 66, 27 }, { 20, 4 }, 4, 2, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 65, 26 }, { 21, 6 }, 4, 2, colorXY);
	Sleep(t);
	gotoXY(78, 29);
}

void loadGameGraphic(string& uName, string& password) {
	system("cls");
	int t = 25;
	Sleep(t);
	textFillColor(12, BACKGROUND_COLOR);
	int col1 = 50, row1 = 12;
	gotoXY(col1, row1++);
	wcout << L"██       ██████   █████  ██████       ██████   █████  ███    ███ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██      ██    ██ ██   ██ ██   ██     ██       ██   ██ ████  ████ ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██      ██    ██ ███████ ██   ██     ██   ███ ███████ ██ ████ ██ █████   ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██      ██    ██ ██   ██ ██   ██     ██    ██ ██   ██ ██  ██  ██ ██      ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"███████  ██████  ██   ██ ██████       ██████  ██   ██ ██      ██ ███████ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1, row1++);
	gotoXY(col1, row1++);
	textColor(12);
	cout << "Please input your name and password exactly to load game which you saved. ";
	Screen nameScreen;
	int e = 5;
	nameScreen.draw.retangle({ 25, 6 }, { 60, 30 }, BLACK, 1, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 72 - e, 22 }, { 20, 4 }, 3, 1, colorXY);
	Sleep(t);
	gotoXY(61 - e, 24);
	cout << "User name:";
	gotoXY(61 - e, 29);
	cout << "Password:";
	nameScreen.draw.retangle({ 72 - e, 27 }, { 20, 4 }, 3, 1, colorXY);
	Sleep(t);
	gotoXY(84 - e, 24);
	//presentCursor();
	SetCursorSize(1);
	char* tmpPassword = new char[30];
	password = "                                  ";
	cin >> uName;
	gotoXY(84 - e, 29);
	int n = 0;
	int g = 0;
	for (int i = 0; i < 30; i++) {
		if (_kbhit) {
			int key = _getch();
			if (key != 13 && key != 8) {
				gotoXY(84 + g - e, 29);
				cout << "*";
				password[n] = (char)key;
				n++;
				g++;
			}
			else if (key == 8) {
				password[n] = NULL;
				if (n > 0) n--;
				if (g > 0) g--;
				gotoXY(84 + g - e, 29);
				cout << " ";
				gotoXY(84 + g - e, 29);

			}
			else break;
		}

	}
	password.resize(n);
	hideCursor();
}

void loadingGameGraphic() {
	int t = 25;
	int col1 = 50, row1 = 18;
	textColor(BLACK);
	gotoXY(col1, row1++);
	wcout << L"██          ██████      █████     ██████     ██    ███    ██     ██████  ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██         ██    ██    ██   ██    ██   ██    ██    ████   ██    ██       ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██         ██    ██    ███████    ██   ██    ██    ██ ██  ██    ██   ███ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██         ██    ██    ██   ██    ██   ██    ██    ██  ██ ██    ██    ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"███████     ██████     ██   ██    ██████     ██    ██   ████     ██████     ██  ██  ██";
	Sleep(t);
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 25 }, BLACK, 1, colorXY);
	nameScreen.draw.retangle({ 62, 28 }, { 28, 2 }, BLACK, 1, colorXY);
	int g = 100;
	for (int i = 63; i < 63 + 28 * 2; i++) {
		gotoXY(i++, 29);
		cout << (char)254;
		Sleep(g);
	}
	system("cls");
	playSound(L"resources/countdown.wav");
	int u = 20;
	int y = 80;
	int col2 = y, row2 = u;
	textColor(BLACK);
	gotoXY(col2, row2++);
	wcout << L"██████  ";
	gotoXY(col2, row2++);
	wcout << L"     ██ ";
	gotoXY(col2, row2++);
	wcout << L" █████  ";
	gotoXY(col2, row2++);
	wcout << L"     ██ ";
	gotoXY(col2, row2++);
	wcout << L"██████  ";
	Sleep(1000);
	system("cls");


	col2 = y;
	row2 = u;
	gotoXY(col2, row2++);
	wcout << L"██████  ";
	gotoXY(col2, row2++);
	wcout << L"     ██ ";
	gotoXY(col2, row2++);
	wcout << L" █████  ";
	gotoXY(col2, row2++);
	wcout << L"██      ";
	gotoXY(col2, row2++);
	wcout << L"███████ ";
	Sleep(1000);
	system("cls");


	col2 = y;
	row2 = u;
	gotoXY(col2, row2++);
	wcout << L" ██ ";
	gotoXY(col2, row2++);
	wcout << L"███ ";
	gotoXY(col2, row2++);
	wcout << L" ██ ";
	gotoXY(col2, row2++);
	wcout << L" ██ ";
	gotoXY(col2, row2++);
	wcout << L" ██ ";
	Sleep(1000);
	system("cls");

	col2 = y - 10;
	row2 = u;
	gotoXY(col2, row2++);
	wcout << L" ██████      ██████     ██ ";
	gotoXY(col2, row2++);
	wcout << L"██          ██    ██    ██ ";
	gotoXY(col2, row2++);
	wcout << L"██   ███    ██    ██    ██ ";
	gotoXY(col2, row2++);
	wcout << L"██    ██    ██    ██       ";
	gotoXY(col2, row2++);
	wcout << L" ██████      ██████     ██ ";
	Sleep(1000);
}

void saveGameGraphic() {
	system("cls");
	int t = 25;
	Sleep(t);
	textFillColor(12, BACKGROUND_COLOR);
	int col1 = 50, row1 = 22;
	gotoXY(col1, row1++);
	wcout << L" ██████   █████  ███    ███ ███████     ███████  █████  ██    ██ ███████ ██████  ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██       ██   ██ ████  ████ ██          ██      ██   ██ ██    ██ ██      ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██   ███ ███████ ██ ████ ██ █████       ███████ ███████ ██    ██ █████   ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██    ██ ██   ██ ██  ██  ██ ██               ██ ██   ██  ██  ██  ██      ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L" ██████  ██   ██ ██      ██ ███████     ███████ ██   ██   ████   ███████ ██████  ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1 - 2, row1++);
	textColor(12);
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 25 }, BLACK, 1, colorXY);
	gotoXY(78, 29);
}

void fillPassword (string& key) {
	system("cls");
	int t = 25;
	Sleep(t);
	textFillColor(3, BACKGROUND_COLOR);
	int col1 = 55, row1 = 18;
	gotoXY(col1, row1++);
	wcout << L"██████   █████  ███████ ███████ ██     ██  ██████  ██████  ██████  ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██   ██ ██   ██ ██      ██      ██     ██ ██    ██ ██   ██ ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██████  ███████ ███████ ███████ ██  █  ██ ██    ██ ██████  ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██      ██   ██      ██      ██ ██ ███ ██ ██    ██ ██   ██ ██   ██ ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"██      ██   ██ ███████ ███████  ███ ███   ██████  ██   ██ ██████  ";
	Sleep(t);
	gotoXY(col1, row1++);
	wcout << L"                                                                            ";
	Sleep(t);
	gotoXY(col1 + 5, row1++);
	textColor(3);
	cout << "Please fill in your password in the blanks below to save game. ";
	Screen nameScreen;
	nameScreen.draw.retangle({ 30, 12 }, { 60, 25 }, 12, 1, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 66, 27 }, { 20, 4 }, 3, 2, colorXY);
	Sleep(t);
	nameScreen.draw.retangle({ 65, 26 }, { 21, 6 }, 3, 2, colorXY);
	Sleep(t);
	gotoXY(78, 29);
	textColor(3);
	cin >> key;
}
	