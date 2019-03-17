#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

namespace Algorithm {

	// 点
	class Point {
		int x, y;
	public:
		Point() :x(0), y(0) {  }
		Point(int x, int y) :x(x), y(y) {  }
		friend ostream & operator << (ostream & out, const Point & p) {
			out << '(' << p.x << ',' << p.y << ')';
			return out;
		}
		friend istream & operator >> (istream & in, Point & p) {
			in >> p.x >> p.y;
			return in;
		}
	};

	// 矩阵
	template<class T>
	class Matrix {
	private:
		int row, col;
		T **mat;
	public:
		Matrix() { row = 0; col = 0; mat = NULL; }
		Matrix(int size);
		Matrix(int r, int c);
		int GetRowCount() { return row; }
		int GetColumnCount() { return col; }
		T * operator [](int i);
		void Print();
	public:
		friend ostream & operator << (ostream & out, const Matrix & p) {
			out << '(' << p.row << ',' << p.col << ')';
			return out;
		}
		friend istream & operator >> (istream & in, Matrix & p) {
			in >> p.row >> p.col;
			return in;
		}
		friend class MatrixChain;
	};

	/**
	* 打印向量
	* a 向量
	* n 长度
	*/
	template<class T>
	void PrintArray(T a[], int n);

	namespace DivideAndConquer {

		// 棋盘覆盖
		class ChessBoard {
		private:
			int size;
			Matrix<int> board;
			static int tile;
		public:
			ChessBoard(int n);
			void Init(int dr, int dc);
			void Solve(int tr, int tc, int dr, int dc, int size);
			void Print();
			static void test();
		};

		int ChessBoard::tile = 0;

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
		
		// 最大子段和
		class MaxSubSum {
		public:
			// 最大子段和问题的简单算法
			int Solve(int n, int *a, int &besti, int &bestj);
			// 最大子段和问题的分治算法
			int SolveDC(int *a, int left, int right);
			// 最大子段和问题的动态规划算法
			int SolveDP(int *a, int left, int right);
			// 测试最大子段和
			static void test();
		};


		// 矩阵连乘
		template<class T>
		class MatrixChain {
		private:
			int n;
			Matrix<int> m;
			Matrix<int> s;
			vector<Matrix<T>> chain;
			void TraceBack(int i, int j, Matrix<int> & s);
			int Count(Matrix<T> &a, Matrix<T> &b);
		public:
			MatrixChain();
			void AddMatrix(Matrix<T> & m);
			void Solve();
			void Print();
			void PrintChain();
			static void test();
		};

		// 最长公共子序列
		class LCS {
		public:
			void Solve(string a, string b, Matrix<int> & c, Matrix<int> & s);
			void Print(string a, string b, Matrix<int> & s);
			static void test();
		};

		void test();
	}

	namespace Backtracking {

		// 最大装载
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


		// 骑士巡游
		class BoxPop {
			int **grid;
			int m, n;
			static int dirs[8][2];
			list<Point> path;
		public:
			BoxPop();
			BoxPop(int m, int n);
			void Solve(int i, int j);
			void Show();
			static void test();
		protected:
			void Backtracking(int i, int j, int step);
			bool IsValid(int i, int j);
		};

		int BoxPop::dirs[8][2] = { 
			{ 1,2 },{ 2,1},{2,-1 },{1,-2 },
			{-1,-2 },{-2,-1 },{-2,1 },{-1,2 }
		};

		void test();
	}
	void test();
};