#pragma once
#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <windows.h> // Console screen format
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <mmsystem.h>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <thread>
#include <cstring>

using namespace std;

struct PlayerInfo
{
	char name[21];
	int score = 0;
	double time = 0;
};

struct GameInfo
{
	int** currentMap;
	int size = 0;
	int currentScore = 0;

	~GameInfo() 
	{
		if (currentMap != nullptr) 
		{
			for (int i = 0; i < size; i++) 
			{
				delete[] currentMap[i];
			}
			delete[] currentMap;
		}
	}

};

struct Node
{
	int** map;
	int score;
	Node* next;

	Node(int** data, int score)
	{
		this->map = data;
		this->score = score;
		this->next = NULL;
	}
};

struct Stack // Last in first out
{
	Node* head = NULL;
	int size = 0;

	bool isEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return 0;
	}

	bool firstMove()
	{
		if (head->next == NULL)
		{
			return true;
		}
		return 0;
	}

	void push(int** data, int score)
	{
		Node* p = new Node(data, score);
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			p->next = head;
			head = p;
		}
		size++;
	}

	void push_readFile(int** data, int score)
	{
		Node* p = new Node(data, score);
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			Node* node = head;
			while (node->next != NULL)
			{
				node = node->next;
			}
			node->next = p;
		}
		size++;
	}

	Node* pop()
	{
		if (isEmpty())
		{
			return NULL;
		}
		else
		{
			Node* tmp = head;
			head = head->next;
			size--;
			return tmp;
		}
	}

	Node* top()
	{
		if (isEmpty())
		{
			return NULL;
		}
		else
		{
			return head;
		}
	}

	int getsize()
	{
		return size;
	}

	void clear(int map_size)
	{
		Node* node = head;
		while (node != nullptr)
		{
			Node* next = node->next;
			cleanupMap(node->map, map_size);
			delete node;
			node = next;
		}
		head = nullptr;
		size = 0;
	}


	void cleanupMap(int** map, int size) 
	{
		for (int i = 0; i < size; i++) 
		{
			delete[] map[i];
		}
		delete[] map;
		map = nullptr;
	}
};

struct Node2
{
	PlayerInfo data;
	Node2* next;
};

// ADDITION:
extern bool check;
extern bool on_1;
extern bool on_2;
extern bool resume;
extern char** resumeName;
extern bool tryagain;
extern PlayerInfo top_players[40];
extern bool eng;
extern bool viet;
extern const char XOR_KEY;
extern int highScoreEver;

#include "file.h"
#include "gamelogic.h"
#include "graphic.h"
#include "menu.h"
#include "newgame.h"


#endif
