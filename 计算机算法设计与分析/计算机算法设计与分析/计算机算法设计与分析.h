#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

namespace Algorithm {

	// ��
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

	// ����
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
	* ��ӡ����
	* a ����
	* n ����
	*/
	template<class T>
	void PrintArray(T a[], int n);

	namespace DivideAndConquer {

		// ���̸���
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

		// �鲢����
		namespace MergeSort {

			template<class T> void MergeArray(T a[], T b[], int left, int mid, int right);
			template<class T> void Sort(T a[], T b[], int left, int right);
			void test();
		}

		// �ǵݹ��鲢����
		namespace MergeSortNonrecursive {
			template<class T> void Merge(T a[], T b[], int left, int mid, int right);
			template<class T> void MergePass(T a[], T b[], int sz, int n);
			template<class T> void Sort(T a[], T b[], int n);
			void test();
		}

		// ��������
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
		
		// ����Ӷκ�
		class MaxSubSum {
		public:
			// ����Ӷκ�����ļ��㷨
			int Solve(int n, int *a, int &besti, int &bestj);
			// ����Ӷκ�����ķ����㷨
			int SolveDC(int *a, int left, int right);
			// ����Ӷκ�����Ķ�̬�滮�㷨
			int SolveDP(int *a, int left, int right);
			// ��������Ӷκ�
			static void test();
		};


		// ��������
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

		// �����������
		class LCS {
		public:
			void Solve(string a, string b, Matrix<int> & c, Matrix<int> & s);
			void Print(string a, string b, Matrix<int> & s);
			static void test();
		};

		void test();
	}

	namespace Backtracking {

		// ���װ��
		template<class T>
		class Loading {
		public:
			Loading(T *w, T c, int n);
			~Loading();
			static void test();
			friend T MaxLoading(T *, T, int);

		private:
			void Backtrack(int n);
			int n; // ��װ����
			T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
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
			int n; // ��װ����
			int *x, *bestx; // ��ǰ�⣬��ǰ���Ž�
			T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
			T r; // ʣ�༯װ������
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
			int **M; // ����ҵ����Ĵ���ʱ��
			int *x; // ��ǰ��ҵ����
			int *bestx; // ��ǰ������ҵ����
			int *f2; // ����2��ɴ����ʱ��
			int f1; // ����1��ɴ����ʱ��
			int f; // ���ʱ���
			int bestf; // ��ǰ����ֵ
			int n; // ��ҵ��
		};


		// ��ʿѲ��
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