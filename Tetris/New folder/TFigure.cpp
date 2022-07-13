#include "Figure.cpp"
#include "vector"

class TFigure :public Figure
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
	TFigure()
	{
		fig = T;
		rotations = { T,T1,T2,T3 };
	}
};