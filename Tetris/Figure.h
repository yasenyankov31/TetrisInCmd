#pragma once
#include<vector>
#include <algorithm>

using namespace std;

const int boardHeight = 20;
const int boardWidth = 10;

bool CheckIfCanRotate(char board[boardHeight][boardWidth], vector<vector<char>> figure, int y, int x);
void InsertFigure(char board[boardHeight][boardWidth], vector<vector<char>> figure, int y, int x);
void ClearA(char board[boardHeight][boardWidth]);

class Figure
{
	
public:
	int phase;
	vector<vector<char>> fig;
	vector<vector<vector<char>>> rotations;
	void Rotate(char Board[boardHeight][boardWidth], vector<vector<vector<char>>> Rotations, int y, int x);
};

