#pragma once
#include "gameSound.h"

void playSound(LPCWSTR path){
    PlaySound(path, NULL, SND_ASYNC);
}

void playSoundLoop(LPCWSTR path) {
    PlaySound(path, NULL, SND_LOOP | SND_ASYNC);
}

void turnOffSound() {
    PlaySound(NULL, NULL, NULL);
}