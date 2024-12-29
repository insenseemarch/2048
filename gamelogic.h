#pragma once

#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "Header.h"
// Including all of gamelogic.cpp's functions

void writePlayerInfo(PlayerInfo& player, string filename);
bool compareScores(PlayerInfo a, PlayerInfo b);
bool isNameExist(string playerName, string filename);
void addPlayer(Node2*& head2, PlayerInfo player);
Node2* readPlayersfromFile(string filename);
int findPlayerRank(Node2* head2, string playerName);
int findBestScore(PlayerInfo player, string filename);
int** createMap(int size);
int moveLeft(int** a, int size);
int moveRight(int** a, int size);
int moveUp(int** a, int size);
int moveDown(int** a, int size);
void printMatrix(int** a, int size);
int check1(int** a, int** tmp, int size);
void addBlock(int** a, int size);
int gameOver(int** a, int size);
void printScore(PlayerInfo player, int score, int size);
void copyMap(int** a, int** b, int size);
void pushState(Stack& undoStack, Stack& redoStack, int** a, int size, int score);
void undo(Stack& undoStack, Stack& redoStack, int**& a, int size, int& score);
void redo(Stack& undoStack, Stack& redoStack, int**& a, int size, int& score);
bool sameMap(int** a, int** p, int size);
bool checkWin(int** a, int size);
bool isValidChar(char ch);
bool isValidName(string s);
void removeDuplicateNames(PlayerInfo players[], int& numPlayers);
void cleanupMap(int** map, int size);
void printRank(PlayerInfo player, string filename);
int swapInfo(PlayerInfo player, string filename);

#endif
