#include <iostream>
#include <thread>
#include <Windows.h>
#include <algorithm>
#include <vector>


using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define VK_RIGHT          0x44 //D button
#define VK_LEFT           0x41 //A button
#define VK_DOWN			  0x53 //S button
#define VK_ROTATE         0x52 //R button

const int boardHeight = 20;
const int boardWidth = 10;


void ClearScreen()
{
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void InsertFigure(char board[boardHeight][boardWidth], vector<vector<char>> figure, int y, int x)
{
	int a = 0;
	if (y + figure.size() <= boardHeight && x + figure[0].size() <= boardWidth)
	{
		for (size_t i = y; i < y + figure.size(); i++)
		{
			for (size_t j = 0; j < figure[0].size(); j++)
			{
				if (figure[a][j] != ' ')
				{
					board[i][x + j] = figure[a][j];
				}
			}
			a++;

		}
	}


}

void ClearA(char board[boardHeight][boardWidth])
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		replace(std::begin(board[i]), std::end(board[i]), 'A', ' ');
	}

}

void ChangeToB(char board[boardHeight][boardWidth])
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		replace(std::begin(board[i]), std::end(board[i]), 'A', 'B');
	}

}

void LastMove(int x, int y, int dirx, char board[boardHeight][boardWidth])
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

bool CheckIfCanRotate(char board[boardHeight][boardWidth], vector<vector<char>> figure, int y, int x)
{
	for (size_t i = y; i < y + figure.size(); i++)
	{
		for (size_t j = 0; j < figure[0].size(); j++)
		{
			if (board[i][x + j] == 'B' || x + j<0 || x + j>boardWidth - 1 || board[i][x + j] == '#')
			{
				return false;
			}
		}

	}
	return true;
}

class Figure
{
public:
	int phase = 0;
	vector<vector<char>> fig;
	vector<vector<vector<char>>> rotations;

	void Rotate(char Board[boardHeight][boardWidth], vector<vector<vector<char>>> Rotations, int y, int x)
	{
		int prevPhase = phase;
		if (Rotations.size() > 0)
		{
			(phase < Rotations.size() - 1) ? phase++ : phase = 0;

			if (CheckIfCanRotate(Board, Rotations[phase], y, x))
			{
				ClearA(Board);
				InsertFigure(Board, Rotations[phase], y, x);
			}
			else
			{
				phase = prevPhase;
			}

		}


	};

};

class IFigure :public Figure
{
public:

	vector<vector<char>> I = { {'A'},
							{'A'},
							{'A'},
							{'A'}
	};
	vector<vector<char>> I1 = { {'A','A','A','A'}
	};
	IFigure()
	{
		fig = I;
		rotations = { I,I1 };
	}

};

class SFigure :public Figure
{
public:
	vector<vector<char>> S = { {' ','A','A'},
								 {'A','A',' '}
	};
	vector<vector<char>> S1 = { {'A',' '},
								{'A','A'},
								{' ','A'}
	};
	SFigure()
	{
		fig = S;
		rotations = { S,S1 };
	}

};

class ZFigure :public Figure
{
public:
	vector<vector<char>> Z = { {'A','A',' '},
								 {' ','A','A'}
	};
	vector<vector<char>> Z1 = { {' ','A'},
								  {'A','A'},
								  {'A',' '}
	};
	ZFigure()
	{
		fig = Z;
		rotations = { Z,Z1 };
	}

};

class LFigure :public Figure
{
public:
	vector<vector<char>> L = { {'A',' '},
								{'A',' '},
								{'A','A'},
	};
	vector<vector<char>> L1 = { {' ',' ','A'},
								  {'A','A','A'},
	};
	vector<vector<char>> L2 = { {'A','A'},
								  {' ','A'},
								{' ','A'},
	};
	vector<vector<char>> L3 = { {'A','A','A'},
						{'A',' ',' '},
	};
	LFigure()
	{
		fig = L;
		rotations = { L,L1,L2,L3 };
	}

};

class JFigure :public Figure
{
public:
	vector<vector<char>> J = { {' ','A'},
					   {' ','A'},
					   {'A','A'},
	};
	vector<vector<char>> J1 = { {'A','A','A'},
						{' ',' ','A'},
	};
	vector<vector<char>> J2 = { {'A','A'},
						{'A',' '},
						{'A',' '},
	};
	vector<vector<char>> J3 = { {'A',' ',' '},
						{'A','A','A'},
	};
	JFigure()
	{
		fig = J;
		rotations = { J,J1,J2,J3 };
	}

};

class TFigure :public Figure
{
public:
	vector<vector<char>> T = { {'A','A','A'},
					   {' ','A',' '}
	};
	vector<vector<char>> T1 = { {'A',' '},
						{'A','A'},
						{'A',' '},
	};
	vector<vector<char>> T2 = { {' ','A',' '},
						{'A','A','A'}
	};
	vector<vector<char>> T3 = { {' ','A'},
						{'A','A'},
						{' ','A'},
	};
	TFigure()
	{
		fig = T;
		rotations = { T,T1,T2,T3 };
	}
};

class OFigure :public Figure
{
public:
	vector<vector<char>> O = { { 'A','A' }
								,{ 'A', 'A'}
	};
	OFigure()
	{
		fig = O;
		rotations = {};
	}

};


void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void RenderBoard(char board[boardHeight][boardWidth],int score)
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
	int figureplace;
	int boardspaces[boardHeight][boardWidth];

	char board[boardHeight][boardWidth] = {};


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

					if ((board[i + 1][j] == 'B' || board[i + 1][j] == '#')|| (board[i + 1][j+x] == 'B' || board[i + 1][j+x] == '#'))
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
							LastMove(posX, posY, x, board);
						}
						canMove = true;
						posY = 0;
						posX = 5;
						srand(time(NULL));
						figures[randomFigure].phase = 0;
						randomFigure = (rand() % 6) + 1;
						ChangeToB(board);
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


		
		RenderBoard(board,score);

		
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

