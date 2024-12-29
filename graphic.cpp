#include "Header.h"

void LockConsoleSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Thiet lap kich thuoc buffer màn hình
	COORD coord;
	coord.X = width;
	coord.Y = height;
	SetConsoleScreenBufferSize(hStdout, coord);

	// Thiet lap kich thuoc cua so console
	SMALL_RECT windowSize;
	windowSize.Top = 0;
	windowSize.Left = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	SetConsoleWindowInfo(hStdout, TRUE, &windowSize);

	// Lay handle cua cua so console
	HWND consoleWindow = GetConsoleWindow();

	// Khoa kich thuoc cua so
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_SIZEBOX);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

// Co tham khao tu: https://github.com/haophancs/cpp-2048-game

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoyx(int y, int x)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int getThingColor(string c)
{
	if (c == "/" || c == "\\")
		return 11;
	else if (c == "|")
		return 14;
	else if (c == "-")
		return 10;
	else
		return 15;
}

string mapThing(int y, int x, int max_y, int max_x)
{
	if (y == 0 && x == 0) {

		return "/";
	}
	else if (y == 0 && x == max_x - 1) {

		return "\\";
	}
	else if (y == max_y - 1 && x == 0) {

		return "\\";
	}
	else if (y == max_y - 1 && x == max_x - 1) {

		return "/";
	}
	else if (x % 7 == 0) {

		return "|";
	}
	else if (y % 2 == 0) {

		return "-";
	}
	else {

		return " ";
	}
}

string borderHelloScreen(int y, int x, int max_y, int max_x)
{
	if (y == 0 && x == 0) {

		return "/";
	}
	else if (y == 0 && x == max_x - 1) {

		return "\\";
	}
	else if (y == max_y - 1 && x == 0) {

		return "\\";
	}
	else if (y == max_y - 1 && x == max_x - 1) {

		return "/";
	}
	else if (x ==0 || x == max_x-1) 
	{

		return "|";
	}
	else if (y == 0 || y == max_y-1) {

		return "-";
	}
	else 
	{

		return " ";
	}
}

int getValColor(int val) 
{

	int key = log(val) / log(2);

	switch (key) 
	{

	case 1:
		return 15;

	case 2:
		return 14;

	case 3:
		return 14;

	case 4:
		return 14;

	case 5:
		return 13;

	case 6:
		return 13;

	case 7:
		return 13;

	case 8:
		return 11;

	case 9:
		return 11;

	case 10:
		return 10;

	case 11:
		return 10;
	}
	return 0;
}

// Frame for UNDO & REDO
void Draw1(int** a, int size) 
{

	gotoyx(1, 0);

	int max_y = size * 2 + 1;
	int max_x = size * 6 + size + 1;

	for (int i = 0; i < max_y; i++) {

		for (int j = 0; j < max_x; j++) {

			string m = mapThing(i, j, max_y, max_x);
			color(getThingColor(m));
			cout << m;
		}
		cout << endl;
	}
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			int val = a[i][j];
			string val_str = to_string(val);
			if (val_str == "0") val_str = " ";

			if (val_str.length() < 4) {

				int l = val_str.length();
				for (int k = 0; k < 4 - l; k++) {
					val_str = " " + val_str;
				}
			}
			color(getValColor(val));
			gotoyx(i * 2 + 1 + 1, j * 7 + 1 + 1);
			cout << val_str;
		}
	}
	if (eng == true)
	{
		if (on_1 == false && on_2 == true)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Move up    | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Move down  | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Move left  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Move right | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [u]: Undo       | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "| [r]: Redo       | " << endl;
			gotoyx(8, size * 7 + 3);
			cout << "| [x]: Exit       | " << endl;
			gotoyx(9, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
		else if (on_1 == true && on_2 == false)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Move up    | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Move down  | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Move left  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Move right | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [u]: Undo       | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "| [x]: Exit       | " << endl;
			gotoyx(8, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
		else if (on_1 == false && on_2 == false)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Move up    | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Move down  | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Move left  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Move right | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [x]: Exit       | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
	}
	else
	{
		if (on_1 == false && on_2 == true)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Di len     | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Di xuong   | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Sang trai  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Sang phai  | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [u]: Hoan tac   | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "| [r]: Quay lai   | " << endl;
			gotoyx(8, size * 7 + 3);
			cout << "| [x]: Thoat      | " << endl;
			gotoyx(9, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
		else if (on_1 == true && on_2 == false)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Di len     | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Di xuong   | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Sang trai  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Sang phai  | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [u]: Hoan tac   | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "| [x]: Thoat      | " << endl;
			gotoyx(8, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
		else if (on_1 == false && on_2 == false)
		{
			color(7);
			gotoyx(1, size * 7 + 3);
			cout << "-------------------" << endl;
			gotoyx(2, size * 7 + 3);
			cout << "| [w]: Di len     | " << endl;
			gotoyx(3, size * 7 + 3);
			cout << "| [s]: Di xuong   | " << endl;
			gotoyx(4, size * 7 + 3);
			cout << "| [a]: Sang trai  | " << endl;
			gotoyx(5, size * 7 + 3);
			cout << "| [d]: Sang phai  | " << endl;
			gotoyx(6, size * 7 + 3);
			cout << "| [x]: Thoat      | " << endl;
			gotoyx(7, size * 7 + 3);
			cout << "-------------------" << endl << endl;
		}
	}
}

void helloScreen() // 122 - 40 
{
	int max_y = 18;
	int max_x = 46;

	for (int i = 0; i < max_y; i++) {
		gotoyx(i+1, 38);

		for (int j = 0; j < max_x; j++) {

			string m = borderHelloScreen(i, j, max_y, max_x);
			color(getThingColor(m));
			cout << m;
		}
	}
	gotoyx(3, 56);
	cout << "Welcome to: " << endl;

	color(9);
	gotoyx(5, 46);
	cout << "2222   0000     444     8888   " << endl;
	gotoyx(6, 45);
	cout << "2    2 0    0   4   4   8    8 " << endl;
	gotoyx(7, 49);
	cout << "2  0    0  4    4    8  8 " << endl;
	gotoyx(8, 48);
	cout << "2   0    0 444444444   88 " << endl;
	gotoyx(9, 47);
	cout << "2    0    0       4    8  8 " << endl;
	gotoyx(10, 46);
	cout << "2     0    0       4   8    8 " << endl;
	gotoyx(11, 45);
	cout << "2222    0000        4    8888 " << endl;

	color(7);
	gotoyx(13, 45);
	cout << "This 2048 version is created by " << endl;
	color(9);
	gotoyx(14, 41);
	cout << "[23CTT2 | 23120172 - Tran Thi Thuy Tien]" << endl;
	color(7);
	gotoyx(16, 46);
	cout << "Please press any key to start!" << endl;
	_getch(); // Waiting for user to press any key before starting to play game.
	system("cls");
}