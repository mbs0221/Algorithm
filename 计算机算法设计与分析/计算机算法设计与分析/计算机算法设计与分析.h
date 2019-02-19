#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

namespace Algorithm {

	/**
	* ��ʼ������
	* rows ����
	* cols ����
	*/
	int **InitMatrix(int rows, int cols);

	/**
	* ��ʼ������
	* mat ����
	* size ��С
	*/
	int **InitMatrix(int size);

	/**
	* ��ӡ����
	* mat ����
	* size ��С
	*/
	void PrintMatrix(int **mat, int size);

	/**
	* ��ӡ����
	* a ����
	* n ����
	*/
	template<class T>
	void PrintArray(T a[], int n);

	namespace DivideAndConquer {

		// ���̸���
		namespace ChessBoard {

			static int tile = 0;

			void Init(int **board, int dr, int dc);
			/**
			* ���̸���
			* tr �������ϽǷ����к�
			* tc �������ϽǷ����к�
			* dr ���ⷽ�������к�
			* dc ���ⷽ�������к�
			* size ���̴�С
			*/
			void Solve(int **board, int tr, int tc, int dr, int dc, int size);
			void test();
		}

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

		namespace MaxSubSum {

			/* ����Ӷκ�����ļ��㷨*/
			int Solve(int n, int *a, int &besti, int &bestj);
			/* ����Ӷκ�����ķ����㷨*/
			int SolveDC(int *a, int left, int right);
			/* ����Ӷκ�����Ķ�̬�滮�㷨*/
			int SolveDP(int *a, int left, int right);
			/* ��������Ӷκ�*/
			void test();
		}

		namespace MatrixChain {

			/* ����������� */
			void Solve(int *p, int **m, int **s, int n);
			/* ���ݽ� */
			void TraceBack(int i, int j, int **s);
			/* 3.1 ���Ծ������� */
			void test();
		}

		namespace LongestCommonSubsequence {

			/* ����������� */
			void Solve(string a, string b, int **c, int **s);
			/* ��ӡ����������� */
			void PrintLCS(string a, string b, int **s);
			/* 3.3 ��������������� */
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

		void test();
	}
	void test();
};