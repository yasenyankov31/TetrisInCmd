#include "Figure.h"



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
		replace(begin(board[i]), end(board[i]), 'A', ' ');
	}

}


void Figure::Rotate(char Board[boardHeight][boardWidth], vector<vector<vector<char>>> Rotations, int y, int x)
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
