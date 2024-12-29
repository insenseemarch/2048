#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include "Header.h"
// Including all of menu.cpp's functions

void start();
void menu1(PlayerInfo& player, Stack& undoStack, Stack& redoStack, int& check, int& counter, int& size);
int unreOption(bool& on_1, bool& on_2, int size);
void gameSetting(int& size, int& option);
void drawFrame(int max_y, int max_x);
void gameResume(Stack& undoStack, Stack& redoStack, PlayerInfo& player, int& size, int numPlayers);
int languageOption(bool& eng, bool& viet, int size);
int sizeOfGame();

#endif
