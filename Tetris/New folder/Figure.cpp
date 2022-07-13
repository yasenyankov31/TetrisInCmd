
#include "Tetris.cpp"
#include <vector>



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


