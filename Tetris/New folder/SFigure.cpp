#include "Figure.cpp"
#include "vector"

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