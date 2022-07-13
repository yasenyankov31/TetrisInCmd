#include "Figure.cpp"
#include "vector"
class LFigure :public Figure
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
	LFigure()
	{
		fig = L;
		rotations = { L,L1,L2,L3 };
	}

};