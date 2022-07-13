#include <iostream>
#include <thread>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include "Figure.h"
#include "IFigure.h"
#include "LFigure.h"
#include "SFigure.h"
#include "ZFigure.h"
#include "JFigure.h"
#include "OFigure.h"
#include "TFigure.h"

using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define VK_RIGHT          0x44 //D button
#define VK_LEFT           0x41 //A button
#define VK_DOWN			  0x53 //S button
#define VK_ROTATE         0x52 //R button

char board[boardHeight][boardWidth] = {};

void ClearScreen()
{
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void ChangeToB()
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		replace(std::begin(board[i]), std::end(board[i]), 'A', 'B');
	}

}

void LastMove(int x, int y, int dirx)
{
	bool interupt=false;
	vector<pair<int, int>> cordinates;//x,y
	for (size_t i = boardHeight - 1; i >= y; i--)
	{
		for (size_t j = 1; j < boardWidth; j++)
		{
			if (board[i][j] == 'A')
			{
				if (board[i][j + dirx] == 'B'|| board[i+1][j + dirx] == 'B')
				{
					interupt = true;
				}
				pair<int, int> xy = { j,i };
				cordinates.push_back(xy);
			}
		}
	}
	if (!interupt)
	{
		ClearA(board);
		for (size_t i = 0; i < cordinates.size(); i++)
		{
			board[cordinates[i].second][cordinates[i].first + dirx] = 'A';
		}
	}

}

void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void RenderBoard(int score)
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		printf("#");
		for (size_t j = 0; j < boardWidth; j++)
		{
			printf("%c", board[i][j]);
		}
		if (i == 4)
		{
			cout << "#  Score: " << score<<"\n";
		}
		else
		{
			printf("#\n");
		}
		


	}
}



int main()
{
	for (size_t i = 0; i < boardHeight - 1; i++)
	{
		fill(board[i], board[i] + 10, ' ');
	}
	fill(board[boardHeight - 1], board[boardHeight - 1] + 10, '#');

	IFigure figureI;
	SFigure figureS;
	ZFigure figureZ;
	LFigure figureL;
	JFigure figureJ;
	TFigure figureT;
	OFigure figureO;

	Figure figures[7];
	figures[0] = figureI;
	figures[1] = figureS;
	figures[2] = figureZ;
	figures[3] = figureL;
	figures[4] = figureJ;
	figures[5] = figureT;
	figures[6] = figureO;

	int y, x, posY = 0, posX = 5;
	srand(time(NULL));
	int randomFigure = (rand() % 6) + 1;
	InsertFigure(board, figures[randomFigure].fig, posY, posX);

	HideCursor();

	bool nearWallLeft;
	bool nearWallRight;
	int score = 0;

	bool canMove = true;

	int timeSpeed = 250;
	bool GameOver = false;

	while (!GameOver)
	{
		vector<int> deletedRows;
		timeSpeed = 250;
		int stepsDown = 1;
		//reset flags
		x = 0;
		y = 0;
		nearWallLeft = false;
		nearWallRight = false;

		//input
		if (GetAsyncKeyState(VK_RIGHT) != 0 && GetAsyncKeyState(VK_RIGHT) != 1 && posX < boardWidth)
		{
			x = 1;
			posX++;
		}
		if (GetAsyncKeyState(VK_LEFT) != 0 && GetAsyncKeyState(VK_LEFT) != 1 && posX > 0)
		{
			x = -1;
			posX--;
		}
		if (GetAsyncKeyState(VK_DOWN) != 0 && GetAsyncKeyState(VK_DOWN) != 1 && canMove)
			timeSpeed = timeSpeed / 4;

		if (GetAsyncKeyState(VK_ROTATE) != 0 && GetAsyncKeyState(VK_ROTATE) != 1)
			figures[randomFigure].Rotate(board, figures[randomFigure].rotations, posY, posX);






		//loop for collision
		for (int i = boardHeight - 2; i > 0; i--)
		{
			if (board[i][0] == 'A')
			{
				nearWallLeft = true;
			}
			if (board[i][9] == 'A')
			{
				nearWallRight = true;
			}
			int bCount = 0;
			for (size_t j = 0; j < boardWidth; j++)
			{
				if (board[i][j] == 'A')
				{

					if ((board[i + 1][j] == 'B' || board[i + 1][j] == '#'))
					{
						canMove = false;
					}
					if (j != 0 && j != boardWidth - 1)
					{
						if (board[i][j - 1] == 'B')
						{
							nearWallLeft = true;
						}
						else if (board[i][j + 1] == 'B')
						{
							nearWallRight = true;
						}
					}


				}
				else if (board[i][j] == 'B')
				{
					bCount++;
				}


			}
			if (bCount == 10)
			{
				score += 100;
				deletedRows.push_back(i);
				fill(board[i], board[i] + 10, ' ');
			}


		}


		//move piece
		for (int i = boardHeight - 2; i >= 0; i--)
		{
			for (size_t j = 0; j < boardWidth; j++)
			{

				if (board[i][j] == 'A')
				{
					if (canMove)
					{
						if ((!nearWallLeft && x == -1) || (!nearWallRight && x == 1))
						{
							swap(board[i][j], board[i + stepsDown][j + x]);
						}
						else
						{
							swap(board[i][j], board[i + stepsDown][j]);
						}
					}
					else
					{
						if ((!nearWallLeft && x == -1) || (!nearWallRight && x == 1))
						{
							LastMove(posX, posY, x);
						}
						canMove = true;
						posY = 0;
						posX = 5;
						srand(time(NULL));
						figures[randomFigure].phase = 0;
						randomFigure = (rand() % 6) + 1;
						ChangeToB();
						//Game Over
						for (size_t i = 0; i < boardWidth; i++)
						{
							if (board[1][i] == 'B')
							{
								i = boardWidth;
								GameOver = true;
								break;
							}
						}

						InsertFigure(board, figures[randomFigure].fig, posY, posX);

					}
				}

				else if (board[i][j] == 'B')
				{
					for (size_t k = 0; k < deletedRows.size(); k++)
					{
						if (i < deletedRows[k])
						{
							swap(board[i][j], board[i + deletedRows.size()][j]);
							break;
						}
					}

				}

			}
		}


		
		RenderBoard(score);

		
		std::this_thread::sleep_for(std::chrono::milliseconds(timeSpeed));
		ClearScreen();
		if (canMove)
		{
			posY++;
		}


	}
	std::system("cls");
	std::cout << "Game Over!Your score is " << score;



	return 0;
}

