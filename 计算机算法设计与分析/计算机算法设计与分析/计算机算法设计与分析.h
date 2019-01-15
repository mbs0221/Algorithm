#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

namespace Algorithm {

	/**
	* 初始化矩阵
	* rows 行数
	* cols 列数
	*/
	int **InitMatrix(int rows, int cols);

	/**
	* 初始化矩阵
	* mat 矩阵
	* size 大小
	*/
	int **InitMatrix(int size);

	/**
	* 打印矩阵
	* mat 矩阵
	* size 大小
	*/
	void PrintMatrix(int **mat, int size);

	/**
	* 打印向量
	* a 向量
	* n 长度
	*/
	template<class T>
	void PrintArray(T a[], int n);

	namespace DivideAndConquer {

		// 棋盘覆盖
		namespace ChessBoard {

			static int tile = 0;

			void Init(int **board, int dr, int dc);
			/**
			* 棋盘覆盖
			* tr 棋盘左上角方格行号
			* tc 棋盘左上角方格列号
			* dr 特殊方格所在行号
			* dc 特殊方格所在列号
			* size 棋盘大小
			*/
			void Solve(int **board, int tr, int tc, int dr, int dc, int size);
			void test();
		}

		// 归并排序
		namespace MergeSort {

			template<class T> void MergeArray(T a[], T b[], int left, int mid, int right);
			template<class T> void Sort(T a[], T b[], int left, int right);
			void test();
		}

		// 非递归版归并排序
		namespace MergeSortNonrecursive {
			template<class T> void Merge(T a[], T b[], int left, int mid, int right);
			template<class T> void MergePass(T a[], T b[], int sz, int n);
			template<class T> void Sort(T a[], T b[], int n);
			void test();
		}

		// 快速排序
		namespace QuickSort {
			template<class T>
			int Partition(T a[], int p, int r);
			template<class T>
			void Sort(T a[], int left, int right);
			void test();
		}

		void test();
	}

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

	namespace Backtracking {

		template<class T>
		class Loading {
		public:
			Loading(T *w, T c, int n);
			~Loading();
			static void test();
			friend T MaxLoading(T *, T, int);

		private:
			void Backtrack(int n);
			int n; // 集装箱数
			T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
		};

		template<class T>
		class XLoading {
		public:
			XLoading(T *w, T c, int n, int *bestx);
			~XLoading();
			static void test();
			friend T MaxXLoading(T *w, T c, int n, int *bestx);

		private:
			void Backtrack(int i);
			int n; // 集装箱数
			int *x, *bestx; // 当前解，当前最优解
			T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
			T r; // 剩余集装箱重量
		};

		template<class T>
		T MaxMLoading(T *w, T c, int n, int *bestx);

		class Flowshop {
			friend int Flow(int**, int, int *);
		public:
			Flowshop(int **, int, int *);
			~Flowshop();
			static void test();
		private:
			void Backtrack(int i);
			int **M; // 各作业所需的处理时间
			int *x; // 当前作业调度
			int *bestx; // 当前最优作业调度
			int *f2; // 机器2完成处理的时间
			int f1; // 机器1完成处理的时间
			int f; // 完成时间和
			int bestf; // 当前最优值
			int n; // 作业数
		};

		void test();
	}
	void test();
};