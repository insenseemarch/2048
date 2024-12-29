#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include "Header.h"
// Including all of file.cpp's functions

void loadGameState(Stack& undoStack, Stack& redoStack, PlayerInfo& player, int& size, string filename, bool& on_1, bool& on_2);
int changeSaveFile();
int existResume(Stack undoStack, Stack redoStack, PlayerInfo player, int size);
int existResume12();
int sameResumeName(Stack undoStack, Stack redoStack, PlayerInfo player, int size, string name);
void saveGameState(Stack undoStack, Stack redoStack, PlayerInfo player, int size, string filename, bool on_1, bool on_2);
void xorEncrypt(char* data, int size);

#endif