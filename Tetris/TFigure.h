#pragma once
#include "Figure.h"
class TFigure:public Figure
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
	TFigure();
};

