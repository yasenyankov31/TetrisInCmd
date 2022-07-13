#pragma once
#include "Figure.h"
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
	SFigure();

};





