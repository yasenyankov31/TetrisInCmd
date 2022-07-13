
#include "Figure.cpp"
#include "vector"

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
	IFigure()
	{
		fig = I;
		rotations = { I,I1 };
	}

};












