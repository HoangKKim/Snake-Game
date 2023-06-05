#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")

// Standard library
#include <thread>
#include <map>
#include <string>
#include <iostream>
#include <conio.h>
#include <iostream>
#include <windows.h>  
#include <mmsystem.h>
#include <winuser.h>
#include <future>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <fstream>
#include <ctime>

// Custom library
#include "graphic.h"
#include "screen.h"
#include "gameSound.h"
#include "menu.h"
#include "snake.h"

void setup();

void mainMenu();