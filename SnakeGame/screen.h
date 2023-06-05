#pragma once
#include "graphic.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

// Define console
#define WIDTH 1284
#define HEIGHT 760
extern string colorXY[205][85];
extern short snakeColor;

struct Screen {

    void clear() {
        system("cls");
    }
    
    Screen() {
        for (int i = 0; i < 150; ++i) {
            for (int j = 0; j < 55; ++j) {
                colorXY[i][j] = "GRAY";
            }
        }
    }

    struct Draw {
        #define width first
        #define height second
        void retangle(const pair<int, int> topLeft, const pair<int, int> dimension, int color, int thickness, string colorXY[205][85]) {
            textColor(color);
            for (int i = topLeft.first; i <= topLeft.first + (dimension.width * 2); ++i) {
                if (thickness == 2) {
                    gotoXY(i, topLeft.second);
                    printf("%c", 219);

                    gotoXY(i, topLeft.second + dimension.height);
                    colorXY[i][topLeft.second + dimension.height] = "DANGER";
                    printf("%c", 219);
                }
                else if (thickness == 1) {
                    gotoXY(i, topLeft.second);
                    colorXY[i][topLeft.second] = "DANGER";
                    printf("%c", 220);

                    gotoXY(i, topLeft.second + dimension.height);
                    colorXY[i][topLeft.second + dimension.height] = "DANGER";
                    printf("%c", 223);
                }
            }

            for (int i = topLeft.second; i <= topLeft.second + dimension.height; ++i) {
                if (thickness == 2) {
                    gotoXY(topLeft.first, i);
                    printf("%c%c", 219, 219);

                    gotoXY(topLeft.first + (dimension.width * 2), i);
                    colorXY[topLeft.first + (dimension.width * 2)][i] = "DANGER";
                    colorXY[topLeft.first + (dimension.width * 2) + 1][i] = "DANGER";
                    printf("%c%c", 219, 219);
                }
                else if (thickness == 1) {
                    if (i != topLeft.second && i != topLeft.second + dimension.height) {
                        gotoXY(topLeft.first, i);
                        colorXY[topLeft.first][i] = "DANGER";
                        printf("%c", 219);

                        gotoXY(topLeft.first + (dimension.width * 2), i);
                        colorXY[topLeft.first + (dimension.width * 2)][i] = "DANGER";
                        printf("%c", 219);
                    }
                }
            }
        }

    } draw;

    void resetScreenColor(string colorXY[205][85]) {
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < 85; ++j) {
                colorXY[i][j] = "SAFE";
            }
        }
    }
};
