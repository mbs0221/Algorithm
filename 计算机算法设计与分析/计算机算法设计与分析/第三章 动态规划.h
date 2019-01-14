#pragma once

#include <iostream>
#include <string>
#include <iomanip>

namespace DynamicProgramming {

	namespace MaxSubSum {
		/* 最大子段和问题的简单算法*/
		int Solve(int n, int *a, int &besti, int &bestj);
		/* 最大子段和问题的分治算法*/
		int SolveDC(int *a, int left, int right);
		/* 最大子段和问题的动态规划算法*/
		int SolveDP(int *a, int left, int right);
	}

	namespace MatrixChain {

		void Solve(int *p, int **m, int **s, int n);
		void TraceBack(int i, int j, int **s);
	}

	/**
	* 初始化矩阵
	* rows 行数
	* cols 列数
	*/
	int **InitMatrix(int rows, int cols);

	void test_3_1();
	void test_3_3();
	void test_3_4();

	void test();
};