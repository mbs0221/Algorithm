#pragma once

#include <iostream>
#include <string>
#include <iomanip>

namespace DynamicProgramming {

	namespace MaxSubSum {
		/* ����Ӷκ�����ļ��㷨*/
		int Solve(int n, int *a, int &besti, int &bestj);
		/* ����Ӷκ�����ķ����㷨*/
		int SolveDC(int *a, int left, int right);
		/* ����Ӷκ�����Ķ�̬�滮�㷨*/
		int SolveDP(int *a, int left, int right);
	}

	namespace MatrixChain {

		void Solve(int *p, int **m, int **s, int n);
		void TraceBack(int i, int j, int **s);
	}

	/**
	* ��ʼ������
	* rows ����
	* cols ����
	*/
	int **InitMatrix(int rows, int cols);

	void test_3_1();
	void test_3_3();
	void test_3_4();

	void test();
};