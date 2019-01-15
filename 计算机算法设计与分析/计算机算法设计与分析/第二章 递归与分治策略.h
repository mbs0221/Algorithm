#pragma once


#include "������㷨��������.h"

namespace Algorithm {

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
}