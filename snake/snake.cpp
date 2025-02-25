﻿#include <iostream>
#include <Windows.h>
#include <conio.h>

class Snake
{
public:
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection wasd;
	enum color
	{
		Black = 0,
		Green = 2,
		Red = 4,
		LightBlue = 9,
		White = 7
	};

	Snake(int width, int height) : width(width), height(height), score(0), gameOver(false)
	{
		srand((unsigned)time(NULL));
		x = width / 2;
		y = height / 2;
		fructX = rand() % width;
		fructY = rand() % height;
	}

	void Color(color text)
	{
		SetConsoleTextAttribute(hConsole, (WORD)(text));
	}

	void Coordinate(int x, int y)
	{
		COORD coord = { x, y };
		SetConsoleCursorPosition(hConsole, coord);
	}

	void CMD()
	{
		wchar_t name[] = L"Snake";
		SetConsoleTitle(name);
		RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
		RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
		GetConsoleCursorInfo(hConsole, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hConsole, &structCursorInfo);
		SetConsoleCursorPosition(hConsole, coord);
		ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	}
	void Speed()
	{
		Sleep(delay);
	}

	void Start()
	{
		CMD();
		if (level == "0")
		{
			Color(LightBlue);
			Coordinate(19, 1); std::cout << "Easy";
			Coordinate(15, 2); std::cout << "Max score = 100";
			Coordinate(15, 3); std::cout << "Speed = 50 ms";
			Coordinate(11, 4); std::cout << "No death from the zone";

			Coordinate(45, 1); std::cout << "Normal";
			Coordinate(40, 2); std::cout << "Max score = 200";
			Coordinate(40, 3); std::cout << "Speed = 50 ms";

			Coordinate(70, 1); std::cout << "Hard";
			Coordinate(65, 2); std::cout << "Max score = 500";
			Coordinate(65, 3); std::cout << "Speed = 25 ms";

			Coordinate(95, 1); std::cout << "God";
			Coordinate(90, 2); std::cout << "Max score = 500";
			Coordinate(90, 3); std::cout << "Speed = 10 ms";

			for (int i = 10; i < 110; i++)
			{
				Coordinate(i, 0); std::cout << "#";
			}

			for (int i = 0; i <= 5; i++)
			{
				Coordinate(10, i); std::cout << "#";
				Coordinate(10, i + 2); std::cout << "#";
				Coordinate(35, i); std::cout << "#";
				Coordinate(60, i); std::cout << "#";
				Coordinate(85, i); std::cout << "#";
				Coordinate(110, i + 2); std::cout << "#";
				Coordinate(110, i); std::cout << "#";
			}

			for (int i = 10; i < 110; i++)
			{
				Coordinate(i, 5); std::cout << "#";
			}

			for (int i = 10; i <= 110; i++)
			{
				Coordinate(i, 7); std::cout << "#";
			}

			Coordinate(54, 6); std::cout << "level -> "; std::cin >> level;


		}

		if (level == "Easy" || level == "easy")
		{
			delay = 50;
			highScore = 100;
		}

		else if (level == "Normal" || level == "normal")
		{
			delay = 50;
			highScore = 200;
		}


		else if (level == "Hard" || level == "hard")
		{
			delay = 25;
			highScore = 500;
		}

		else if (level == "God" || level == "god")
		{
			delay = 10;
			highScore = 500;
		}
		else
		{
			delay = 1000;
			highScore = 1000;
		}
		system("CLS");
	}

	void GenMap()
	{
		CMD();
		Sleep(delay);

		std::cout << "\n\n\n";
		for (int i = 0; i <= centralization; i++)
		{
			std::cout << " ";
		}
		for (int i = 0; i <= width; i++)
		{
			Color(LightBlue);
			std::cout << "#";
		}
		std::cout << "\n";
		for (int i = 0; i <= height; i++)
		{
			for (int i = 0; i <= centralization; i++)
			{
				std::cout << " ";
			}
			for (int j = 0; j <= width; j++)
			{
				if (j == 0 || j == width)
				{

					Color(LightBlue);
					std::cout << "#";
				}

				else if (i == y && j == x)
				{
					Color(Red);
					std::cout << "O";
				}

				else if (j == fructX && i == fructY)
				{
					Color(Green);
					std::cout << "o";
				}
				else
				{
					bool tail = false;
					for (int k = 0; k < snakeTail; k++)
					{
						if (snakeTailX[k] == j && snakeTailY[k] == i)
						{
							Color(Red);
							std::cout << "o";
							tail = true;
						}
					}
					if (!tail)
						std::cout << " ";
				}
			}
			std::cout << "\n";
		}
		for (int i = 0; i <= centralization; i++)
		{
			std::cout << " ";
		}
		for (int i = 0; i <= width; i++)
		{
			Color(LightBlue);
			std::cout << "#";
		}
	}

	void Menu()
	{
		Coordinate(108, 11); std::cout << level;
		Coordinate(103, 13); std::cout << "SnakeTail: " << snakeTail;
		Coordinate(103, 14); std::cout << "Score: " << score << "/" << highScore;
		Coordinate(103, 15); std::cout << "Speed: " << delay << " ";
		Coordinate(103, 17); std::cout << "x - game over";
		Coordinate(103, 18); std::cout << "p - pause";
		Coordinate(103, 19); std::cout << "r - restart";

		for (int i = 0; i < 20; i++)
		{
			Coordinate(99 + i, 10); std::cout << "#";
		}
		for (int i = 10; i < 20; i++)
		{
			Coordinate(99, i); std::cout << "#";
			Coordinate(119, i); std::cout << "#";
		}
		for (int i = 0; i <= 20; i++)
		{
			Coordinate(99 + i, 20); std::cout << "#";
		}
	}


	void Input()
	{
		if (_kbhit())
		{
			switch (_getch()) {
			case 'a':
				if (wasd != RIGHT) { wasd = LEFT; }
				break;
			case 'd':
				if (wasd != LEFT) { wasd = RIGHT; }
				break;
			case 'w':
				if (wasd != DOWN) { wasd = UP; }
				break;
			case 's':
				if (wasd != UP) { wasd = DOWN; }
				break;
			case 'x':
				gameOver = true;
				break;
			case 'p': system("PAUSE>nul");
				break;
			}
		}
	}

	void Logic()
	{
		int X = snakeTailX[0];
		int Y = snakeTailY[0];
		int X2, Y2;
		snakeTailX[0] = x;
		snakeTailY[0] = y;

		for (int i = 1; i < snakeTail; i++)
		{
			X2 = snakeTailX[i];
			Y2 = snakeTailY[i];
			snakeTailX[i] = X;
			snakeTailY[i] = Y;
			X = X2;
			Y = Y2;

		}
		switch (wasd)
		{
		case LEFT: x--;
			break;
		case RIGHT: x++;
			break;
		case DOWN: y++;
			break;
		case UP: y--;
			break;
		default:
			break;
		}

		if (level == "Easy" || level == "easy")
		{
			if (x > width - 1) { x = 1; }
			if (x < 1) { x = width - 1; }
			if (y > height) { y = 0; }
			if (y < 0) { y = height; }

		}

		else
		{
			if (x > width || x < 0 || y > height || y < 0 || x == width || x == 0)
			{
				gameOver = true;
			}
		}

		for (int i = 0; i < snakeTail; i++)
		{
			if (snakeTailX[i] == x && snakeTailY[i] == y)
				gameOver = true;
		}
		if (score == highScore)
		{
			youWin = true;
		}
	}

	void GenApple()
	{
		srand((unsigned)time(NULL));
		fructX = rand() % width;
		fructY = rand() % height;
	}
	void Apple()
	{

		for (int k = 0; k < snakeTail; k++)
		{
			if (snakeTailX[k] == fructX && snakeTailY[k] == fructY)
			{
				GenApple();
			}
		}
		if (x == fructX && y == fructY)
		{
			if (delay > 1) delay -= 1;
			score += 1;
			snakeTail += 1;
			GenApple();
		}
		if (fructX > width || x < 0 || fructY > height || fructY < 0 || fructX == width || fructX == 0 || fructY == height)
		{
			GenApple();
		}
	}

	bool GameOver()
	{
		return gameOver;
	}
	bool YouWin()
	{
		return youWin;
	}

private:
	std::string level = "0";
	int highScore = 0;
	int snakeTail = 0;
	int delay = 0;
	int centralization = 35, width, height, x, y, fructX, fructY, score;
	bool gameOver = false;
	bool youWin = false;
	int snakeTailX[1000], snakeTailY[1000];
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, FALSE);
	CONSOLE_CURSOR_INFO structCursorInfo;
};

int main()
{
	Snake snake(50, 20);
	snake.Start();
	snake.GenApple();
	snake.Speed();
	while (!snake.GameOver() && !snake.YouWin())
	{
		snake.Apple();
		snake.Input();
		snake.GenMap();
		snake.Menu();
		snake.Logic();
	}

	if (snake.YouWin())
	{
		snake.Coordinate(57, 13); snake.Color(Snake::color::Green); std::cout << "YOU WIN";
	}
	else
	{
		snake.Coordinate(57, 13); snake.Color(Snake::color::Red); std::cout << "GAME OVER";
	}

	while (!_kbhit());
	char c = _getch();
	if (c == 'R' || c == 'r')
	{
		system("cls");
		main();
	}
	else
	{
		snake.GenMap();
		snake.Coordinate(57, 13); snake.Color(Snake::color::Green); std::cout << "GooD Bye";
		system("PAUSE>nul");
	}
}
