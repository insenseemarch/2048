#include "Header.h"

PlayerInfo top_players[40];

// Ghi ten, diem, thoi gian hoan thanh cua nguoi choi vao file
// Save the player's name, score, time into file
void writePlayerInfo(PlayerInfo& player, string filename)
{
	ofstream file(filename, ios::binary | ios::app);
	file.write(reinterpret_cast<char*>(&player), sizeof(PlayerInfo));
	file.close();
}

bool compareScores(PlayerInfo a, PlayerInfo b)
{
	if (a.score == b.score)
	{
		if (strcmp(a.name, b.name) == 0)
		{
			return a.time > b.time;
		}
		return a.time < b.time;
	}
	return a.score > b.score;
}

void addPlayer(Node2*& head2, PlayerInfo player)
{
	Node2* newNode = new Node2{ player, nullptr };

	if (!head2 || head2->data.score < player.score)
	{
		newNode->next = head2;
		head2 = newNode;
	}
	else
	{
		Node2* current = head2;
		while (current->next && current->next->data.score >= player.score)
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

// Dua nguoi choi hien tai vao mot Node da duoc sap xep theo diem
Node2* readPlayersfromFile(string filename)
{
	ifstream file(filename, ios::binary);
	PlayerInfo player;
	Node2* head2 = nullptr;
	while (file.read((char*)&player, sizeof(PlayerInfo)))
	{
		addPlayer(head2, player);
	}
	file.close();
	return head2;
}

int findPlayerRank(Node2* head2, string playerName)
{
	int rank = 1;
	Node2* node2 = head2;
	while (node2)
	{
		if (node2->data.name == playerName)
		{
			return rank;
		}
		node2 = node2->next;
		rank++;
	}
	return -1;
}

void removeDuplicateNames(PlayerInfo players[], int& numPlayers) 
{
	for (int i = 0; i < numPlayers-1; ++i) 
	{
		for (int j = i + 1; j < numPlayers; ) 
		{
			if (strcmp(players[i].name, players[j].name) == 0) 
			{
				// Xoa ten trung lap bang cach dich chuyen cac phan tu
				// Remove duplicate names by shifting elements
				for (int k = j; k < numPlayers - 1; ++k) 
				{
					players[k] = players[k + 1];
				}
				--numPlayers; 
			}
			else 
			{
				++j; 
			}
		}
	}
}

int swapInfo(PlayerInfo player, string filename)
{
	int numPlayers = 0;
	ifstream file(filename, ios::binary);
	while (file.read(reinterpret_cast<char*>(&player), sizeof(PlayerInfo)))
	{
		if (numPlayers < 500)
		{
			top_players[numPlayers++] = player;
		}
		else
		{
			int minScoreIndex = 0;
			for (int i = 1; i < 500; ++i)
			{
				// Tim nguoi choi co diem thap nhat trong 40 nguoi
				if (top_players[i].score < top_players[minScoreIndex].score)
				{
					minScoreIndex = i;
				}
				// Truong hop hai nguoi bang diem nhau
				else if (top_players[i].score == top_players[minScoreIndex].score)
				{
					// Neu da co ten nguoi do trong danh sach (nghia la da chon resume) thi xep lan co thoi gian choi lau hon len tren (cong don thoi gian)
					if (strcmp(top_players[i].name, top_players[minScoreIndex].name) == 0)
					{
						if (top_players[i].time < top_players[minScoreIndex].time)
						{
							minScoreIndex = i;
						}
					}
					// Neu trong danh sach khong trung ten thi xep nguoi choi co thoi gian ngan hon len tren
					else
					{
						if (top_players[i].time > top_players[minScoreIndex].time)
						{
							minScoreIndex = i;
						}
					}
					
				}
				/*if (top_players[i].name == top_players[minScoreIndex].name)
				{
					if (top_players[i].time < top_players[minScoreIndex].time)
					{
						minScoreIndex = i;
					}
				}*/
			}
			// Neu nguoi choi moi co diem cao hon nguoi thap nhat, thay diem nguoi thap nhat bang diem nguoi choi moi
			if (player.score > top_players[minScoreIndex].score)
			{
				top_players[minScoreIndex] = player;
			}
			else if (player.score == top_players[minScoreIndex].score)
			{
				if (strcmp(player.name, top_players[minScoreIndex].name) == 0)
				{
					if (player.time > top_players[minScoreIndex].time)
					{
						top_players[minScoreIndex] = player;
					}
				}
				else
				{
					if (player.time < top_players[minScoreIndex].time)
					{
						top_players[minScoreIndex] = player;
					}
				}
			}
		}
	}
	// compareScores cho ve ket qua sap xep giam dan
	sort(top_players, top_players + numPlayers, compareScores);
	removeDuplicateNames(top_players, numPlayers);
	return numPlayers;
}

void printRank(PlayerInfo player, string filename)
{
	int numPlayers = swapInfo(player, filename);

	gotoyx(2, 31);
	cout << "_____________________________________________________";
	gotoyx(3, 31);
	cout << "Rank  Player ID                 Score      Time   ";
	gotoyx(4, 31);
	cout << "_____________________________________________________";
	int pos = 5;
	int numtoPrint = min(numPlayers, 20);
	for (int i = 0; i < numtoPrint; ++i)
	{
		if (i == 0)
		{
			color(9);
		}
		gotoyx(pos, 31);
		cout << i + 1;
		gotoyx(pos, 37);
		cout << top_players[i].name;
		gotoyx( pos,65);
		cout << top_players[i].score;
		gotoyx(pos,74);
		int minutes = (top_players[i].time) / 60;
		int seconds = (int)(top_players[i].time) % 60;
		cout << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
		
		if (i == 0)
		{
			if (top_players[0].score < highScoreEver && highScoreEver >0)
			{
				gotoyx(pos, 87);
				color(112);
				cout << "Highest score: " << highScoreEver;
			}
			color(7);
		}
		pos++; 

	}
	for (int i = numtoPrint; i < 20; i++)
	{
		color(8);
		gotoyx(pos++, 31);
		cout << i + 1;
	}
	color(7);
	gotoyx( pos++,31);
	cout << "_____________________________________________________";
	gotoyx(pos, 31);
}

int highScoreEver = 0;
int findBestScore(PlayerInfo player, string filename)
{
	PlayerInfo top_players[20];
	PlayerInfo player2;
	int numPlayers = 0;
	ifstream file(filename, ios::binary);
	while (file.read(reinterpret_cast<char*>(&player2), sizeof(PlayerInfo)))
	{
		if (numPlayers < 20)
		{
			top_players[numPlayers++] = player2;
		}
		else
		{
			int minScoreIndex = 0;
			for (int i = 1; i < 20; ++i)
			{
				if (top_players[i].score < top_players[minScoreIndex].score)
				{
					minScoreIndex = i;
				}
			}
			if (player2.score > top_players[minScoreIndex].score)
			{
				top_players[minScoreIndex] = player2;
			}
		}
	}

	// S?p x?p danh sách theo ?i?m gi?m d?n
	sort(top_players, top_players + numPlayers, compareScores);
	if (top_players[0].score > highScoreEver)
	{
		highScoreEver = top_players[0].score;
	}
	if (player.score > highScoreEver)
	{
		highScoreEver = player.score;
		/*ofstream fileOut(filename, ios::binary | ios::trunc);
		for (int i = 0; i < numPlayers; ++i)
		{
			fileOut.write((char*)(&top_players[i]), sizeof(PlayerInfo));
		}*/
	}
	file.close();
	return highScoreEver;
}

int** createMap(int size)
{
	int** a = new int* [size];
	for (int i = 0; i < size; i++)
	{
		a[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			a[i][j] = 0;
		}
	}
	return a;
}

int moveLeft(int** a, int size) 
{
	int addingScore = 0;

	bool** combined = new bool* [size];
	for (int i = 0; i < size; i++)
	{
		combined[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			combined[i][j] = false;
		}
	}

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			if (a[i][j] > 0)
			{
				int x = j;
				while (x >= 1) 
				{
					// Kiem tra neu ben trai so do bang 0
					if (a[i][x-1] == 0) 
					{
						// Gan vi tri ben trai bang gia tri vi tri ben phai
						a[i][x - 1] = a[i][x];
						// Gan vi tri ben phai bang 0
						a[i][x] = 0;
						x--; // Tiep tuc di ve phai trai cua so do
					}
					// Kiem tra neu so ben trai bang so ben phai
					else if (a[i][x-1] == a[i][x] && !combined[i][x-1])
					{
						// Diem se bang so ben phai * 2
						addingScore += a[i][x] * 2;
						// So ben trai bang so ben phai * 2
						a[i][x - 1] = a[i][x] * 2;
						// So ben phai bang 0
						a[i][x] = 0;
						combined[i][x - 1] = true;
						break;
					}
					else 
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		delete[] combined[i];
	}
	delete[] combined;
	return addingScore;
}

int moveRight(int** a, int size) 
{
	int addingScore = 0;

	// Khoi tao mang phu de theo doi cac o da gop
	bool** combined = new bool* [size];
	for (int i = 0; i < size; i++) 
	{
		combined[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			combined[i][j] = false;
		}
	}


	for (int i = 0; i < size; i++) 
	{
		for (int j = size - 1; j > 0; j--) 
		{
			if (a[i][j] == 0)
			{
				continue;
			}

			int x = j - 1;
			while (x >= 0 && a[i][x] == 0) 
			{ 
				// Tim mot o khong phai bang 0 de so sanh
				x--;
			}

			if (x >= 0 && a[i][x] == a[i][j] && !combined[i][x]) 
			{
				addingScore += a[i][j] * 2;
				a[i][j] *= 2;
				a[i][x] = 0;
				combined[i][j] = true; 
			}
		}

		// Di chuyen cac o ve ben phai
		for (int j = size - 1; j >= 0; j--) 
		{
			if (a[i][j] == 0) 
			{
				int x = j - 1;
				while (x >= 0 && a[i][x] == 0) 
				{
					x--;
				}
				if (x >= 0) {
					a[i][j] = a[i][x];
					a[i][x] = 0;
				}
			}
		}
	}

	for (int i = 0; i < size; i++) 
	{
		delete[] combined[i];
	}
	delete[] combined;

	return addingScore;
}

int moveUp(int** a, int size) 
{
	int addingScore = 0;

	bool** combined = new bool* [size];
	for (int i = 0; i < size; i++) 
	{
		combined[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			combined[i][j] = false;
		}
	}
	for (int j = 0; j < size; j++) 
	{
		for (int i = 0; i < size; i++) 
		{
			if (a[i][j] > 0)
			{
				int y = i;
				while (y > 0) 
				{
					if (a[y-1][j] == 0)
					{
						a[y - 1][j] = a[y][j];
						a[y][j] = 0;
						y--;
					}
					else if (a[y-1][j] == a[y][j] && !combined[y-1][j])
					{
						addingScore += a[y][j] * 2;
						a[y - 1][j] = a[y][j] * 2;
						a[y][j] = 0;
						combined[y - 1][j] = true;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < size; i++) 
	{
		delete[] combined[i];
	}
	delete[] combined;
	return addingScore;
}

int moveDown(int** a, int size) 
{
	int addingScore = 0;

	bool** combined = new bool* [size];
	for (int i = 0; i < size; i++) 
	{
		combined[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			combined[i][j] = false;
		}
	}

	for (int j = 0; j < size; j++) 
	{
		for (int i = size - 1; i >= 0; i--) 
		{
			if (a[i][j] > 0)
			{
				int y = i;
				while (y < size - 1) 
				{
					if (a[y+1][j] == 0)
					{
						a[y + 1][j] = a[y][j];
						a[y][j] = 0;
						y++;
					}
					else if (a[y+1][j] == a[y][j] && !combined[y+1][j])
					{
						addingScore += a[y][j] * 2;
						a[y + 1][j] = a[y][j] * 2;
						a[y][j] = 0;
						combined[y + 1][j] = true;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < size; i++) 
	{
		delete[] combined[i];
	}
	delete[] combined;
	return addingScore;

}

void printMatrix(int** a, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

int check1(int** a, int** tmp, int size)
{
	int temp = 1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Kiem tra neu co su khac biet (di chuyen) giua hai mang thi tien hanh them vao o moi
			if (a[i][j]==0 || a[i][j] !=tmp[i][j])
			{
				temp = 0;
				break;
			}
		}
	}
	return temp;
}

void addBlock(int** a, int size)
{
	int pos1 = 0, pos2 = 0;
	srand(time(NULL));
	while (1)
	{
		pos1 = rand() % size; // Random a number from 0 to 3
		pos2 = rand() % size;
		if (a[pos1][pos2] == 0)
		{
			do
			{
				a[pos1][pos2] = 2 + rand() % 3; // Random a number from 2 to 4
			} while (a[pos1][pos2] == 3); // If that number is 3, random again
			break;
		}
	}
}

int gameOver(int** a, int size)
{
	int tmp1 = 0, tmp2 = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Neu co mot o bang 0 thi van con tiep tuc duoc
			if (a[i][j] == 0)
			{
				tmp1 = 1;
				break;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Xet 1 o, kiem tra o ben phai
			if (j < size - 1 && a[i][j] == a[i][j + 1])
			{
				tmp2 = 1;
				break;
			}
			// Xet 1 o, kiem tra o ben duoi
			if (i < size - 1 && a[i][j] == a[i + 1][j])
			{
				tmp2 = 1;
				break;
			}
			// Ben trai
			if (j > 0 && a[i][j] == a[i][j - 1])
			{
				tmp2 = 1;
				break;
			}
			// Ben tren
			if (i > 0 && a[i][j] == a[i - 1][j])
			{
				tmp2 = 1;
				break;
			}
		}
	}
	if (tmp1 || tmp2) // Neu co mot trong hai khac 0 thi choi tiep
	{
		return 0;
	}
	return 1; // Neu ca hai deu cung bang 0 (khong di chuyen duoc nua) thi da thua
}

void printScore(PlayerInfo player, int score, int size)
{
	color(10);
	gotoyx(size * 2 + 6, 0);
	cout << "Score: " << left << setw(10) << setfill(' ') << score;
	color(11);
	gotoyx(size * 2 + 7, 0);
	cout << "Top 1: " << findBestScore(player, "player_scores.bin") << endl;
}

void copyMap(int** a, int** b, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}


void pushState(Stack& undoStack, Stack& redoStack, int** a, int size, int score)
{
	int** copy = new int* [size];
	for (int i = 0; i < size; i++)
	{
		copy[i] = new int[size];
	}
	copyMap(a, copy, size);
	undoStack.push(copy, score); 
}

void undo(Stack& undoStack, Stack& redoStack, int**& a, int size, int& score)
{
	if (!undoStack.isEmpty())
	{
		Node* lastAction = undoStack.pop();
		redoStack.push(lastAction->map, lastAction->score);
		if (!undoStack.isEmpty())
		{
			Node* current = undoStack.top();
			copyMap(current->map, a, size);
			score = current->score;
		}
	}
}

void redo(Stack& undoStack, Stack& redoStack, int**& a, int size, int& score)
{
	if (!redoStack.isEmpty())
	{
		Node* lastUndoAction = redoStack.pop();
		undoStack.push(lastUndoAction->map, lastUndoAction->score);
		copyMap(lastUndoAction->map, a, size);
		score = lastUndoAction->score;
	}
}

bool sameMap(int** a, int** p, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (p[i][j] != a[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool checkWin(int** a, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (a[i][j] == 2048)
			{
				return true;
			}
		}
	}
	return false;
}

bool isValidChar(char ch)
{
	// isalnum kiem tra so va chu cai, 32 la dau cach, '\n' la dau enter
	// isalnum return true if it is a letter or a number, 32 stands for space, '\n' stands for enter
	if (isalnum(ch) && ch != 32 && ch != '\n')
	{
		return true;
	}
	return false;
}

bool isValidName(string s)
{
	// Kiem tra tung ki tu trong ten
	// Check one-by-one character in the name
	for (char ch : s)
	{
		if (!isValidChar(ch))
		{
			return false;
		}
	}
	return true;
}
