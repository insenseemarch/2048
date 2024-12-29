#pragma once
#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "Header.h"
// Including all of graphic.cpp's functions

void LockConsoleSize(SHORT width, SHORT height);
void color(int color);
void gotoyx(int y, int x);
int getThingColor(string c);
string mapThing(int y, int x, int max_y, int max_x);
int getValColor(int val);
void Draw1(int** a, int size);
void helloScreen();
string borderHelloScreen(int y, int x, int max_y, int max_x);

#endif
