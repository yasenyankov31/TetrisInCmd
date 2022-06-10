#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>
#include <algorithm>
#include <vector>


using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define VK_RIGHT          0x44
#define VK_LEFT           0x41
#define VK_DOWN			  0x53
#define VK_ROTATE         0x52

const int boardHeight = 20;
const int boardWidth = 10;

void cls()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

void InsertFigure(string board[boardHeight][boardWidth], vector<vector<string>> figure, int y, int x)
{
	int a = 0;
	for (size_t i = y; i < y + figure.size(); i++)
	{
		for (size_t j = 0; j < figure[0].size(); j++)
		{
			board[i][x + j] = figure[a][j];

		}
		a++;

	}

}

void ClearA(string board[boardHeight][boardWidth])
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		replace(std::begin(board[i]), std::end(board[i]), "A", ".");
	}

}

void ChangeToB(string board[boardHeight][boardWidth])
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		replace(std::begin(board[i]), std::end(board[i]), "A", "B");
	}

}


class Figure
{
public:
	int phase = 0;
	vector<vector<string>> fig;
	vector<vector<vector<string>>> rotations;

	void Rotate(string Board[boardHeight][boardWidth], vector<vector<vector<string>>> Rotations, int y, int x)
	{
		if (Rotations.size() > 0 && x + 4 < boardWidth && y + 4 < boardHeight)
		{
			ClearA(Board);
			if (phase < Rotations.size() - 1)
			{
				phase++;
			}
			else
			{
				phase = 0;
			}
			InsertFigure(Board, Rotations[phase], y, x);
		}


	};

};

class IFigure :public Figure
{
public:

	vector<vector<string>> I = { {"A"},
							{"A"},
							{"A"},
							{"A"}
	};
	vector<vector<string>> I1 = { {"A","A","A","A"}
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
	vector<vector<string>> S = { {".","A","A"},
								 {"A","A","."}
	};
	vector<vector<string>> S1 = { {"A","."},
								{"A","A"},
								{".","A"}
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
	vector<vector<string>> Z = { {"A","A","."},
								 {".","A","A"}
	};
	vector<vector<string>> Z1 = { {".","A"},
								  {"A","A"},
								  {"A","."}
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
	vector<vector<string>> L = { {"A","."},
								{"A","."},
								{"A","A"},
	};
	vector<vector<string>> L1 = { {".",".","A"},
								  {"A","A","A"},
	};
	vector<vector<string>> L2 = { {"A","A"},
								  {".","A"},
								{".","A"},
	};
	vector<vector<string>> L3 = { {"A","A","A"},
						{"A",".","."},
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
	vector<vector<string>> J = { {".","A"},
					   {".","A"},
					   {"A","A"},
	};
	vector<vector<string>> J1 = { {"A","A","A"},
						{".",".","A"},
	};
	vector<vector<string>> J2 = { {"A","A"},
						{"A","."},
						{"A","."},
	};
	vector<vector<string>> J3 = { {"A",".","."},
						{"A","A","A"},
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
	vector<vector<string>> T = { {"A","A","A"},
					   {".","A","."}
	};
	vector<vector<string>> T1 = { {"A","."},
						{"A","A"},
						{"A","."},
	};
	vector<vector<string>> T2 = { {".","A","."},
						{"A","A","A"}
	};
	vector<vector<string>> T3 = { {".","A"},
						{"A","A"},
						{".","A"},
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
	vector<vector<string>> O = { { "A","A" }
								,{ "A", "A"}
	};
	OFigure()
	{
		fig = O;
		rotations = {};
	}

};


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void RenderBoard(string board[boardHeight][boardWidth])
{
	for (size_t i = 0; i < boardHeight; i++)
	{
		cout << "#";
		for (size_t j = 0; j < boardWidth; j++)
		{
			cout << board[i][j];
		}
		cout << "#" << "\n";

	}
}




int main()
{


	int figureplace;
	int boardspaces[boardHeight][boardWidth];

	string board[boardHeight][boardWidth];


	for (size_t i = 0; i < boardHeight - 1; i++)
	{
		fill(board[i], board[i] + 10, ".");
	}
	fill(board[boardHeight - 1], board[boardHeight - 1] + 10, "#");

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
	int randomFigure = rand() % 6 + 0;
	InsertFigure(board, figures[randomFigure].fig, posY, posX);

	ShowConsoleCursor(false);

	bool nearWallLeft;
	bool nearWallRight;
	int score = 0;

	while (true)
	{
		//Game Over
		if (board[0][5]=="B")
		{
			break;
		}
		//reset flags
		x = 0;
		y = 0;
		nearWallLeft = false;
		nearWallRight = false;

		//input
		if (GetAsyncKeyState(VK_RIGHT) != 0 && GetAsyncKeyState(VK_RIGHT) != 1)
			x = 1;
		posX++;
		if (GetAsyncKeyState(VK_LEFT) != 0 && GetAsyncKeyState(VK_LEFT) != 1)
			x = -1;
		posX--;
		if (GetAsyncKeyState(VK_DOWN) != 0 && GetAsyncKeyState(VK_DOWN) != 1)
			y = 1;
		if (GetAsyncKeyState(VK_ROTATE) != 0 && GetAsyncKeyState(VK_ROTATE) != 1)
			figures[randomFigure].Rotate(board, figures[randomFigure].rotations, posY, posX);


		
		int deletedRows = 0;
		//loop for collision
		for (int i = boardHeight - 2; i > 0; i--)
		{
			int bCount = 0;
			for (size_t j = 1; j < boardWidth; j++)
			{
				if (board[i][j] == "A")
				{
					if (board[i + 1][j] == "B" || board[i + 1][j] == "#")
					{
						posY = 0;
						posX = 5;
						srand(time(NULL));
						figures[randomFigure].phase = 0;
						randomFigure = rand() % 6 + 0;
						ChangeToB(board);
						InsertFigure(board, figures[randomFigure].fig, posY, posX);
						break;
					}
					if (board[i][j - 1] == "B" || board[i][0] == "A")
					{
						nearWallLeft = true;
					}
					if (board[i][j + 1] == "B" || board[i][9] == "A")
					{
						nearWallRight = true;
					}

				}
				if (board[i][j] == "B")
				{
					bCount++;
				}


			}
			if (bCount==9&& board[i][0] == "B")
			{
				deletedRows++;
				score += 100;
				fill(board[i], board[i] + 10, ".");
			}

		}

		//move piece
		for (int i = boardHeight - 2; i >= 0; i--)
		{
			for (size_t j = 0; j < boardWidth; j++)
			{

				if (board[i][j] == "A")
				{
					if (!nearWallLeft && x == -1)
					{
						swap(board[i][j], board[i + 1][j - 1]);
					}
					else if (!nearWallRight && x == 1)
					{
						swap(board[i][j], board[i + 1][j + 1]);
					}
					else
					{
						swap(board[i][j], board[i + 1][j]);
					}
				}
				if (board[i][j] == "B")
				{
					if (board[i+1][j] == "." && deletedRows != 0)
					{
						swap(board[i][j], board[i + deletedRows][j]);
					}
					
				}
			}
		}

		RenderBoard(board);


		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		cls();
		posY++;

	}
	cout << "Game Over! Your score is " << score;



	return 0;
}

