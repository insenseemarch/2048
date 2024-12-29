#include "Header.h"

const char XOR_KEY = 0xFF;

// XOR Encryption
void xorEncrypt(char* data, int size) 
{
	for (int i = 0; i < size; ++i) 
	{
		data[i] ^= XOR_KEY;
	}
}

// Ham giai phong bo nho 
void cleanupMap(int** map, int size) 
{
	for (int i = 0; i < size; i++) 
	{
		delete[] map[i];
	}
	delete[] map;
	map = nullptr;
}

// Tai thong tin nguoi choi len
// Read players' informations
void loadGameState(Stack& undoStack, Stack& redoStack, PlayerInfo& player, int& size, string filename, bool &on_1, bool& on_2)
{
	undoStack.clear(size);
	redoStack.clear(size);

	int score = 0;
	ifstream savegame(filename, ios::binary);
	if (!savegame)
	{
		cout << "Cannot open file for reading!" << endl;
		return;
	}

	savegame.read(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));
	// Giai ma doan du lieu da ma hoa
	// Decode the encrypted data
	xorEncrypt(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));

	savegame.read(reinterpret_cast<char*>(&size), sizeof(int));

	int undo_size = 0;
	savegame.read(reinterpret_cast<char*>(&undo_size), sizeof(int));
	xorEncrypt(reinterpret_cast<char*>(&undo_size), sizeof(int));

	int redo_size = 0;
	savegame.read(reinterpret_cast<char*>(&redo_size), sizeof(int));

	for (int i = 0; i < undo_size; i++)
	{
		int score_tmp = 0;
		savegame.read(reinterpret_cast<char*>(&score_tmp), sizeof(int));
		int** map = new int* [size];

		for (int j = 0; j < size; j++)
		{
			map[j] = new int[size];
			savegame.read(reinterpret_cast<char*>(map[j]), size * sizeof(int));
		}
		// Them vao undoStack theo thu tu FIFO
		// Add to undoStack in FIFO order
		undoStack.push_readFile(map, score_tmp);
		
	}

	for (int j = 0; j < redo_size; j++)
	{
		int score_tmp = 0;
		savegame.read(reinterpret_cast<char*>(&score_tmp), sizeof(int));

		int** map = new int* [size];

		for (int j = 0; j < size; j++)
		{
			map[j] = new int[size];
			savegame.read(reinterpret_cast<char*>(map[j]), size * sizeof(int));
		}
		redoStack.push_readFile(map, score_tmp);
		
	}

	savegame.read(reinterpret_cast<char*>(&on_1), sizeof(bool));
	savegame.read(reinterpret_cast<char*>(&on_2), sizeof(bool));
	xorEncrypt(reinterpret_cast<char*>(&on_2), sizeof(bool));

	savegame.read(reinterpret_cast<char*>(&highScoreEver), sizeof(int));
	xorEncrypt(reinterpret_cast<char*>(&highScoreEver), sizeof(int));


	savegame.close();
}

// Ham tra ve vi tri nguoi dung muon luu du lieu cua minh de len
// The function returns the location where the user wants to save their data
int changeSaveFile()
{
tryagain:
	{
		drawFrame(18,46);

		gotoyx(5, 46);
		cout << "The saving slots are now full.";
		gotoyx(6, 40);
		cout << "Please choose one ID you want to replace:" << endl;
		int Set[] = { 7,7,7, 7, 7 }; // Default colors
		int counter = 1;
		char key;

		for (int i = 0;;)
		{
			gotoyx(8, 46);
			color(Set[0]);
			cout << "1. Player: " << resumeName[0] << endl;

			gotoyx(9, 46);
			color(Set[1]);
			cout << "2. Player: " << resumeName[1] << endl;

			gotoyx(10, 46);
			color(Set[2]);
			cout << "3. Player: " << resumeName[2] << endl;

			gotoyx(11, 46);
			color(Set[3]);
			cout << "4. Player: " << resumeName[3] << endl;

			gotoyx(12, 46);
			color(Set[4]);
			cout << "5. Player: " << resumeName[4] << endl;

			gotoyx(14, 43);
			color(7);
			cout << "Or press [x] to exit (no saving game).";
			key = _getch();
			if (key == -32 || key == 224)
			{
				key = _getch();
			}

				if (key == 72 && (counter >= 2 && counter <= 5)) // 72 = up arrow key
				{
					counter--;
				}
				else if (key == 80 && (counter >= 1 && counter <= 4)) // 80 = down arrow key
				{
					counter++;
				}

				else if (key == '\r') 
				{
					if (counter == 1)
					{
						system("cls");
						return 1;
					}
					else if (counter == 2)
					{
						system("cls");
						return 2;
					}
					else if (counter == 3)
					{
						system("cls");
						return 3;
					}
					else if (counter == 4)
					{
						system("cls");
						return 4;
					}
					else if (counter == 5)
					{
						system("cls");
						return 5;
					}
				}
				else if (key == 'x')
				{
					system("cls");
					drawFrame(18,46);
					gotoyx(10, 43);
					color(7);
					cout << "Thanks for your time! See you again!" << endl;
					gotoyx(20, 38);
					exit(0);
				}
				else
				{
					if (counter != 1 && counter != 5)
					{
						gotoyx(16, 43);
						color(12);
						cout << "Invalid entry!";
						color(7);
						gotoyx(17, 43);
						system("pause");
						system("cls");
						counter = 1;
						key = '\0';
						goto tryagain;
					}
				}
			if (check == true)
			{
				system("cls");
				break;
			}
			else
			{
				Set[0] = 7; 
				Set[1] = 7;
				Set[2] = 7;
				Set[3] = 7;
				Set[4] = 7;
				if (counter == 1)
				{
					Set[0] = 14; 
				}
				if (counter == 2)
				{
					Set[1] = 14; 
				}
				if (counter == 3)
				{
					Set[2] = 14; 
				}
				if (counter == 4)
				{
					Set[3] = 14; 
				}
				if (counter == 5)
				{
					Set[4] = 14; 
				}
			}
		}
	}
}

// Dem so luong nguoi choi da dung resume
// Count the number of players who have chosen resume
int existResume(Stack undoStack, Stack redoStack, PlayerInfo player, int size)
{
	fstream input;
	int count = 0;
	for (int i = 1; i <= 5; i++)
	{
		input.open("player" + to_string(i) + ".bin", ios::in);
		if (input)
		{
			count++;
			input.close();
		}
	}
	return count;
}

// Ham dung de tra ve vi tri nguoi dung muon luu
int existResume12()
{
	fstream input;
	int count = 0;
	for (int i = 1; i <= 5; i++)
	{
		input.open("player" + to_string(i) + ".bin", ios::in);
		if (input)
		{
			count++;
			input.close();
		}
	}
	if (count == 5)
	{
		system("cls");
		return (changeSaveFile() - 1);
	}
	return count;
}

// Ham kiem tra neu trong danh sach Resume da co ten hien tai thi tra ve vi tri file do
// The function checks if the Resume list already has the same name as the current one, then return that file's position
int sameResumeName(Stack undoStack, Stack redoStack, PlayerInfo player, int size, string name)
{
	for (int i = 1; i <= existResume(undoStack, redoStack, player, size); i++)
	{
		ifstream savegame("player" + to_string(i) + ".bin", ios::binary);
		savegame.read(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));
		xorEncrypt(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));

		if (name == player.name)
		{
			return i;
		}
		savegame.close();
	}
	return 0;
}

void saveGameState(Stack undoStack, Stack redoStack, PlayerInfo player, int size, string filename, bool on_1, bool on_2)
{
	// ios::trunc checks if that file has already have data, then delete all of that data
	ofstream savegame(filename, ios::binary | ios::trunc);
	if (!savegame.is_open())
	{
		cerr << "Can not open file to save." << endl;
		return;
	}

	// XOR encryption
	xorEncrypt(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));
	savegame.write(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));
	savegame.write(reinterpret_cast<char*>(&size), sizeof(int));
	
	int undo_size = undoStack.getsize();
	xorEncrypt(reinterpret_cast<char*>(&undo_size), sizeof(int));
	savegame.write(reinterpret_cast<char*>(&undo_size), sizeof(int));

	int redo_size = redoStack.getsize();
	savegame.write(reinterpret_cast<char*>(&redo_size), sizeof(int));

	Node* node1 = undoStack.head;
	while (node1)
	{
		savegame.write(reinterpret_cast<char*>(&node1->score), sizeof(int));
		for (int i = 0; i < size; i++)
		{
			savegame.write(reinterpret_cast<char*>(node1->map[i]), size * sizeof(int));
		}
		node1 = node1->next;
	}

	Node* node2 = redoStack.head;
	while (node2)
	{
		savegame.write(reinterpret_cast<char*>(&node2->score), sizeof(int));
		for (int i = 0; i < size; i++)
		{
			savegame.write(reinterpret_cast<char*>(node2->map[i]), size * sizeof(int));
		}
		node2 = node2->next;
	}

	savegame.write(reinterpret_cast<char*>(&on_1), sizeof(bool));
	xorEncrypt(reinterpret_cast<char*>(&on_2), sizeof(bool));
	savegame.write(reinterpret_cast<char*>(&on_2), sizeof(bool));

	xorEncrypt(reinterpret_cast<char*>(&highScoreEver), sizeof(int));
	savegame.write(reinterpret_cast<char*>(&highScoreEver), sizeof(int));


	savegame.close();
}