#pragma once


#include "ds.h"

using namespace std;
using namespace DataStructure;

namespace Algorithm {

	template<class T>
	void PrintArray(T a[], int n);

	// 分治
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

	// 动态规划
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


		// 3.11 最优二叉搜索树
		class OptimalBST {
			int n;
			Matrix<int> a, b;
			Matrix<int> m, s, w;
		public:
			void Solve();
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
			Matrix<int> c, s;
			string a, b;
		public:
			LCS(string &a, string &b);
			void Solve();
			void Print();
			static void test();
		};

		// 最长上升子序列
		class LAS {
			Matrix<int> dp;
		public:
			void Solve(int nums[], int N);
			void Print();
			static void test();
		};

		// 字符串
		class String {
		public:
			int EditDistance(string a, string & b);
			static void test();
		};
		void test();
	}

	// 回溯法
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
			list<Vector<int>> path;
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

		// 玩家
		class Player {
			Vector<int> x;
		public:
			Player() {  }
			Vector<int> & GetPosition() { return x; }
			void SetPosition(Vector<int> v) { x = v; }
		};

		// HDU1016 Prime Ring Problem
		class PrimeRing {
			int number;
			int *table;
			bool *visited;
			bool prime[100];
		protected:
			bool isPrime(int num);
			void Backtracking(int step);
		public:
			PrimeRing();
			void Solve(int n);
			void Print();
			static void test();
		};

		// 井字棋游戏
		class TicTacToe {
			Player a, b;// 玩家
			Matrix<int> table; // 棋盘
		public:
			
		};

		// 拼图游戏
		class Jigsaw {
			Matrix<int> m;
		public:
			void Solve();
		};


		//class Jigsaw
		//{
		//	int matrix[4][4] =
		//	{
		//		{ 1,  2,  3,  4 },
		//		{ 5,  6,  7,  8 },
		//		{ 9,  10, 11, 12 },
		//		{ 13, 14, 15, 0 }
		//	};

		//	int distance(int **mat1, int **mat2)
		//	{
		//		int count = 0;
		//		for (int i = 0; i < 4; i++)
		//		{
		//			for (int j = 0; j < 4; j++)
		//			{
		//				if (mat1[i][j] != mat2[i][j])
		//				{
		//					count++;
		//				}
		//			}
		//		}
		//	}

		//	void solve(int **correct, int **matrix, int n)
		//	{
		//		int step = 0;
		//		std::priority_queue<Dir> q;
		//		q.push(Dir(3, 3));
		//		while (!q.empty()) {
		//			int d = distance(correct, matrix);// 在位方格数


		//		}
		//	}
		//};
		void test();
	}
	
	// 数据挖掘
	namespace DataMining {
		
		// 频繁项集
		class Item {
			int id;
			int frequency;
			double support;
		public:
			Item() { id = 0; frequency = 0; support = 0; }
			Item(const Item &item) { id = item.id; frequency = item.frequency; support = item.support; }
			Item(int id, int freq) :id(id), frequency(freq) {  }
			int getId() { return id; }
			int getFrequency() { return this->frequency; }
			double getSupport() { return this->support; }
			void setSupport(double s) { support = s; }
			void increase() { this->frequency++; }
			bool operator < (Item &b) { return frequency < b.frequency; }
			bool operator <= (Item &b) { return frequency <= b.frequency; }
			bool operator == (Item &b) { return frequency == b.frequency; }
			bool operator >= (Item &b) { return frequency >= b.frequency; }
			bool operator > (Item &b) { return frequency > b.frequency; }
		};

		// FP-Tree Node
		class FPTreeNote {
			Item item;
			FPTreeNote *child, *sibling;
			FPTreeNote *next;
		};

		// FP-Tree
		class FPTree {
			map<string, Item*> table;
			FPTreeNote *root;
		public:
			void put(string item);
			void build(list<string> ts);
			static void test();
		};

		void readlines(list<string> &lines, string file);

		void test();
	}
	void test();
};