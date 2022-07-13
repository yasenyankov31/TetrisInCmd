#include "Figure.cpp"
#include "vector"

class OFigure :public Figure
{
public:
	vector<vector<char>> O = { { 'A','A' }
								,{ 'A', 'A'}
	};
	OFigure()
	{
		fig = O;
		rotations = {};
	}

};