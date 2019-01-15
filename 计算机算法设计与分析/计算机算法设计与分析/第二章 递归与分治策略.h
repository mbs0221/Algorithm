#pragma once


#include "计算机算法设计与分析.h"

namespace Algorithm {

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
}