#pragma once

#include <queue>

class Dir
{
public :
	int row, col;
	Dir(int row, int col) :row(row), col(col)
	{

	}
};

class BranchAndBound
{
	int matrix[4][4] = 
	{
		{1,  2,  3,  4},
		{5,  6,  7,  8},
		{9,  10, 11, 12},
		{13, 14, 15, 0}
	};

	int distance(int **mat1, int **mat2) 
	{
		int count = 0;
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (mat1[i][j] != mat2[i][j]) 
				{
					count++;
				}
			}
		}
	}

	void solve(int **correct, int **matrix, int n) 
	{
		int step = 0;
		std::priority_queue<Dir> q;
		q.push(Dir(3, 3));
		while (!q.empty()) {
			int d = distance(correct, matrix);// 在位方格数


		}
	}
};