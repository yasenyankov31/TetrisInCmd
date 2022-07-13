#include "Figure.cpp"
#include "vector"

class JFigure :public Figure
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
	JFigure()
	{
		fig = J;
		rotations = { J,J1,J2,J3 };
	}

};
