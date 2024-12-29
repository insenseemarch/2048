#include "Header.h"

bool resume = false;
bool on_1 = false; // Stands for UNDO option (false = off)
bool on_2 = false; // Stands for UNDO & REDO option (false = off)
bool eng = true;
bool viet = false;
char** resumeName = nullptr;


void start()
{
	HWND hwnd = GetConsoleWindow();
	LONG cur_style = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, cur_style | WS_EX_TRANSPARENT | WS_EX_LAYERED);

	LockConsoleSize(1000, 800);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hConsole, &dwMode);
	dwMode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hConsole, dwMode);

	PlayerInfo player;
	Stack undoStack;
	Stack redoStack;
	GameInfo map;
	helloScreen();
	gotoyx(7, 10);
	int size = 4;
	resumeName = new char* [5];
	for (int i = 0; i < 5; ++i)
	{
		resumeName[i] = new char[21];
	}
	system("cls");
	int counter = 0;
	int check = -1;
	menu1(player, undoStack, redoStack, check, counter, size);
	color(7);
	char temp;
	if (counter == 1)
	{
		label:
		{
				system("cls");
				drawFrame(18, 46);
				gotoyx(3, 42);
				color(8);
				cout << "Please press Enter twice if necessary";
				color(11);
				gotoyx(5, 42);
				cout << "What is your ID? (up to 20 characters)";
				color(7);
				gotoyx(6, 42);
				cin.getline(player.name, 21);
				if (cin.fail())
				{
					cin.clear();
				}
				cin.ignore(100000, '\n');
				gotoyx(6, 42);
				gotoyx(8, 55);
				cout << "Your ID is ";
				gotoyx(9, 61 - (strlen(player.name) / 2));
				color(11);
				cout << player.name;
				gotoyx(10, 47);
				color(7);
				cout << "(only accepts 20 characters)";
				gotoyx(12, 47);
				cout << "Are you sure? (y/n)";
				do
				{
					temp = _getch();
					if (temp == 'Y' || temp == 'y')
					{
						system("cls");
						break;
					}
					else if (temp == 'n' || temp == 'N')
					{
						system("cls");
						goto label;
					}
				} while (temp != 'Y' && temp != 'y' && temp != 'n' && temp != 'N');
			
		} 


		// QUY DINH TEN HOP LE: Chi chua SO va CHU CAI, phan biet giua chu hoa va thuong (vi du: abc khac ABc,...)
		// VALID NAME REGULATIONS: Contains only numbers and letters, sensitive to upper and lower case letters (for example, abc is different from ABc,...)
		do
		{
			if (!isValidName(player.name))
			{
				drawFrame(18, 46);
				gotoyx(8, 41);
				color(12);
				cout << "Invalid ID (including strange character)" << endl;
				gotoyx(9, 52);
				color(12);
				cout << "Please try again!";
				gotoyx(10, 45);
				color(7);
				system("pause");
				system("cls");
				goto label;
			}
		} while (!isValidName(player.name));
		do
		{
			if (isNameExist(player.name, "player_scores.bin"))
			{
				drawFrame(18, 46);
				gotoyx(8, 40);
				color(12);
				cout << "Invalid ID (this ID has been already used)" << endl;
				gotoyx(9, 52);
				color(12);
				cout << "Please try again!";
				gotoyx(10, 45);
				color(7);
				system("pause");
				system("cls");
				goto label;
			}
		} while (isNameExist(player.name, "player_scores.bin"));
		system("cls");

		int** a = createMap(size);
		int** p = createMap(size);
		playGame1(a, p, size, player, map, check, counter, 0, undoStack, redoStack);
	}
}

void menu1(PlayerInfo& player, Stack& undoStack, Stack& redoStack, int& check, int& counter, int& size)
{
	// Dem so luong nguoi choi da dung resume
	// Count the number of players who have chosen resume
	int count_temp = existResume(undoStack, redoStack, player, size);
	

	for (int i = 0; i < count_temp; i++)
	{
		// Tai thong tin nguoi choi de lay ten nguoi choi
		// Read players' informations from file to store players' name
		loadGameState(undoStack, redoStack, player, size, "player" + to_string(i + 1) + ".bin", on_1, on_2);
		strcpy_s(resumeName[i], 21, player.name);
	}
	for (int i = count_temp; i < 5; i++)
	{
		strcpy_s(resumeName[i], 21, " ");
	}

	on_1 = false; 
	on_2 = false;
	size = 4;

	// Xoa undoStack va redoStack sau khi dung cho ham loadGameState()
	// Clear undoStack and redoStack after using them for loadGameState()
	undoStack.clear(size); 
	redoStack.clear(size);

	player.score = 0;
	int Set[] = { 7,7,7 , 7, 7, 7 }; // Default colors (white)
	counter = 1;
	check = false;
	char key;
	drawFrame(18,46);
	for (int i = 0;;)
	{
		color(3);
		
		// Using ENGLISH
		if (eng == true)
		{
			gotoyx(3, 58);
			cout << "MENU" << endl;
			color(7);
			gotoyx(4, 48);
			cout << "+------------------------+";
			gotoyx(5, 48);
			color(Set[0]);
			cout << "|  1. New game           |" << endl;
			color(7);
			gotoyx(6, 48);
			cout << "+------------------------+";
			gotoyx(7, 48);
			color(Set[1]);
			cout << "|  2. Game settings      |" << endl;
			color(7);

			gotoyx(8, 48);
			cout << "+------------------------+";
			gotoyx(9, 48);
			color(Set[2]);
			cout << "|  3. Player's ranking   |" << endl;
			color(7);

			gotoyx(10, 48);
			cout << "+------------------------+";
			gotoyx(11, 48);
			color(Set[3]);
			cout << "|  4. How to play        |" << endl;
			color(7);

			gotoyx(12, 48);
			cout << "+------------------------+";
			gotoyx(13, 48);
			color(Set[4]);
			cout << "|  5. Exit               |" << endl;
			color(7);

			gotoyx(14, 48);
			cout << "+------------------------+";
			gotoyx(15, 48);
			if (count_temp == 0)
			{
				Set[5] = 8;
			}
			color(Set[5]);
			cout << "|  6. Resume             |" << endl;
			color(7);

			gotoyx(16, 48);
			cout << "+------------------------+";


			key = _getch();
			if (count_temp > 0)
			{
				if (key == 72 && (counter >= 2 && counter <= 6)) // 72 = up arrow key
				{
					counter--;
				}
				if (key == 80 && (counter >= 1 && counter <= 5)) // 80 = down arrow key
				{
					counter++;
				}
			}
			else if (count_temp == 0)
			{
				if (key == 72 && (counter >= 2 && counter <= 5)) // 72 = up arrow key
				{
					counter--;
				}
				if (key == 80 && (counter >= 1 && counter <= 4)) // 80 = down arrow key
				{
					counter++;
				}
			}

			if (key == '\r') // 72 = up arrow key
			{
				if (counter == 1)
				{
					system("cls");
					break;
				}
				if (counter == 2)
				{
					system("cls");
					gameSetting(size, check);
				}
				if (counter == 3)
				{
					while (check == false)
					{
						check = false;
						system("cls");

						
						int max_y = 29;
						int max_x = 59;

						for (int i = 0; i < max_y; i++)
						{
							gotoyx(i, 28);

							for (int j = 0; j < max_x; j++)
							{

								string m = borderHelloScreen(i, j, max_y, max_x);
								color(getThingColor(m));
								cout << m;
							}
						}
						//drawFrame(29, 49);
						gotoyx(1, 51);
						color(3);
						cout << "PLAYER'S RANKING" << endl << endl;
						Set[2] = 7;
						color(Set[2]);
						int numPlayers = 0;
						printRank(player, "player_scores.bin");
						//system("pause");
						gotoyx(26, 39);
						cout << "Back to the menu (Y: Yes / N: No)? " << endl;
						char choose = _getch();

						if (choose == 'Y' || choose == 'y')
						{
							system("cls");
							drawFrame(18, 46);
							break;
						}
						else if (choose != 'Y' && choose != 'y' && choose != 'N' && choose != 'n')
						{
							gotoyx(27, 37);
							color(12);
							cout << "Please choose again, this in not in our choice." << endl;
							color(7);
							gotoyx(28, 37);
							system("pause");
						}
					}

				}
				if (counter == 4)
				{
					while (check == false)
					{

						check = false;
						system("cls");
						int max_y = 22;
						int max_x = 65;

						for (int i = 0; i < max_y; i++)
						{
							gotoyx(i + 1, 28);

							for (int j = 0; j < max_x; j++)
							{

								string m = borderHelloScreen(i, j, max_y, max_x);
								color(getThingColor(m));
								cout << m;
							}
						}
						gotoyx(3, 51);
						color(3);
						cout << "HOW TO PLAY" << endl << endl;
						Set[2] = 7;
						color(Set[2]);
						gotoyx(5, 31);
						cout << "1. Use your keys to move the tiles.";
						gotoyx(6, 35);
						color(11);
						cout << "       + W: Moving up." << endl;
						gotoyx(7, 35);
						cout << "       + D: Moving right." << endl;
						gotoyx(8, 35);
						cout << "       + A: Moving left." << endl;
						gotoyx(9, 35);
						cout << "       + S: Moving down." << endl;
						gotoyx(10, 35);
						cout << "       + U: Undoing." << endl;
						gotoyx(11, 35);
						cout << "       + R: Redoing." << endl;
						gotoyx(12, 35);
						cout << "       + X: Exit." << endl;
						gotoyx(13, 31);
						color(7);
						cout << "2. Tiles with the same number merge into one when they touch." << endl;
						gotoyx(14, 31);
						cout << "3. Add them up to reach 2048." << endl;
						gotoyx(15, 31);

						system("pause");
						gotoyx(17, 31);
						cout << "Back to the menu (Y: Yes / N: No)? " << endl;
						char choose = _getch();

						if (choose == 'Y' || choose == 'y')
						{
							system("cls");
							drawFrame(18, 46);
							break;
						}
						else if (choose != 'Y' && choose != 'y' && choose != 'N' && choose != 'n')
						{
							gotoyx(19, 31);
							color(12);
							cout << "Please choose again, this in not in our choice." << endl;
							gotoyx(20, 31);
							color(7);
							system("pause");
						}
					}
				}
				if (counter == 5)
				{
					color(7);
					system("cls");
					exit(0);
				}
				if (counter == 6)
				{
					color(7);
					system("cls");
					gameResume(undoStack, redoStack, player, size, existResume(undoStack, redoStack, player, size));
				}
			}
		}

		if (check == true)
		{
			menu1(player, undoStack, redoStack, check, counter, size);
		}
		else
		{
			Set[0] = 7; // Default white color
			Set[1] = 7;
			Set[2] = 7;
			Set[3] = 7;
			Set[4] = 7;
			if (count_temp > 0)
			{
				Set[5] = 7;
			}

			if (counter == 1)
			{
				Set[0] = 14; // 12 is color red
			}
			if (counter == 2)
			{
				Set[1] = 14; // 12 is color red
			}
			if (counter == 3)
			{
				Set[2] = 14; // 12 is color red
			}
			if (counter == 4)
			{
				Set[3] = 14;
			}
			if (counter == 5)
			{
				Set[4] = 14;
			}
			if (count_temp > 0)
			{
				if (counter == 6)
				{
					Set[5] = 14;
				}
			}
		}
	}
}

// Chinh che do UNDO & REDO
// Turn on/off UNDO & REDO options
int unreOption(bool& on_1, bool& on_2, int size)
{
	int Set1[] = { 7,7 }; // Default colors
	int counter = 1;
	int option = 0;
	char key;
	system("cls");
	drawFrame(18,46);

	for (int i = 0;;)
	{
		color(3);
		if (eng == true)
		{
			gotoyx(3, 54);
			cout << "GAME SETTINGS" << endl;
		}
		else
		{
			gotoyx(3, 57);
			cout << "CAI DAT" << endl;
		}
		gotoyx(5, 51);
		color(14);
		if (eng == true)
		{
			cout << "2. Undo/Redo button" << endl;
		}
		else
		{
			cout << "2. Hoan tac/Quay ve" << endl;
		}
		color(7);
		gotoyx(7, 44);
		cout << "+-----------------------------+";
		color(Set1[0]);
		gotoyx(8, 44);
		if (on_1 == false)
		{
			if (eng == true)
			{
				cout << "| (i) Turn on UNDO            |";
			}
			else
			{
				cout << "| (i) Mo HOAN TAC             |";
			}
		}
		else
		{
			if (eng == true)
			{
				cout << "| (i) Turn off UNDO           |";
			}
			else
			{
				cout << "| (i) Tat HOAN TAC            |";
			}
		}
		color(7);
		gotoyx(9, 44);
		cout << "+-----------------------------+";
		gotoyx(10, 44);
		color(Set1[1]);
		if (on_2 == false)
		{
			if (eng == true)
			{
				cout << "| (i) Turn on UNDO & REDO     |";
			}
			else
			{
				cout << "| (i) Mo HOAN TAC & QUAY VE   |";
			}
		}
		else
		{
			if (eng == true)
			{
				cout << "| (i) Turn off UNDO & REDO    |";
			}
			else
			{
				cout << "| (i) Tat HOAN TAC & QUAY VE  |";
			}
		}
		color(7);
		gotoyx(11, 44);
		cout << "+-----------------------------+";
		gotoyx(13, 50);
		color(7);
		if (eng == true)
		{
			cout << "Our press [x] to back!" << endl;
		}
		else
		{
			cout << "Hoac nhan [x] de quay ve!" << endl;
		}
		key = _getch();

		if (key == 72 && counter == 2) // 72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && counter == 1) // 80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')
		{
			switch (counter)
			{
			case 1:
				if (on_1 == false)
				{
					on_1 = true;
					if (on_2 == true)
					{
						on_2 = false;
					}
				}
				else
				{
					on_1 = false;
				}
				return 1;
				break;
			case 2:
				if (on_2 == false)
				{
					on_2 = true;
					if (on_1 == true)
					{
						on_1 = false;
					}
				}
				else
				{
					on_2 = false;
				}
				return 2;
				break;
			}
			return option;
		}
		else if (key == 'x')
		{
			//gameSetting(size, counter);
			break;
		}
		if (check == true)
		{
			system("cls");
			break;
		}
		else
		{
			Set1[0] = 7; // Default white color
			Set1[1] = 7;

			if (counter == 1)
			{
				Set1[0] = 14; // 12 is color red
			}
			if (counter == 2)
			{
				Set1[1] = 14; // 12 is color red
			}
		}
	}
	return option;
}

// Chinh ngon ngu hien thi
// Change language into ENGLISH or VIETNAMESE
int languageOption(bool& eng, bool& viet, int size)
{
	int Set1[] = { 7,7 }; // Default colors
	int counter = 1;
	int option = 0;
	char key;
	system("cls");
	drawFrame(18,46);

	for (int i = 0;;)
	{
		color(3);
		if (eng == true)
		{
			gotoyx(3, 54);
			cout << "GAME SETTINGS" << endl;
		}
		else
		{
			gotoyx(3, 57);
			cout << "CAI DAT";
		}
		gotoyx(5, 55);
		color(14);
		if (eng == true)
		{
			cout << "3. Language" << endl;
		}
		else
		{
			cout << "3. Ngon ngu" << endl;
		}
		color(7);
		gotoyx(7, 44);
		cout << "+-----------------------------+";
		gotoyx(8, 44);
		if (eng == false)
		{
			Set1[0] = 14;
			Set1[1] = 8;
		}
		else
		{
			Set1[0] = 8;
			Set1[1] = 14;
		} 
		color(Set1[0]);
		if (eng == true)
		{
			cout << "| (i) English                 |";
		}
		else
		{
			cout << "| (i) Tieng Anh               |";
		}
		color(7);
		gotoyx(9, 44);
		cout << "+-----------------------------+";
		gotoyx(10, 44);
		color(Set1[1]);
		if (eng == true)
		{
			cout << "| (ii) Vietnamese             |";
		}
		else
		{
			cout << "| (ii) Tieng Viet             |";

		}
		color(7);
		gotoyx(11, 44);
		cout << "+-----------------------------+";
		gotoyx(13, 50);
		color(7);
		if (eng == true)
		{
			cout << "Our press [x] to back!" << endl;
		}
		else
		{
			cout << "Hoac nhan [x] de quay ve!" << endl;
		}
		key = _getch();

		if (counter == 2 && (eng == false)) // 72 = up arrow key
		{
			counter--;
		}
		if (counter == 1 && (eng == true)) // 80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')
		{
			switch (counter)
			{
			case 1:
				eng = true;
				//viet = false;
				return 1;
				break;
			case 2:
				eng = false;
				//viet = true;
				return 2;
				break;
			}
			return option;
		}
		else if (key == 'x')
		{
			//gameSetting(size, counter);
			break;
		}
	}
	return option;
}

void gameSetting(int& size, int& option)
{
	int max_y = 18;
	int max_x = 46;

	for (int i = 0; i < max_y; i++) {
		gotoyx(i + 1, 38);

		for (int j = 0; j < max_x; j++) {

			string m = borderHelloScreen(i, j, max_y, max_x);
			color(getThingColor(m));
			cout << m;
		}
	}
	int Set[] = { 7, 7, 7, 7}; // Default colors
	int counter = 1;
	char key;
	option = 0;
	for (int i = 0;;)
	{
		gotoyx(3, 54);
		color(3);
		if (eng == true)
		{
			gotoyx(3, 54);
			cout << "GAME SETTINGS" << endl;
		}
		else
		{
			gotoyx(3, 57);
			cout << "CAI DAT" << endl;
		}

		color(7);
		gotoyx(4, 48);
		cout << "+------------------------+";
		gotoyx(5, 48);
		color(Set[0]);
		if (eng == true)
		{
			cout << "| 1. Size of game        |" << endl;
		}
		else
		{
			cout << "| 1. Kich thuoc choi     |" << endl;
		}
		color(7);
		gotoyx(6, 48);
		cout << "+------------------------+";
		gotoyx(7, 48);
		color(Set[1]);
		if (eng == true)
		{
			cout << "| 2. Undo/Redo button    |" << endl;
		}
		else
		{
			cout << "| 2. Che do Hoan/Quay    |" << endl;

		}
		color(7);
		gotoyx(8, 48);
		cout << "+------------------------+";
		gotoyx(9, 48);
		color(Set[2]);
		if (eng == true)
		{
			cout << "| 3. Language            |" << endl;
		}
		else
		{
			cout << "| 3. Ngon ngu            |" << endl;
		}
		gotoyx(10, 48);
		color(7);
		cout << "+------------------------+";
		gotoyx(11, 48);
		color(Set[3]);
		if (eng == true)
		{
			cout << "| 4. Back to menu        |" << endl;
		}
		else
		{
			cout << "| 4. Quay ve DS chon     |" << endl;
		}
		gotoyx(12, 48);
		color(7);
		cout << "+------------------------+";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <=4)) // 72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) // 80 = down arrow key
		{
			counter++;
		}

		if (key == '\r') // 72 = up arrow key
		{
			if (counter == 1)
			{
			label1:
				size = sizeOfGame();
				if (size == 4)
				{
					system("cls");
					drawFrame(18,46);
					break;
				}
				system("cls");
				drawFrame(18,46);
				color(3);
				if (eng == true)
				{
					gotoyx(3, 54);
					cout << "GAME SETTINGS" << endl;
				}
				else
				{
					gotoyx(3, 57);
					cout << "CAI DAT" << endl;
				}
				gotoyx(5, 51);
				color(Set[0]);
				if (eng == true)
				{
					cout << "1. Size of game" << endl;
				}
				else
				{
					cout << "1. Kich thuoc choi" << endl;
				}
				gotoyx(7, 41);
				color(7);
				if (eng == true)
				{
					cout << "You have changed your GAME SIZE into " << size << "x" << size << endl;
				}
				else
				{
					cout << "Ban da thay doi KICH THUOC thanh " << size << "x" << size << endl;
				}
				if (eng == true)
				{
					gotoyx(8, 51);
					cout << "Are you sure (y/n)?";
				}
				else
				{
					gotoyx(8, 41);
					cout << "Ban da chac chan chua (y/n)?";
				}
				char makesure;
				do
				{
					makesure = _getch();
					if (makesure == 'y' || makesure == 'Y')
					{
						system("cls");
						gameSetting(size, option);
						break;
					}
					else if (makesure == 'n' || makesure == 'N')
					{
						system("cls");
						goto label1;
					}
				} while (makesure != 'y' && makesure != 'Y' && makesure != 'n' && makesure != 'N');

				break;
			}
			if (counter == 2)
			{
				drawFrame(18,46);
			label:
				option = unreOption(on_1, on_2, size);
				if (option == 0)
				{
					system("cls");
					drawFrame(18,46);
					break;
					//gameSetting(size, option);
				}
				system("cls");
				drawFrame(18,46);
				color(3);
				if (eng == true)
				{
					gotoyx(3, 54);
					cout << "GAME SETTINGS" << endl;
				}
				else
				{
					gotoyx(3, 57);
					cout << "CAI DAT" << endl;
				}
				gotoyx(5, 51);
				color(14);
				if (eng == true)
				{
					cout << "2. Undo/Redo option" << endl;
				}
				else
				{
					cout << "2. Che do Hoan/Quay" << endl;
				}

				if (option == 1)
				{
					gotoyx(7, 45);
					color(7);
					if (on_1 == true)
					{
						if (eng == true)
						{
							cout << "You have turned on UNDO option." << endl;
						}
						else
						{
							cout << "Ban da mo che do HOAN TAC." << endl;
						}
					}
					else
					{
						if (eng == true)
						{
							cout << "You have turned off UNDO option." << endl;
						}
						else
						{
							cout << "Ban da tat che do HOAN TAC." << endl;
						}
					}
					if (eng == true)
					{					
						gotoyx(8, 51);
						cout << "Are you sure (y/n)?";
					}
					else
					{
						gotoyx(8, 41);
						cout << "Ban da chac chan chua (y/n)?";
					}
					char makesure;
					do
					{
						makesure = _getch();
						if (makesure == 'y' || makesure == 'Y')
						{
							system("cls");
							gameSetting(size, option);

						}
						else if (makesure == 'n' || makesure == 'N')
						{
							if (on_1 == true)
							{
								on_1 = false;
							}
							else
							{
								on_1 = true;
							}
							system("cls");
							goto label;
						}
					} while (makesure != 'y' && makesure != 'Y' && makesure != 'n' && makesure != 'N');
					break;
				}
				else if (option == 2)
				{
					gotoyx(7, 42);
					color(7);
					if (on_2 == true)
					{
						if (eng == true)
						{
							cout << "You have turned on UNDO & REDO option." << endl;
						}
						else
						{
							cout << "Ban da mo che do HOAN TAC & QUAY LAI." << endl;
						}
					}
					else
					{
						gotoyx(7, 41);
						if (eng == true)
						{
							cout << "You have turned off UNDO & REDO option." << endl;
						}
						else
						{
							cout << "Ban da tat che do HOAC TAC & QUAY LAI." << endl;
						}
					}
					
					if (eng == true)
					{
						gotoyx(8, 51);
						cout << "Are you sure (y/n)?";
					}
					else
					{
						gotoyx(8, 41);
						cout << "Ban da chac chan chua (y/n)?";
					}
					char makesure;
					do
					{
						makesure = _getch();
						if (makesure == 'y' || makesure == 'Y')
						{
							system("cls");
							gameSetting(size, option);
						}
						else if (makesure == 'n' || makesure == 'N')
						{
							if (on_2 == true)
							{
								on_2 = false;
							}
							else
							{
								on_2 = true;
							}
							system("cls");
							goto label;
						}
					} while (makesure != 'y' && makesure != 'Y' && makesure != 'n' && makesure != 'N');
					break;
				}
			}
			else if (counter == 3)
			{
				drawFrame(18,46);
			language:
				option = languageOption(eng, viet, size);
				if (option == 0)
				{
					system("cls");
					drawFrame(18,46);
					break;
					//gameSetting(size, option);
				}
				system("cls");
				drawFrame(18,46);
				gotoyx(3, 54);
				color(3);
				cout << "GAME SETTINGS" << endl;
				gotoyx(5, 55);
				color(14);
				cout << "3. Language" << endl;

				if (option == 1)
				{
					gotoyx(7, 46);
					color(7);
					cout << "You have changed into ENGLISH";
					gotoyx(8, 51);
					cout << "Are you sure (y/n)?";
					char makesure;
					do
					{
						makesure = _getch();
						if (makesure == 'y' || makesure == 'Y')
						{
							system("cls");
							gameSetting(size, option);

						}
						else if (makesure == 'n' || makesure == 'N')
						{
							eng = false;
							viet = true;
							system("cls");
							goto language;
						}
					} while (makesure != 'y' && makesure != 'Y' && makesure != 'n' && makesure != 'N');
					break;
				}
				else if (option == 2)
				{
					gotoyx(7, 45);
					color(7);
					cout << "Ban da thay doi sang TIENG VIET.";

					gotoyx(8, 45);
					cout << "Ban da chac chan chua (y/n)?";
					char makesure;
					do
					{
						makesure = _getch();
						if (makesure == 'y' || makesure == 'Y')
						{
							system("cls");
							gameSetting(size, option);
						}
						else if (makesure == 'n' || makesure == 'N')
						{
							viet = false;
							eng = true;
							system("cls");
							goto language;
						}
					} while (makesure != 'y' && makesure != 'Y' && makesure != 'n' && makesure != 'N');
					break;
				}
			}
			else if (counter == 4)
			{
				system("cls");
				drawFrame(18,46);
				break;
			}
		}
		if (check == true)
		{
			system("cls");
			break;
		}
		else
		{
			Set[0] = 7; // Default white color
			Set[1] = 7;
			Set[2] = 7;
			Set[3] = 7;
			if (counter == 1)
			{
				Set[0] = 14; // 12 is color red
			}
			if (counter == 2)
			{
				Set[1] = 14; // 12 is color red
			}
			if (counter == 3)
			{
				Set[2] = 14; // 12 is color red
			}
			if (counter == 4)
			{
				Set[3] = 14; // 12 is color red
			}
		}
	}
}

// Chinh so luong o
// Change SIZE of game (from 4x4 to 10x10)
int sizeOfGame()
{
	int Set1[] = { 7, 7, 7, 7, 7, 7}; // Default colors
	int counter = 1;
	int size = 4;
	char key;
	system("cls");
	int max_y = 25;
	int max_x = 46;

	for (int i = 0; i < max_y; i++) {
		gotoyx(i + 1, 38);

		for (int j = 0; j < max_x; j++) {

			string m = borderHelloScreen(i, j, max_y, max_x);
			color(getThingColor(m));
			cout << m;
		}
	}

	for (int i = 0;;)
	{
		color(3);
		if (eng == true)
		{
			gotoyx(3, 54);
			cout << "GAME SETTINGS" << endl;
		}
		else
		{
			gotoyx(3, 57);
			cout << "CAI DAT" << endl;
		}

		gotoyx(5, 51);
		color(14);
		if (eng == true)
		{
			cout << "1. Size of game" << endl;
		}
		else
		{
			cout << "1. Kich thuoc choi" << endl;
		}

		color(7);
		gotoyx(7, 53);
		cout << "+--------------+";
		color(Set1[0]);
		gotoyx(8, 53);
		cout << "|      5x5     |";
		color(7);
		gotoyx(9, 53);
		cout << "+--------------+";

		gotoyx(10, 53);
		color(Set1[1]);
		cout << "|      6x6     |";
		color(7);
		gotoyx(11, 53);
		cout << "+--------------+";
		gotoyx(12, 53);
		color(Set1[2]);
		cout << "|      7x7     |";
		color(7);
		gotoyx(13, 53);
		cout << "+--------------+";
		gotoyx(14, 53);
		color(Set1[3]);
		cout << "|      8x8     |";
		color(7);
		gotoyx(15, 53);
		cout << "+--------------+";
		gotoyx(16, 53);
		color(Set1[4]);
		cout << "|      9x9     |";
		color(7);
		gotoyx(17, 53);
		cout << "+--------------+";
		gotoyx(18, 53);
		color(Set1[5]);
		cout << "|     10x10    |";
		color(7);
		gotoyx(19, 53);
		cout << "+--------------+";

		gotoyx(21, 50);
		color(7);
		if (eng == true)
		{
			cout << "Or press [x] to back!" << endl;
		}
		else
		{
			cout << "Hoac nhan [x] de quay ve!" << endl;
		}
		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 6)) // 72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 5)) // 80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')
		{
			switch (counter)
			{
			case 1: size = 5; break;
			case 2: size = 6; break;
			case 3: size = 7; break;
			case 4: size = 8; break;
			case 5: size = 9; break;
			case 6: size = 10; break;
			}
			return size;
		}
		else if (key == 'x')
		{
			break;
		}
		if (check == true)
		{
			system("cls");
			break;
		}
		else
		{
			Set1[0] = 7; // Default white color
			Set1[1] = 7;
			Set1[2] = 7;
			Set1[3] = 7;
			Set1[4] = 7;
			Set1[5] = 7;

			if (counter == 1)
			{
				Set1[0] = 14; // 12 is color red
			}
			if (counter == 2)
			{
				Set1[1] = 14; // 12 is color red
			}
			if (counter == 3)
			{
				Set1[2] = 14; // 12 is color red
			}
			if (counter == 4)
			{
				Set1[3] = 14; // 12 is color red
			}
			if (counter == 5)
			{
				Set1[4] = 14; // 12 is color red
			}
			if (counter == 6)
			{
				Set1[5] = 14; // 12 is color red
			}
		}
	}
	return size;
}

void gameResume(Stack& undoStack, Stack& redoStack, PlayerInfo& player, int& size, int numPlayers)
{
	

	for (int i = 0; i < 18; i++)
	{
		gotoyx(i + 1, 35);

		for (int j = 0; j < 50; j++)
		{

			string m = borderHelloScreen(i, j, 18, 50);
			color(getThingColor(m));
			cout << m;
		}
	}

	int Set[] = {7, 7, 7, 7, 7,7 }; // Default colors (white)
	int counter = 1;
	char key;

	int size_name = 0;
	int pos = 5;

	for (int i = 0;;)
	{
		pos = 5;
		gotoyx(3, 55);
		color(3);
		if (eng == true)
		{
			cout << "RESUME GAME" << endl;


			gotoyx(pos++, 37);
			color(7);
			cout << "+---------------------------------------------+";
			gotoyx(pos, 37);
			color(Set[0]);
			cout << "|  1. Player: " << resumeName[0];
			gotoyx(pos, 83);
			cout << "|";
			pos++;

			if (strcmp(resumeName[1], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[1]);
				cout << "|  2. Player: " << resumeName[1];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[2], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[2]);
				cout << "|  3. Player: " << resumeName[2];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[3], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[3]);
				cout << "|  4. Player: " << resumeName[3];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[4], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[4]);
				cout << "|  5. Player: " << resumeName[4];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}
			gotoyx(pos++, 37);
			color(7);
			cout << "+---------------------------------------------+";
			gotoyx(pos++, 37);
			color(Set[5]);
			cout << "|  " << existResume(undoStack, redoStack, player, size) + 1 << ". Back to the menu                        |" << endl;
			gotoyx(pos, 37);
			color(7);
			cout << "+---------------------------------------------+";
		}
		else
		{
			cout << "CHOI TIEP" << endl;

			gotoyx(pos++, 37);
			color(7);
			cout << "+---------------------------------------------+";
			gotoyx(pos, 37);
			color(Set[0]);
			cout << "|  1. Nguoi choi: " << resumeName[0];
			gotoyx(pos, 83);
			cout << "|";
			pos++;

			if (strcmp(resumeName[1], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[1]);
				cout << "|  2. Nguoi choi: " << resumeName[1];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[2], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[2]);
				cout << "|  3. Nguoi choi: " << resumeName[2];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[3], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[3]);
				cout << "|  4. Nguoi choi: " << resumeName[3];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}

			if (strcmp(resumeName[4], " ") != 0)
			{
				gotoyx(pos++, 37);
				color(7);
				cout << "+---------------------------------------------+";
				gotoyx(pos, 37);
				color(Set[4]);
				cout << "|  5. Nguoi choi: " << resumeName[4];
				gotoyx(pos, 83);
				cout << "|";
				pos++;
			}
			gotoyx(pos++, 37);
			color(7);
			cout << "+---------------------------------------------+";
			gotoyx(pos, 37);
			color(Set[5]);
			cout << "|  " << existResume(undoStack, redoStack, player, size) + 1 << ". Quay ve danh sach chon";
			gotoyx(pos++, 83);
			cout << "|";
			gotoyx(pos, 37);
			color(7);
			cout << "+---------------------------------------------+";
		}

		key = _getch();

		int number = existResume(undoStack, redoStack, player, size);

		if (key == 72 && (counter >= 2 && counter <= number+1)) // 72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= (number))) // 80 = down arrow key
		{
			counter++;
		}

		if (key == '\r') // 72 = up arrow key
		{
			if (counter != (number + 1))
			{
				resume = true;
			}
			if (counter == 1)
			{

				loadGameState(undoStack, redoStack, player, size, "player" + to_string(1) + ".bin", on_1, on_2);
			playgame:
				{
					system("cls");
					GameInfo map;
					Node* node = undoStack.pop();
					int** a = node->map;
					int** p = node->map;
					playGame1(a, p, size, player, map, check, counter, player.time, undoStack, redoStack);
					//break;
				}
			}
			else if (counter == 2 && (counter != number +1))
			{
				loadGameState(undoStack, redoStack, player, size, "player" + to_string(2) + ".bin", on_1, on_2);
				goto playgame;
			}
			else if (counter == 3 && (counter != number + 1))
			{
				loadGameState(undoStack, redoStack, player, size, "player" + to_string(3) + ".bin", on_1, on_2);
				goto playgame;
			}
			else if (counter == 4 && (counter != number + 1))
			{
				loadGameState(undoStack, redoStack, player, size, "player" + to_string(4) + ".bin", on_1, on_2);
				goto playgame;
			}
			else if (counter == 5 && (counter != number + 1))
			{
				loadGameState(undoStack, redoStack, player, size, "player" + to_string(5) + ".bin", on_1, on_2);
				goto playgame;
			}
			else if (counter == (number +1))
			{
				system("cls");
				drawFrame(18,46);
				break;
			}
		}
		if (check == true)
		{
			system("cls");
			break;
		}
		else
		{
			Set[0] = 7; // Default white color
			if (strcmp(resumeName[1], " ") != 0)
			{
				Set[1] = 7;
			}
			if (strcmp(resumeName[2], " ") != 0)
			{
				Set[2] = 7;
			}
			if (strcmp(resumeName[3], " ") != 0)
			{
				Set[3] = 7;
			}
			if (strcmp(resumeName[4], " ") != 0)
			{
				Set[4] = 7;
			}
			Set[5] = 7;
			if (counter == 1)
			{
				Set[0] = 14; // 14 is color yellow
			}
			if (counter == 2 && (counter != number + 1) && strcmp(resumeName[1], " ") != 0)
			{
				Set[1] = 14; 
			}
			if (counter == 3 && (counter != number + 1) && strcmp(resumeName[2], " ") != 0)
			{
				Set[2] = 14; 
			}
			if (counter == 4 && (counter != number + 1) && strcmp(resumeName[3], " ") != 0)
			{
				Set[3] = 14; 
			}
			if (counter == 5 && (counter != number + 1) && strcmp(resumeName[4], " ") != 0)
			{
				Set[4] = 14; 
			}
			if (counter == number + 1)
			{
				Set[5] = 14; 
			}
		}
	}
}

void drawFrame(int max_y, int max_x)
{

	for (int i = 0; i < max_y; i++) 
	{
		gotoyx(i + 1, 38);

		for (int j = 0; j < max_x; j++) 
		{

			string m = borderHelloScreen(i, j, max_y, max_x);
			color(getThingColor(m));
			cout << m;
		}
	}
}