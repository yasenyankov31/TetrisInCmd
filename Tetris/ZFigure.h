#pragma once
#include "Figure.h"
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
	ZFigure();

};

