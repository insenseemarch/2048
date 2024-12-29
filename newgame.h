#pragma once
#ifndef _NEWGAME_H_
#define _NEWGAME_H_

#include "Header.h"
// Including all of newgame.cpp's functions

void playGame1(int** a, int** p, int size, PlayerInfo player, GameInfo map, int check, int counter, double add, Stack undoStack, Stack redoStack);
bool isNameExist(string playerName, string filename);

#endif

