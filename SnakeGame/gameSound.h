#pragma once
#pragma comment(lib, "winmm.lib")
#include <string>
#include <windows.h> 
#include <iostream>
#include <mmsystem.h>

// Play sound from path
void playSound(LPCWSTR path);

void playSoundLoop(LPCWSTR path);

void turnOffSound();