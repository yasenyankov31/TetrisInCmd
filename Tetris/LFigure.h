#pragma once
#include "Figure.h"
class LFigure:public Figure
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
	LFigure();
};

