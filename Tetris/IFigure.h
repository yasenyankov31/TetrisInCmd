#pragma once

#include "Figure.h"

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
	IFigure();
};

