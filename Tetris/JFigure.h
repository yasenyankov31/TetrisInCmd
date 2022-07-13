#pragma once
#include "Figure.h"

class JFigure:public Figure
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
	JFigure();
};

