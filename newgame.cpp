#include "Header.h"

bool tryagain = false;
bool check = false;

bool isNameExist(string playerName, string filename) 
{
	PlayerInfo player;

	swapInfo(player, filename);
	

	bool top20 = false;
	bool resume_part = false;

	for(int i=0;i<20;i++)
	{
		if (strcmp(top_players[i].name, playerName.c_str()) == 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(resumeName[i], playerName.c_str()) == 0)
		{
			return true;
		}
	}

	return false; // Tên ng??i ch?i không t?n t?i trong t?p tin
}

// Turn ON Undo & Redo
void playGame1(int** a, int** p, int size, PlayerInfo player, GameInfo map, int check, int counter, double add, Stack undoStack, Stack redoStack)
{
tryagain:
	{
		if (tryagain == true)
		{
			a = createMap(size);
			player.score = 0;
		}
	}
	bool win = false;
	auto start = chrono::high_resolution_clock::now();

	int pos1, pos2, pos3, pos4, i, j;

	// Neu chua chon resume thi bat dau chon hai o bat ki de them so
	if (resume == false)
	{
		a = createMap(size);
		srand(time(NULL));
		pos1 = rand() % 4;
		pos2 = rand() % 4;
		while (1)
		{
			pos3 = rand() % 4;
			pos4 = rand() % 4;
			if (pos3 != pos1 && pos4 != pos2)
			{
				break;
			}
		}
		do
		{
			a[pos1][pos2] = 2 + rand() % 3;
			a[pos3][pos4] = 2 + rand() % 3;
		} while (a[pos1][pos2] == 3 || a[pos3][pos4] == 3);
	}
	Draw1(a, size);
	char selection;

	int count = 0;
	bool shouldContinue = false;
	bool undo_check = false;
	bool redo_check = false;
	bool first_move = false;

	// Luu trang thai mang ban dau
	p = new int* [size];
	for (int i = 0; i < size; i++)
	{
		p[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			p[i][j] = a[i][j];
		}
	}

	// Neu da chon resume roi va co mo UNDO hoac UNDO&REDO thi tien hanh lay mang ban dau
	if (resume == true && (on_1 !=false || on_2 != false))
	{
		Node* temp = undoStack.head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				p[i][j] = temp->map[i][j];
			}
		}
	}

	// Mang dung de doi chieu voi nuoc di hien tai
	int** tmp = new int* [size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = new int[size];
	}

	while (1)
	{
		printScore(player, player.score, size);

		if (shouldContinue == false && (on_1 != false || on_2 != false))
		{
			pushState(undoStack, redoStack, a, size, player.score);
		}
		else if (shouldContinue == true && (on_1 != false || on_2 != false))
		{
			if (selection == 'w' || selection == 'a' || selection == 'd' || selection == 's')
			{
				pushState(undoStack, redoStack, a, size, player.score);
			}
			shouldContinue = false;
		}

		copyMap(a, tmp, size);

		selection = _getch();

		if (selection == 'w')
		{
			if (undo_check == true)
			{
				if (!redoStack.isEmpty())
				{
					redoStack.clear(size);
					undo_check = false;
				}
			}
			player.score += moveUp(a, size);
		}
		else if (selection == 's')
		{
			if (undo_check == true)
			{
				if (!redoStack.isEmpty())
				{
					redoStack.clear(size);
					undo_check = false;
				}
			}
			player.score += moveDown(a, size);

		}
		else if (selection == 'a')
		{
			if (undo_check == true)
			{
				if (!redoStack.isEmpty())
				{
					redoStack.clear(size);
					undo_check = false;
				}
			}
			player.score += moveLeft(a, size);
		}
		else if (selection == 'd')
		{
			if (undo_check == true)
			{
				if (!redoStack.isEmpty())
				{
					redoStack.clear(size);
					undo_check = false;
				}
			}
			player.score += moveRight(a, size);
		}
		else if (selection == 'x')
		{
			system("cls");
			drawFrame(18,46);
			color(7);
			gotoyx(3, 44);
			if (eng == true)
			{
				cout << "Do you really want to exit [Y/N]? " << endl;
			}
			else
			{
				cout << "Ban co that su muon thoat [Y/N]?" << endl;
			}
			char select;
			do
			{
				select = _getch();
				if (select == 'Y' || select == 'y')
				{
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double> duration = end - start;
					player.time = duration.count() + add;

					// Neu nguoi choi chon Yes thi tien hanh luu thong tin nguoi choi
					writePlayerInfo(player, "player_scores.bin");
					
					if (on_1 == false && on_2 == false)
					{
						pushState(undoStack, redoStack, a, size, player.score);
					}
					gotoyx(4, 42);
					if (eng == true)
					{
						cout << "Do you want to save your game [Y/N]? " << endl;
					}
					else
					{
						cout << "Ban co muon luu game lai khong [Y/N]?" << endl;
					}
					char chon;
					do
					{
						chon = _getch();
						if (chon == 'Y' || chon == 'y')
						{
							gotoyx(6, 10);
							if (sameResumeName(undoStack, redoStack, player, size, player.name) == 0)
							{
								saveGameState(undoStack, redoStack, player, size, "player" + to_string(existResume12() + 1) + ".bin", on_1, on_2);
							}
							else
							{
								saveGameState(undoStack, redoStack, player, size, "player" + to_string(sameResumeName(undoStack, redoStack, player, size, player.name)) + ".bin", on_1, on_2);

							}
						}
						else if (chon == 'N' || chon == 'n')
						{
							drawFrame(18, 46);
							color(7);
							gotoyx(5, 41);
							if (eng == true)
							{
								cout << "You have chosen NOT save. See you again!" << endl;
							}
							else
							{
								cout << "Ban da chon KHONG luu. Hen gap lai ban!" << endl;
							}
							goto deleteThings;
						}
					} while (chon != 'Y' && chon != 'y' && chon != 'n' && chon != 'N');
					drawFrame(18,46);
					color(7);
					gotoyx(5, 44);
					if (eng == true)
					{
						cout << "Saved successfully! See you again!" << endl;
					}
					else
					{
						cout << "Luu thanh cong! Hen gap lai ban sau!" << endl;
					}
					deleteThings:
					{
						gotoyx(7, 45);
						system("pause");
						system("cls");

						cleanupMap(a, size);
						cleanupMap(p, size);
						cleanupMap(tmp, size);
						undoStack.clear(size);
						redoStack.clear(size);

						for (int i = 0; i < 5; ++i)
						{
							delete[] resumeName[i];
						}
						delete[] resumeName;

						exit(0);
					}
				}
				else if (select == 'N' || select == 'n')
				{
					system("cls");
					goto exit_error;

				}
			} while (select != 'Y' && select != 'y' && select != 'N' && select != 'n');
			break;
		}
		else if (selection == 'u')
		{
			if (on_1 != false || on_2 != false)
			{
				if (sameMap(a, p, size))
				{
					color(12);
					gotoyx(size * 2 + 4, 0);
					if (eng == true)
					{
						cout << "This is your original state." << endl;
					}
					else
					{
						cout << "Day la nuoc di ban dau cua ban." << endl;
					}
					color(7);
					system("pause");
					system("cls");
					player.score = 0;
					//undo_check = false;
					Draw1(a, size);
					continue;
				}
				else
				{
				undo:
					{
						undo(undoStack, redoStack, a, size, player.score);
						redo_check = false;
						Draw1(a, size);
						shouldContinue = true;
						undo_check = true;
						continue;
					}
				}
			}
			else if (on_1 == false && on_2 == false)
			{
				color(12);
				gotoyx(size * 2 + 4, 0);
				if (eng == true)
				{
					cout << "Invalid entry! " << endl;
				}
				else
				{
					cout << "Phim khong hop le!" << endl;
				}
				shouldContinue = true;
				color(7);
				system("pause");
				system("cls");
				goto exit_error;
			}
		}
		else if (selection == 'r')
		{
			if (on_2 == true)
			{
				if (undo_check == false && resume == false)
				{
					color(12);
					gotoyx(size * 2 + 4, 0);
					if (eng == true)
					{
						cout << "You have not chosen Undo action." << endl;
					}
					else
					{
						cout << "Ban chua bam chon nut Hoan tac." << endl;
					}
					color(7);
					system("pause");
					system("cls");
					Draw1(a, size);
					shouldContinue = true;
					continue;
				}
				else if (redoStack.isEmpty())
				{
					color(12);
					gotoyx(size * 2 + 4, 0);

					if (eng == true)
					{
						cout << "This is your last action before making Undo/Redo action." << endl;
					}
					else
					{
						cout << "Day la buoc hien tai cua ban truoc khi chon Hoan tac/Quay lai." << endl;
					}
					shouldContinue = true;
					color(7);
					system("pause");
					system("cls");
					Draw1(a, size);
					continue;
				}
				else
				{
					redo(undoStack, redoStack, a, size, player.score);
					Draw1(a, size);
					redo_check = true;
					shouldContinue = true;
					if (sameMap(a, p, size))
					{
						undo_check = false;
						redo_check = true;
						redoStack.clear(size);
					}
					continue;
				}
			}
			else
			{
				color(12);
				gotoyx(size * 2 + 4, 0);

				if (eng == true)
				{
					cout << "Invalid entry! " << endl;
				}
				else
				{
					cout << "Phim khong hop le!" << endl;
				}
				shouldContinue = true;
				color(7);
				system("pause");
				system("cls");
				goto exit_error;
			}
		}
		else
		{
			color(12);
			gotoyx(size * 2 + 4, 0);

			if (eng == true)
			{
				cout << "Invalid entry! " << endl;
			}
			else
			{
				cout << "Phim khong hop le!" << endl;
			}
			shouldContinue = true;
			color(7);
			system("pause");
			system("cls");
			goto exit_error;
		}
		if (check1(a, tmp, size) != 1)
		{
			addBlock(a, size);
		}
	exit_error:
		{
			Draw1(a, size);
		}
		if (gameOver(a, size) == 1)
		{
			Draw1(a, size);
			gotoyx(size * 2 + 4, 0);

			system("pause");
			writePlayerInfo(player, "player_scores.bin");
			system("cls");
			char choose;
			do
			{
				drawFrame(18,46);
				if (eng == true)
				{
					gotoyx(3, 55);
					color(11);
					cout << "GAME OVER!!";
					gotoyx(4, 55);
					color(11);
					cout << "GAME OVER!!";
					gotoyx(5, 55);
					color(11);
					cout << "GAME OVER!!";
				}
				else
				{
					gotoyx(3, 55);
					color(11);
					cout << "THUA CUOC!!";
					gotoyx(4, 55);
					color(11);
					cout << "THUA CUOC!!";
					gotoyx(5, 55);
					color(11);
					cout << "THUA CUOC!!";
				}
				
				color(7);

				Node2* players = readPlayersfromFile("player_scores.bin");
				if (eng == true)
				{
					gotoyx(7, 42);
					cout << "You are ranked ";
					color(14);
					cout << findPlayerRank(players, player.name);
					color(7);
					cout << " on the player list." << endl;
					gotoyx(8, 45);
					cout << "Do you want to try again? [Y/N]";
				}
				else
				{
					gotoyx(7, 39);
					cout << "Ban xep hang ";
					color(14);
					cout << findPlayerRank(players, player.name);
					color(7);
					cout << " trong danh sach nguoi choi." << endl;
					gotoyx(8, 47);
					cout << "Ban co muon choi lai? [Y/N]";

				}
				choose = _getch();
				if (choose == 'Y' || choose == 'y')
				{
					if (on_1 != false || on_2 != false)
					{
						//tryagain = true;
						system("cls");
						goto undo;
					}
					else if (on_1 == false && on_2 == false)
					{
						tryagain = true;
						system("cls");
						player.time = 0;
						goto tryagain;
					}

				}
				else if (choose == 'N' || choose == 'n')
				{
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double> duration = end - start;
					player.time = duration.count() + add;

					if (eng == true)
					{
						gotoyx(10, 42);
						cout << "Thanks for your time! See you again! " << endl;
					}
					else
					{
						gotoyx(10, 42);
						cout << "Cam on ban vi da choi! Hen gap lai! " << endl;
					}
					gotoyx(12, 45);
					system("pause");
					int rank = findPlayerRank(players, player.name);
					
					// Nguoi choi thua cuoc chi tien hanh luu thong tin neu nam trong top 1 -> top 20
					if (rank >= 1 && rank <= 20)
					{
						writePlayerInfo(player, "player_scores.bin");
					}
					system("cls");

					cleanupMap(a, size);
					cleanupMap(p, size);
					cleanupMap(tmp, size);
					undoStack.clear(size);
					redoStack.clear(size);

					for (int i = 0; i < 5; ++i)
					{
						delete[] resumeName[i];
					}
					delete[] resumeName;

					exit(0);
				}
			} while (choose != 'Y' && choose != 'y' && choose != 'N' || choose != 'n');
		}
		if (checkWin(a, size) && win == false)
		{
			Draw1(a, size);
			gotoyx(size * 2 + 4, 0);
			system("pause");
			system("cls");
			char choose;
			do
			{
				drawFrame(18,46);
				color(11);
				if (eng == true)
				{
					gotoyx(3, 56);
					cout << "YOU WIN!!";
					gotoyx(4, 56);
					cout << "YOU WIN!!";
					gotoyx(5, 56);
					cout << "YOU WIN!!";
				}
				else
				{
					gotoyx(3, 54);
					cout << "CHIEN THANG!!";
					gotoyx(4, 54);
					cout << "CHIEN THANG!!";
					gotoyx(5, 54);
					cout << "CHIEN THANG!!";
				}
				color(7);
				
				Node2* players = readPlayersfromFile("player_scores.bin");
				int rank = findPlayerRank(players, player.name);
				if (rank >= 1 && rank <= 20)
				{
					if (eng == true)
					{
						gotoyx(7, 45);
						cout << "You are ranked ";
						color(14);
						cout << findPlayerRank(players, player.name);
						color(7);
						cout << " on the player list." << endl;
					}
					else
					{
						gotoyx(7, 40);
						cout << "Ban xep hang ";
						color(14);
						cout << findPlayerRank(players, player.name);
						color(7);
						cout << " trong danh sach nguoi choi." << endl;
					}
				}
				gotoyx(8, 46);
				if (eng == true)
				{
					cout << "Do you want to continue? [Y/N]";
				}
				else
				{
					cout << "Ban co muon choi tiep? [Y/N]";
				}
				choose = _getch();
				if (choose == 'Y' || choose == 'y')
				{
					system("cls");
					win = true;
					goto exit_error;
				}
				else if (choose == 'N' || choose == 'n')
				{
					auto end = chrono::high_resolution_clock::now();
					chrono::duration<double> duration = end - start;
					player.time = duration.count();
					
					// Nguoi choi thang cuoc khi chon ket thuc se luu lai thong tin
					writePlayerInfo(player, "player_scores.bin");
					
					
					color(7);
					gotoyx(10, 42);
					if (eng == true)
					{
						cout << "Thanks for your time! See you again! " << endl;
					}
					else
					{
						cout << "Cam on ban vi da choi! Hen gap lai! " << endl;
					}

					cleanupMap(a, size);
					cleanupMap(p, size);
					cleanupMap(tmp, size);
					undoStack.clear(size);
					redoStack.clear(size);

					for (int i = 0; i < 5; ++i)
					{
						delete[] resumeName[i];
					}
					delete[] resumeName;

					gotoyx(12, 42);
					system("pause");
					system("cls");
					exit(0);
				}
			} while (choose != 'Y' && choose != 'y' && choose != 'N' || choose != 'n');
		}
	}
}



