#pragma once

#include "计算机算法设计与分析.h"

using namespace std;

namespace Algorithm {
	namespace DynamicProgramming {

		namespace MaxSubSum {

			/* 最大子段和问题的简单算法*/
			int Solve(int n, int *a, int &besti, int &bestj);
			/* 最大子段和问题的分治算法*/
			int SolveDC(int *a, int left, int right);
			/* 最大子段和问题的动态规划算法*/
			int SolveDP(int *a, int left, int right);
			/* 测试最大子段和*/
			void test();
		}

		namespace MatrixChain {

			/* 矩阵连乘求解 */
			void Solve(int *p, int **m, int **s, int n);
			/* 回溯解 */
			void TraceBack(int i, int j, int **s);
			/* 3.1 测试矩阵连乘 */
			void test();
		}

		namespace LongestCommonSubsequence {

			/* 最长公共子序列 */
			void Solve(string a, string b, int **c, int **s);
			/* 打印最长公共子序列 */
			void PrintLCS(string a, string b, int **s);
			/* 3.3 测试最长公共子序列 */
			void test();
		}

		void test();
	}
}